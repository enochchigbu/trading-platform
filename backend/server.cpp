// This file will be the connecting point for the backend business logic to the front end

// In the future, for scalability, there may need to be mulitple web servers that send data to the frontend asynchronously
#include <iostream>
#include <string>
#include <vector>

#include "crow.h"
#include "crow/middlewares/cors.h"

using namespace std;

int main()
{
    crow::App<crow::CORSHandler> app;

    auto &cors = app.get_middleware<crow::CORSHandler>();
    cors
        .global()
        .headers("X-Requested-With", "Content-Type", "Accept", "Access-Control-Allow-Headers", "Access-Control-Allow-Origin")
        .methods("POST"_method, "GET"_method)
        .origin("http://localhost:3000");

    CROW_ROUTE(app, "/")
    ([]()
     {
        // Sample JSON response value 
        crow::json::wvalue response({{"message", "Hello from C++ backend"}});
        crow::response res(response);
        res.set_header("Content-Type", "application/json");
        return res; });

    app.port(3001).multithreaded().run();
    return 0;
}