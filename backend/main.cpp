#include <iostream>
#include <string>
#include <vector>

#include "crow.h"
#include "crow/middlewares/cors.h"
#include "trading_engine/market_data/parse/data_parser.h"

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
        // run the system call to get all updated market data with python script
        system("python3 ../trading_engine/market_data/fetch/data_fetcher.py");

        // Parse the csv file output of the script with the DataParser class
        vector<DataRow> market_data = DataParser::parseCSV("../trading_engine/market_data/data/stock_market_data.csv");
        
        // Run neccesary algorithms in cpp to determine which stocks should be bought

        // Conduct market orders if neccesary

        // Send data to frontend
        crow::json::wvalue response({{"message", market_data[0].timestamp}});
        crow::response res(response);
        res.set_header("Content-Type", "application/json");
        return res; });

    app.port(3001).multithreaded().run();
    return 0;
}