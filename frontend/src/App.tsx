import React, {useState, useEffect} from 'react';
import axios from 'axios-typescript';
import './App.css';

function App() {
  const [message, setMessage] = useState<string>('');

    useEffect(() => {
        const fetchData = async () => {
            try {
                const response = await axios.get('http://0.0.0.0:3001/get_market_data_json');
                console.log(response)
                const data = JSON.parse(response.data);
                setMessage(data[0].symbol);
            } catch (error) {
                console.error('Error fetching data:', error);
                setMessage('Error fetching data');
            }
        };

        fetchData();
    }, []);

  return (
    <div className="App">
      <header className="App-header">
        <p> {message} </p>
      </header>
    </div>
  );
}

export default App;
