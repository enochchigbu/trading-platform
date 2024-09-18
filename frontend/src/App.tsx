import React, {useState, useEffect} from 'react';
import axios from 'axios-typescript';
import './App.css';

function App() {
  const [message, setMessage] = useState<string>('');

    useEffect(() => {
        const fetchData = async () => {
            try {
                const response = await axios.get('http://0.0.0.0:3001/');
                console.log(response)
                //  TODO: Change something to deprecate JSON.Parse
                setMessage(JSON.parse(response.data).message);
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
