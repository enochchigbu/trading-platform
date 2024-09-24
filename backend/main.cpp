// This file will be the connecting point for the backend business logic to the front end

// TODO: In the future, for scalability, there may need to be mulitple web servers that send data to the frontend asynchronously
#include <iostream>
#include <string>
#include <vector>

#include "crow.h"
#include "crow/middlewares/cors.h"
#include "trading_engine/market_data/dataParser.cpp"

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
        crow::json::wvalue response({{"message", "Hello from C++ backend"}});

        // run the system call to get all updated market data with python script
        int script = system("python3 ./trading_engine/market_data/get_crypto_market_data.py")

        // parse the csv file and get the first line
        if (script != 0) {
            
        }

        crow::json::wvalue response({{"message", "Hello from C++ backend"}});
        crow::response res(response);
        res.set_header("Content-Type", "application/json");
        return res; });

    app.port(3001).multithreaded().run();
    return 0;
}