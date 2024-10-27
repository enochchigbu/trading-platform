# TODO: Add option functionality in future

import datetime
import json
import os

from alpaca.data.historical import CryptoHistoricalDataClient, StockHistoricalDataClient
from alpaca.data.requests import CryptoBarsRequest, StockBarsRequest
from alpaca.data.timeframe import TimeFrame

BASE_PATH = "/Users/enochchigbu/Personal Projects/CPP Projects/trading-platform/backend"
api_keys_path = os.path.join(BASE_PATH, "trading_engine/market_data/api_keys.json")

# Get API Keys from json file, store as const
with open(api_keys_path) as keys_file:
    keys = json.load(keys_file)

ALPACA_PAPER_API_KEY = keys['ALPACA_PAPER_API_KEY']
ALPACA_PAPER_API_SECRET = keys['ALPACA_PAPER_API_SECRET']

# Get today's date and date from a week ago
end_date = datetime.date.today()
start_date = end_date - datetime.timedelta(weeks=1)

# Convert the Datetime objects to strings
start_date_str = start_date.strftime("%Y-%m-%d")
end_date_str = end_date.strftime("%Y-%m-%d")

# Create the clienta for getting historical data
crypto_client = CryptoHistoricalDataClient()
stock_client = StockHistoricalDataClient(
    ALPACA_PAPER_API_KEY,  ALPACA_PAPER_API_SECRET)

# Request objects
crypto_request = CryptoBarsRequest(
    symbol_or_symbols=["BTC/USD", "ETH/USD"],
    timeframe=TimeFrame.Hour,
    start=start_date_str,
    end=end_date_str
)
stock_request = StockBarsRequest(
    symbol_or_symbols=["AAPL", "TSLA", "GOOGL", "MSFT", "NVDA"],
    timeframe=TimeFrame.Hour,
    start=start_date_str,
    end=end_date_str
)

# Retrieve data in a DataFrame and printing it
crypto_bars = crypto_client.get_crypto_bars(crypto_request)
stock_bars = stock_client.get_stock_bars(stock_request)


crypto_data_path = os.path.join(BASE_PATH, "trading_engine/market_data/data/crypto_market_data.csv")
market_data_path = os.path.join(BASE_PATH, "trading_engine/market_data/data/stock_market_data.csv")

# Convert data to json file and store
crypto_bars.df.to_csv(crypto_data_path)
stock_bars.df.to_csv(market_data_path)
