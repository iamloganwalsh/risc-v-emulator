import './Buttons.css'

export function ViewFileButton({ fileName }) {
  const handleClick = () => {
    if (!fileName) return alert('No file selected!');
    console.log('Viewing file:', fileName);
    // TODO: implement actual viewing logic
  };

  return (
    <button onClick={handleClick}>
      View File
    </button>
  );
}

export function UploadFileButton({ fileName }) {
  const handleClick = () => {
    if (!fileName) return alert('No file selected!');
    console.log('Uploading file:', fileName);
    // TODO: implement upload logic
  };

  return (
    <button onClick={handleClick}>
      Upload File
    </button>
  );
}

export function RunFileButton({ fileName, chatboxRef }) {
  const handleClick = () => {
    if (!fileName) return alert('No file selected!');
    chatboxRef.current?.clearMessages();
    chatboxRef.current?.addMessage(`Executing file: ${fileName}\n`)
    window.api.runVM(fileName); 
  };

  return (
    <button onClick={handleClick}>
      Execute File
    </button>
  );
}
