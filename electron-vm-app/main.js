const {app, BrowserWindow} = require('electron');
const path = require('path');

const createWindow = () => {
    const win = new BrowserWindow({
        width: 800,
        height: 600,
        webPreferences: {
            preload: path.join(__dirname, 'preload.js')
        }
    });

    // DEV: load Vite dev server
    if (process.env.VITE_DEV_SERVER_URL) {
        win.loadURL(process.env.VITE_DEV_SERVER_URL);
    } 
    // PROD: load built React files
    else {
        win.loadFile(path.join(__dirname, 'renderer/dist/index.html'));
    }
}

app.whenReady().then(createWindow);