import './App.css'
import { ViewFileButton, UploadFileButton, RunFileButton } from './components/Buttons';
import { Chatbox } from './components/Chatbox';
import { FileSelector } from './components/FileSelector';
import { useState, useRef } from 'react';

function App() {
  const [selectedFile, setSelectedFile] = useState('');
  const chatboxRef = useRef(null);

  const handleFileSelect = (file) => {
    setSelectedFile(file);
    chatboxRef.current?.clearMessages();
  }

  return (
    <div className="UIContainer">
      <div className="FileSelectorDiv">
        <FileSelector className="FileSelector" onSelect={handleFileSelect} />
      </div>

      <div style={{width: '100%'}}>
        <Chatbox ref={chatboxRef}/>
      </div>

      <div className="Buttons">
        <ViewFileButton fileName={selectedFile} />
        <UploadFileButton fileName={selectedFile} />
        <RunFileButton fileName={selectedFile} chatboxRef={chatboxRef}/>
      </div>
    </div>

  );
}

export default App;

