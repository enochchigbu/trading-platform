#include <iostream>
#include <string>
#include <vector>

#include "crow.h"
#include "crow/json.h"
#include "crow/middlewares/cors.h"
#include "trading_engine/market_data/parse/data_parser.h"

using namespace std;

crow::json::wvalue convertDataRowsToJson(const std::vector<DataRow>& dataRows);

int main()
{
    crow::App<crow::CORSHandler> app;

    auto &cors = app.get_middleware<crow::CORSHandler>();
    cors
        .global()
        .headers("X-Requested-With", "Content-Type", "Accept", "Access-Control-Allow-Headers", "Access-Control-Allow-Origin")
        .methods("POST"_method, "GET"_method)
        .origin("http://localhost:3000");

    CROW_ROUTE(app, "/get_market_data_json")
    ([]()
     {
        // run the system call to get all updated market data with python script
        system("python3 ../trading_engine/market_data/fetch/data_fetcher.py");

        // Parse the csv file output of the script with the DataParser class
        vector<DataRow> market_data = DataParser::parseCSV("../trading_engine/market_data/data/stock_market_data.csv");

        // Send market data to frontend
        crow::json::wvalue jsonData = convertDataRowsToJson(market_data);
        crow::response res(jsonData);

        // Set neccessary headers
        res.set_header("Access-Control-Allow-Origin", "*");
        res.set_header("Access-Control-Allow-Headers", "Content-Type");
        res.set_header("Content-Type", "application/json");

        // TODO: Figure out why JSON response is sending as a JSON string and not a JSON object
        
        return res; 
    });
    
    app.port(3001).multithreaded().run();
    return 0;
}

crow::json::wvalue convertDataRowsToJson(const vector<DataRow>& dataRows) {
    crow::json::wvalue::list rowList;

    for (const auto& row : dataRows) {
        crow::json::wvalue rowValue;

        rowValue["symbol"] = row.symbol;

        rowValue["timestamp"] = row.timestamp;
        rowValue["open"] = row.open;
        rowValue["high"] = row.high;
        rowValue["low"] = row.low;
        rowValue["close"] = row.close;
        rowValue["volume"] = row.volume;
        rowValue["trade_count"] = row.trade_count;
        rowValue["vwap"] = row.vwap;

        rowList.emplace_back(rowValue);
    }

    crow::json::wvalue jsonValue;
    jsonValue = move(rowList);

    return jsonValue;
}