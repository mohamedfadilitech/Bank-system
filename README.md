# 🏦 Bank System OOP (C++)

![C++](https://img.shields.io/badge/C++-20-blue.svg)
![Platform](https://img.shields.io/badge/Platform-Windows%20%7C%20Linux-lightgrey.svg)
![Build](https://img.shields.io/badge/Build-Passing-brightgreen.svg)

An Object-Oriented Banking System written in C++. It simulates a real-world console-based banking application featuring client management, transactions, account tracking, and secure user logins.

## ✨ Features
- **User Authentication:** Login system tracking access logs safely.
- **Client Management:** Add, update, delete, or search for bank clientele.
- **Transactions:** Deposit and withdraw logic to smoothly operate on balances.
- **Persistence:** Local text files tracking state (`Clients.txt`, `Users.txt`).
- **Clean Architecture:** Well-organized structure separated into `src`, `include`, and `data` directories.

---

## 📂 Project Structure

```text
BankingSystem/
├── src/                # .cpp source files containing the implementation logic
├── include/            # .h header files containing the class definitions
├── data/               # Persistent data text files (Clients, Users, History)
├── bankSystemOOP.sln   # Visual Studio Solution File
└── .gitignore          # Keeps generated files & binaries off Git
```

---

## 🚀 Getting Started

This application can easily be compiled and run on both **Windows** and **Linux**. Since it persists data via local `.txt` files, **ensure you run the executable from the project's root folder (`BankingSystem/`)** so it can locate the `data/` directory.

### 🪟 Windows (Visual Studio / MSBuild)

**Option 1: Using Visual Studio**
1. Open `bankSystemOOP.slnx` or `bankSystemOOP.vcxproj` in Visual Studio 2022.
2. Select your Architecture (e.g., `x64` or `x86`) and Build Configuration (`Debug` or `Release`).
3. Build the project (`Ctrl+Shift+B`).
4. Press `F5` to run the application directly from Visual Studio.

**Option 2: Using the Command Line (MSBuild)**
1. Open the **Developer Command Prompt for VS**.
2. Navigate to the `BankingSystem/` directory.
3. Build the project:
   ```cmd
   msbuild bankSystemOOP.vcxproj /p:Configuration=Release /p:Platform=x64
   ```
4. Run the executable:
   ```cmd
   x64\Release\bankSystemOOP.exe
   ```

---

### 🐧 Linux (g++ compiler)

Since the codebase is standard cross-platform C++20, compiling on Linux is incredibly straightforward using `g++`.

1. Open your terminal and navigate to the project root (`BankingSystem/`).
2. Make sure you have `g++` and `make` tools installed.
   ```bash
   sudo apt update
   sudo apt install g++ build-essential
   ```
3. Compile the local files manually from the root directory:
   ```bash
   g++ src/*.cpp -I include -std=c++20 -o BankSystem
   ```
4. Run the newly compiled application:
   ```bash
   ./BankSystem
   ```

*(Note: Data operations will perfectly manage the corresponding files internally under `data/`)*

---

## 🛠 Built With
* [C++20](https://isocpp.org/) — Main programming language used
* [MSBuild](https://learn.microsoft.com/en-us/visualstudio/msbuild/msbuild) — Build environment for Windows
* Standard Library `<iostream>`, `<fstream>`, `<vector>`, `<string>`, etc.

## 📄 License
This project is open-source and free to use.
