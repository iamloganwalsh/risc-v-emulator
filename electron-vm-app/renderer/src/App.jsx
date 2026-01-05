import './App.css'
import { ViewFileButton, UploadFileButton, RunFileButton } from './components/Buttons';
import { Chatbox } from './components/Chatbox';
import { FileSelector } from './components/FileSelector';
import {useState} from 'react';

function App() {
  const [selectedFile, setSelectedFile] = useState('');

  return (
    <div className="UIContainer">
      <div className="FileSelectorDiv">
        <FileSelector className="FileSelector" onSelect={setSelectedFile} />
      </div>

      <div>
        <Chatbox />
      </div>

      <div className="Buttons">
        <ViewFileButton fileName={selectedFile} />
        <UploadFileButton fileName={selectedFile} />
        <RunFileButton fileName={selectedFile} />
      </div>
    </div>

  );
}

export default App;

