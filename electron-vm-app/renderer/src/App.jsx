import './App.css'

function App() {
  const message = window.api.hello();

  return (
    <div style={{ padding: 20 }}>
      <h1>Electron + React</h1>
      <p>{message}</p>
    </div>
  );
}

export default App;

