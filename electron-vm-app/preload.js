const {contextBridge, ipcRenderer} = require('electron');

contextBridge.exposeInMainWorld('api', {
    getMiPrograms: () => ipcRenderer.invoke('get-mi-programs'),
    runVM: (programName) => ipcRenderer.invoke('run-vm', programName),
    
    onVMOutput: (callback) => {
        const listener = (event, data) => callback(data);
        ipcRenderer.on('vm-output', listener);
        return () => ipcRenderer.removeListener('vm-output', listener);
    },
    
    onVMExit: (callback) => {
        const listener = (event, code) => callback(code);
        ipcRenderer.on('vm-exit', listener);
        return () => ipcRenderer.removeListener('vm-exit', listener);
    },
    
    sendVMInput: (input) => ipcRenderer.send('vm-input', input),
});