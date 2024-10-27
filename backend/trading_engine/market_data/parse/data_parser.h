#ifndef DATAPARSER_H
#define DATAPARSER_H

#include <string>
#include <vector>
#include <chrono>
#include <fstream> 

using namespace std;

struct DataRow {
    string symbol;
    string timestamp;

    // OHLC (Open, High, Low, Close) Prices
    double open;
    double high;
    double low;
    double close;

    // Trading Metrics
    double volume;
    double trade_count;
    double vwap;
};


class DataParser {
public:
    // Method to parse a CSV file given a file path
    static vector<DataRow> parseCSV(const string& filePath);

    static vector<DataRow> parseJSON(const string& filepath);

private:

};

#endif // DATAPARSER_H