# QnA System

A simple **console-based Question & Answer System** developed in **C++**.  
The application uses **CSV files** as a lightweight database to manage users and questions without requiring an external database system.

---

## Features

- 🔐 User registration
- 🔑 User login & authentication
- ❓ Ask questions to other users
- 📥 View received questions
- 💬 Answer pending questions
- 🚪 Sign out

---

## Project Structure

```
QnA-System/
│── main.cpp
│── users.csv
│── questions.csv
└── README.md
```

---

## Getting Started

### 1. Clone the repository

```bash
git clone https://github.com/your-username/QnA-System.git
cd QnA-System
```

### 2. Compile the project

Using **g++**:

```bash
g++ main.cpp -o QnA
```

### 3. Run the application

**Linux / macOS**

```bash
./QnA
```

**Windows**

```bash
QnA.exe
```

---

## Data Storage

The system stores data using CSV files:

- `users.csv` → Stores registered users.
- `questions.csv` → Stores questions and answers.

---

## ⚠️ Current Limitations

- Passwords are stored as plain text (for learning purposes only).
- Data is stored locally using CSV files.
- The application exits after the user signs out.
- No password hashing or encryption is implemented.

---

## 🛠 Technologies Used

- C++
- Object-Oriented Programming (OOP)
- File Handling
- CSV Storage

---

## 📌 Future Improvements

- Encrypt user passwords.
- Delete or edit questions.
- Search for users.
- Admin dashboard.
- Replace CSV files with SQLite or MySQL.
- Improve input validation and error handling.

---

## Author

**Hoor Hisham**

Computer Science Student • Competitive Programming Enthusiast • Android Developer
