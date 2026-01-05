const {app, BrowserWindow, ipcMain, Menu} = require('electron');
const {spawn, spawnSync} = require('child_process')
const path = require('path');
const fs = require('fs');       // File system

let currentProcess = null;      // VM process used to execute C code

const createWindow = () => {
    const win = new BrowserWindow({
        width: 800,
        height: 600,
        webPreferences: {
            preload: path.join(__dirname, 'preload.js'),
            contextIsolation: true,
            nodeIntegration: false
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

ipcMain.handle('get-mi-programs', async () => {
  const programsDir = path.join(__dirname, '..', 'vm', 'programs');
  const files = fs.readdirSync(programsDir);
  return files.filter(file => file.endsWith('.mi'));
});


// Compile VM if not already done
function ensureVMCompiled() {
    const vmBinary = path.join(__dirname, '..', 'vm', 'vm.exe');

    if (fs.existsSync(vmBinary)) {  // Already compiled
        return;
    } 

    const sources = [
        'virtual_routines.c',
        'vm.c',
        'register_dump.c',
        'instructions.c',
        'initialisation.c',
        'heapbanks.c',
        'decoding.c'
        ].map(f => path.join(__dirname, '..', 'vm', f));

    const result = spawnSync('gcc', ['-o', vmBinary, ...sources], { stdio: 'inherit' });
    if (result.status !== 0) {
        throw new Error('VM compilation failed');
    }
}

// Run VM
ipcMain.handle('run-vm', async (event, programName) => {
    ensureVMCompiled();

    const vmBinary = path.join(__dirname, '..', 'vm', 'vm.exe');
    const programPath = path.join(__dirname, '..', 'vm', 'programs', programName);

    if (currentProcess) {
        currentProcess.kill();
    }

    //await new Promise(resolve => setTimeout(resolve, 100));

    currentProcess = spawn(vmBinary, [programPath]);

    currentProcess.stdout.on('data', (data) => {
        event.sender.send('vm-output', data.toString());
    });

    currentProcess.stderr.on('data', (data) => {
        event.sender.send('vm-output', data.toString());
    });

    currentProcess.on('close', (code) => {
        event.sender.send('vm-exit', code);
        currentProcess = null;
    });

    return true;
})

// Send input to C console
ipcMain.on('vm-input', (event, input) => {
  if (currentProcess) {
    currentProcess.stdin.write(input + '\n');
  }
});

app.on('ready', () => {
    createWindow();
    //Menu.setApplicationMenu(null);
})

