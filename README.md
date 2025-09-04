# HexTerm
HexTerm – A powerful all-in-one Windows terminal &amp; dev environment with multi-language support, file management, networking tools, and built-in Hex editor.
# HexTerm – Advanced Terminal & Dev Environment

## Description
**HexTerm** is an advanced terminal for Windows that not only executes CMD commands but also runs programs and scripts in multiple languages (C, C++, Python, Node.js) and includes a Hex Editor mode for file manipulation in hexadecimal format.

---

## Features

- Execute system commands (CMD Mode)
- **HexTerm Mode**:
  - Hex view of files and save as `-hex.txt`
  - Recover file from hex
  - Overwrite original file from hex
- **Dev Mode for multiple languages**:
  - **C**: create project, add headers, compile and run
  - **C++**: same as C with standard C++ templates
  - **Python**: create project, install packages with pip, run scripts
  - **Node.js**: create project, install packages with npm/yarn, run scripts
- File and directory management (create, delete, list contents)
- Download files from the internet using curl
- Ping IP addresses
- Display network information
- Change prompt and response colors
- Play startup sound
- Interactive menu with animation and colors

---

## Installation

**Requirements:**
- Windows
- Installed gcc/g++, Python, Node.js, NPM (for Dev Mode)

**Installation Steps:**
1. Clone the repository:
   ```bash
   git clone <repository-url>
   ```
2. Run `HexTerm.exe` or compile with Visual Studio/CLion
3. Place the WAV file in `Config\HEXTERM.wav` for startup sound

---

## Usage

**Run Terminal:**
```bash
HexTerm.exe
```

**Common Commands:**
| Command  | Description             |
|----------|-------------------------|
| cc       | Compile C program       |
| cc+      | Compile C++ program     |
| py       | Run Python script       |
| nd       | Run Node.js script      |
| rt       | Start React/NPM project |
| mkp      | Create new project      |
| mkd      | Create directory        |
| mkf      | Create file             |
| rm       | Delete file             |
| rmd      | Delete directory        |
| ip       | Display network info    |
| ipg      | Ping an IP              |
| show     | Show file content       |
| dn       | Download file           |
| cls/clear| Clear terminal          |
| ch      | Switch to CMD mode       |
| help/-h | Show menu                |

---

## Developer Mode

**C/C++:**
- `mkp <project_name>` – Create new project
- `add` – Add header
- `run` – Compile and run
- `show -hd` – Show added headers

**Python:**
- `mkp <project_name>` – Create Python file
- `run` – Execute file
- `pip <package>` – Install package

**Node.js:**
- `mkp <project_name>` – Create JS file
- `run` – Execute file
- `npi <package>` – Install npm/yarn package

**HexMode:**
- `show-hex <file>` – Convert file to hex
- `marge <file-hex.txt>` – Recover file from hex (copy)
- `repMarge <file-hex.txt>` – Overwrite original file from hex

---

## Contributing

- Pull requests and issues are welcome
- Follow coding style and naming conventions

---

## License

MIT License



