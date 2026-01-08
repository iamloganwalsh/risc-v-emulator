import './App.css'
import { ViewFileButton, UploadFileButton, RunFileButton } from './components/Buttons';
import { Chatbox } from './components/Chatbox';
import { ViewBoxModal } from './components/ViewBoxModal';
import { FileSelector } from './components/FileSelector';
import { useState, useRef } from 'react';

function App() {
  const [selectedFile, setSelectedFile] = useState('');
  const [fileContent, setFileContent] = useState('');
  const [viewBoxModal, setViewBoxModal] = useState(false);
  const [viewingFileName, setViewingFileName] = useState('');
  const chatboxRef = useRef(null);

  const handleFileSelect = (file) => {
    setSelectedFile(file);
    chatboxRef.current?.clearMessages();
    setFileContent('');
  }

  const handleViewFile = (fileName, content) => {
    setViewingFileName(fileName);
    setFileContent(content);
    setViewBoxModal(true);
  }

  const handleCloseModal = () => {
    setViewBoxModal(false);
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
        <ViewFileButton fileName={selectedFile} onView={handleViewFile}/>
        <UploadFileButton fileName={selectedFile} />
        <RunFileButton fileName={selectedFile} chatboxRef={chatboxRef}/>
      </div>

      <ViewBoxModal 
        isOpen={viewBoxModal} 
        onClose={handleCloseModal}
        content={fileContent}
        fileName={viewingFileName}
      />
    </div>

  );
}

export default App;

