# TODO: Add option functionality in future

import datetime

from alpaca.data.historical import CryptoHistoricalDataClient, StockHistoricalDataClient
from alpaca.data.requests import CryptoBarsRequest, StockBarsRequest
from alpaca.data.timeframe import TimeFrame

from api_keys import ALPACA_PAPER_API_KEY, ALPACA_PAPER_API_SECRET

# Get today's date
end_date = datetime.date.today()

# Get the date one week ago
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

print(crypto_bars.df)
print(stock_bars.df)

# Convert data to json file and store
crypto_bars.df.to_json('crypto_market_data.json', orient='records', indent=1)
stock_bars.df.to_json('stock_market_data.json', orient='records', indent=1)
crypto_bars.df.to_csv('crypto_market_data.csv')
stock_bars.df.to_csv('stock_market_data.csv')
