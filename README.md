# 🏦 BankVault OOP — C++

![C++](https://img.shields.io/badge/C++-20-blue.svg?style=for-the-badge&logo=cplusplus)
![Platform](https://img.shields.io/badge/Platform-Windows%20%7C%20Linux-lightgrey.svg?style=for-the-badge)
![Build](https://img.shields.io/badge/Build-Passing-brightgreen.svg?style=for-the-badge)
![Architecture](https://img.shields.io/badge/Architecture-OOP-orange.svg?style=for-the-badge)
![License](https://img.shields.io/badge/License-MIT-yellow.svg?style=for-the-badge)

> A fully Object-Oriented console-based Banking System built in C++ — featuring secure login, role-based permissions, client & user management, transactions, transfer logs, login history, and a real-time currency exchange calculator. No external libraries. No frameworks. Pure C++.

---

## 📸 App Preview

| Screen | Preview |
|--------|---------|
| 🔐 Login | Secure credential prompt with session date tracking |
| 🏠 Main Menu | 10 options including Currency Exchange and Login History |
| 💰 Transactions | Deposit, Withdraw, Transfer, Transfer Logs |
| 👥 Manage Users | Full CRUD for system users |
| 💱 Currency Exchange | List, Find, Update rates, and a live Calculator |

---

## 🆚 V2 vs V3 — What's New

| Feature | V2 (BankVault) | V3 (BankVault OOP) |
|---------|---------------|-------------------|
| Architecture | Functional / Procedural | Fully Object-Oriented |
| Login System | ✅ | ✅ |
| Client Management | ✅ | ✅ |
| User Management | ✅ | ✅ |
| Bitwise Permissions | ✅ | ✅ |
| Transactions | Deposit / Withdraw | Deposit / Withdraw / **Transfer** |
| Transfer Logs | ❌ | ✅ |
| Login History | ❌ | ✅ |
| Currency Exchange | ❌ | ✅ (List / Find / Update / Calculator) |
| Code Style | Structs + free functions | Classes with encapsulation |

---

## ✨ Features

### 🔐 Authentication & Sessions
- Login screen with username & password verification
- Session header displays the **logged-in user** and **current date** on every screen
- Logout returns to login screen — no restart required
- Invalid credentials keep prompting until a valid login is entered
- **Login history log** — every login attempt is recorded with timestamp

### 🛡️ Permission System
- Bitwise permission flags — each operation is a power-of-2 bit
- Per-user access control — every user has a custom permissions integer
- Admin mode — value of `-1` grants unrestricted access to everything
- Access denied screen shown when a user attempts a blocked operation
- Menu options hidden based on user permissions

### 👤 Client Management
- 📋 List all clients in a formatted table
- ➕ Add new client — account ID, PIN, name, phone, balance
- 🗑️ Delete client by account ID
- ✏️ Update client details
- 🔍 Find client by account ID
- 🚫 Duplicate account ID prevention

### 👥 User Management
- 📋 List all system users with permission values
- ➕ Add new user with interactive permission assignment
- 🗑️ Delete user by username
- ✏️ Update user password and permissions
- 🔍 Find user by username

### 💰 Transactions
- 💵 Deposit — add funds to any client account
- 💸 Withdraw — deduct funds with overdraft prevention
- 📊 Total Balances — view all accounts with combined total
- 🔄 Transfer — move funds between two accounts
- 📋 Transfer Logs — full history of all transfers

### 💱 Currency Exchange
- 📋 List all supported currencies with rates
- 🔍 Find a specific currency by code
- ✏️ Update exchange rate for any currency
- 🧮 Currency Calculator — convert any amount between any two currencies

### 💾 Persistent Storage
- All data saved to and loaded from local `.txt` files in the `data/` folder
- Custom `#//#` delimiter for reliable record parsing
- File fully reloaded on every operation to reflect live state

---

## 🛡️ How Permissions Work

Each permission is a power of 2 (bit flag). A user's total permissions value is the **sum** of all granted permissions:

| Permission | Value |
|------------|-------|
| Show Client List | 1 |
| Add New Client | 2 |
| Delete Client | 4 |
| Update Client | 8 |
| Find Client | 16 |
| Transactions | 32 |
| Manage Users | 64 |
| Admin (All) | -1 |

**Example:** A user with `permissions = 19` has: Show Client List `(1)` + Add New Client `(2)` + Find Client `(16)`

Stored in `Users.txt` as:
```
ahmed#//#pass123#//#19
```

---

## 🧠 How Data Is Stored

**Client record — `Clients.txt`**
```
A900#//#7827#//#Mohamed Fadili#//#0612345678#//#12000.000000
```

**User record — `Users.txt`**
```
Admin#//#1234#//#-1
ahmed#//#pass123#//#19
```

**Transfer log — `TransferLog.txt`**
```
A900#//#B100#//#500.00#//#2026/04/06 14:32:00#//#Admin
```

**Login history — `LoginHistory.txt`**
```
Admin#//#2026/04/06 09:19:00
```

> On every write operation, the file is fully read into memory, modified, then written back to disk.

---

## 📁 Project Structure

```
BankSystem/
│
├── src/                                  # .cpp source files (entry point & login)
│   ├── bankSystemOOP.cpp                 # Entry point — login flow and main menu dispatch
│   └── clsLoginScreen.cpp                # Login screen implementation
│
├── include/                              # .h header files — all class definitions
│   ├── Global.h                          # Global constants and shared enums
│   ├── clsPerson.h                       # Base person class
│   ├── clsBankClient.h                   # BankClient class (extends clsPerson)
│   ├── clsUser.h                         # User class with permissions
│   ├── clsCurrency.h                     # Currency class and exchange logic
│   ├── clsDate.h                         # Date utility class
│   ├── clsString.h                       # String utility class
│   ├── clsUtil.h                         # General utilities
│   ├── clsInputValidate.h                # Input validation helpers
│   ├── clsScreen.h                       # Base screen class (header drawing)
│   ├── clsMainScreen.h                   # Main menu display and routing
│   ├── clsLoginScreen.h                  # Login screen declaration
│   ├── clsLoginHistoryScreen.h           # Login history log screen
│   ├── clsClientListScreen.h             # Client list display
│   ├── clsAddNewClientScreen.h           # Add new client
│   ├── clsDeleteClientScreen.h           # Delete client
│   ├── clsUpdateClientScreen.h           # Update client
│   ├── clsFindClientScreen.h             # Find client
│   ├── clsTransactionsScreen.h           # Transactions menu
│   ├── clsDepositScreen.h                # Deposit logic
│   ├── clsWithdrawScreen.h               # Withdraw with overdraft check
│   ├── clsTotalBalancesScreen.h          # Total balances view
│   ├── clsTransferScreen.h               # Transfer between accounts
│   ├── clsTransferLogsScreen.h           # Transfer history log
│   ├── clsManageUsers.h                  # Manage users menu
│   ├── clsUsersListScreen.h              # List all users
│   ├── clsAddNewUserScreen.h             # Add new user
│   ├── clsDeleteUserScreen.h             # Delete user
│   ├── clsUpdateUserScreen.h             # Update user
│   ├── clsFindUserScreen.h               # Find user
│   ├── clsCurrenciesListScreen.h         # List all currencies
│   ├── clsFindCurrencyScreen.h           # Find currency by code
│   ├── clsUpdateCurrencyRateScreen.h     # Update exchange rate
│   ├── clsCurrencyExchangeScreen.h       # Currency exchange menu
│   └── clsCurrencyCalculatorScreen.h     # Currency calculator
│
├── data/                                 # Persistent flat-file database
│   ├── Clients.txt                       # All bank client records
│   ├── Users.txt                         # All system user records
│   ├── TransferHistory.txt               # Transfer transaction history
│   ├── loginHistory.txt                  # User login history
│   └── Currencies.txt                    # Currency codes and exchange rates
│
├── BankSystem.vcxproj                    # Visual Studio project file
├── BankSystem.vcxproj.filters            # VS folder structure
├── .gitignore                            # Ignores build artifacts and VS junk
└── README.md
```

---

## 🚀 Getting Started

### Prerequisites

- **Windows:** Visual Studio 2019+ with "Desktop development with C++" workload, **or** MinGW g++
- **Linux / macOS:** g++ with C++20 support (`g++ --version` should be 10+)

---

### 🪟 Windows — Visual Studio (Recommended ⭐)

1. Download [Visual Studio Community](https://visualstudio.microsoft.com/vs/community/) — free
2. During install, select **"Desktop development with C++"**
3. Open Visual Studio → **Open a project or solution** → select `BankSystem.vcxproj`
4. Press `Ctrl + Shift + B` to build
5. Press `Ctrl + F5` to run without debugging

---

### 🪟 Windows — Command Line (MSBuild)

1. Open **Developer Command Prompt for VS**
2. Navigate to the project root:
   ```cmd
   cd path\to\BankVaultOOP
   ```
3. Build:
   ```cmd
   msbuild BankSystem.vcxproj /p:Configuration=Release /p:Platform=x64
   ```
4. Run:
   ```cmd
   x64\Release\BankSystem.exe
   ```

---

### 🐧 Linux / macOS — g++

1. Open terminal and navigate to the project root
2. Install g++ if needed:
   ```bash
   sudo apt update && sudo apt install g++ build-essential
   ```
3. Compile:
   ```bash
   g++ src/*.cpp -I include -std=c++20 -o BankSystem
   ```
4. Run:
   ```bash
   ./BankSystem
   ```

> ⚠️ **Important:** Always run the executable from the **project root directory** so it can find the `data/` folder. Running it from inside `src/` or a build folder will cause file-not-found errors.

---

## 🛠️ Built With

- **Language:** C++20
- **Standard Library:** `<iostream>`, `<fstream>`, `<vector>`, `<string>`, `<iomanip>`, `<ctime>`, `<algorithm>`
- **Concepts Used:**
  - Object-Oriented Programming (classes, inheritance, encapsulation)
  - Multi-file architecture (`.h` declarations / `.cpp` definitions)
  - File I/O (read, write, truncate)
  - Bitwise operators for permission control
  - Static class methods for screen routing
  - String parsing with custom `#//#` delimiter
  - Session management with logout loop
  - Input validation with `do-while` loops

---

## 🔮 Future Improvements

- [ ] Password hashing (bcrypt or SHA-256)
- [ ] SQLite integration to replace flat-file storage
- [ ] CSV export for client and transaction reports
- [ ] Cross-platform `cls` / `clear` screen support
- [ ] Role presets (Teller, Manager, Admin)
- [ ] GUI frontend using Qt or ImGui

---

## 📌 Version History

| Version | Description |
|---------|-------------|
| V1 | Functional C++ — client management only |
| V2 | Added login system, user management, bitwise permissions |
| V3 (this) | Full OOP rewrite — transfer system, login history, currency exchange |

---

## 👤 Author

**Mohamed Fadili**
- GitHub: [@mohamedfadilitech](https://github.com/mohamedfadilitech)

---

## 📄 License

This project is open-source under the [MIT License](LICENSE).
