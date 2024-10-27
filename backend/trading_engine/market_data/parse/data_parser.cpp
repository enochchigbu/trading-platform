#include "data_parser.h"
#include "csv.h"  // Assuming the CSVReader class is in csv.h
#include <fstream>
#include <sstream>
#include <iostream>
#include <vector>
#include <string>
#include <chrono>

using namespace std;
namespace csvlib = io;

vector<DataRow> DataParser::parseCSV(const string& filePath) {
    vector<DataRow> data;

    csvlib::CSVReader<9> csvReader(filePath);
    csvReader.read_header(csvlib::ignore_no_column, "symbol", "timestamp", "open", "high", "low", "close", "volume", "trade_count", "vwap");

    string symbol, timestamp;
    double open, high, low, close, volume, trade_count, vwap;

    while (csvReader.read_row(symbol, timestamp, open, high, low, close, volume, trade_count, vwap)) {
        DataRow row;

        row.timestamp = timestamp;
        row.symbol = symbol;
        row.open = open;
        row.high = high;
        row.low = low;
        row.close = close;
        row.volume = volume;
        row.trade_count = trade_count;
        row.vwap = vwap;

        data.push_back(row);
    }

    return data;
}

vector<DataRow> DataParser::parseJSON(const string& filePath) {
    vector<DataRow> data;
    return data;
}

