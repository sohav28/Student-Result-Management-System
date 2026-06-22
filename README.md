# Student Result Management System 📊

A robust, console-based application built in **C++** that demonstrates core **Object-Oriented Programming (OOP)** principles and persistent data storage using **File Handling**. 

This project simulates a real-world student grading and record management workflow, allowing users to perform complete **CRUD (Create, Read, Update, Delete)** operations on student records.

---

## 🚀 Features

- **Persistent Storage**: Uses C++ binary file streams (`ifstream`, `ofstream`, `fstream`) so that data remains safely saved on the disk even after closing the program.
- **Complete CRUD Operations**:
  - **Create**: Add new student profiles along with individual subject marks (DSA, OOP, DBMS).
  - **Read**: View all student records in a clean, formatted tabular layout or look up a specific student using their unique Roll Number.
  - **Update**: Edit existing student details and subject marks, which dynamically recalculates percentages and grades.
  - **Delete**: Permanently remove a student's record from the database.
- **Automated Performance Tracking**: Automatically calculates total marks, percentage, and assigns appropriate letter grades (`A`, `B`, `C`, `D`, `F`) based on predefined academic thresholds.
- **Robust User Interface**: Features an interactive, menu-driven command-line interface with built-in input formatting.

---

## 🛠️ Core CS & OOP Concepts Demonstrated

This project is specifically designed to showcase a deep understanding of core Computer Science fundamentals:

1. **Inheritance**: Implements a base class `Person` (holding generic attributes like Name) which is inherited by the derived class `Student` to promote code reusability.
2. **Encapsulation**: Data members (like marks, percentage, and roll numbers) are kept `private` within classes, exposed only through explicit public member functions (getters/setters).
3. **File I/O Handling**: Demonstrates efficient file handling mechanics using custom block reads/writes via `reinterpret_cast<char*>` to read and write entire objects directly into binary files.
4. **Formatting Streams**: Utilizes the `<iomanip>` library (`setw`, `left`, `fixed`, `setprecision`) to create a well-aligned, professional reporting dashboard in a console environment.

---

## 📂 Project Structure

```bash
├── code.cpp        # Main source code file containing classes and driver logic
└── README.md       # Project documentation
