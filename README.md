## ---- Description ----

This is my take on a generative AI  
special thanks to **Leo C. Ureel II** at MTU for prompting this idea

## ---- Requirements ----

- g++
- gdb (if you want to debug)
- python

## ---- commands to get started ----

### install external dependencies

1. `mkdir ../CFileRunner` <button onclick="copyToClipboard('mkdir ../CFileRunner')">Copy</button>
2. `git clone https://github.com/superg3m/CFileRunner.git ../CFileRunner` <button onclick="copyToClipboard('git clone https://github.com/superg3m/CFileRunner.git ../CFileRunner')">Copy</button>

### running the program

- `powershell -ExecutionPolicy Bypass -File ../CFileRunner/RunC.ps1` <button onclick="copyToClipboard('powershell -ExecutionPolicy Bypass -File ../CFileRunner/RunC.ps1')">Copy</button>

### Debug the program

- `powershell -ExecutionPolicy Bypass -File ../CFileRunner/DebugC.ps1` <button onclick="copyToClipboard('powershell -ExecutionPolicy Bypass -File ../CFileRunner/DebugC.ps1')">Copy</button>

### Alternatively

- `compile and run/debug the program using g++/gdb`

### Optional Step 3 for more data

1. `python .\PythonScripts\WebScrapper.py` <button onclick="copyToClipboard('python .\PythonScripts\WebScrapper.py')">Copy</button>
2. `python .\PythonScripts\FormatTxtFiles.py` <button onclick="copyToClipboard('python .\PythonScripts\FormatTxtFiles.py')">Copy</button>

<script>
  function copyToClipboard(command) {
    const el = document.createElement("textarea");
    el.value = command;
    document.body.appendChild(el);
    el.select();
    document.execCommand("copy");
    document.body.removeChild(el);
    alert("Command copied to clipboard!");
  }
</script>
