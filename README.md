# Student Record Management System (SRMS)

## Overview

The **Student Record Management System (SRMS)** is a console-based C application designed to manage student academic data efficiently using:

- File Handling  
- Modular Programming  
- Role-Based Access Control  
- Secure Login with Password Masking  
- Search by Roll Number and by Name (New Feature)

The system includes three user roles:
- **Admin** (full access)
- **Staff** (limited access)
- **User** (view-only access)

This project contains the complete SRMS application, simulation outputs, and project documentation.


## Authentication System
- Username & Password login  
- **Password masking** using `_getch()` (Windows only)  
- Credentials stored in `credentials.txt`  
- **Three failed login attempts → Auto exit**  


## Role-Based Access Control
| Role      | Permissions                                   |
|-----------|-----------------------------------------------|
| **Admin** | Add, Display, Search, Update, Delete          |
| **Staff** | Display, Search, Update                       |
| **User**  | Display, Search                               |

---

## Newly Added Feature: Search by Name
A new search system is added:

### 1) Search by Roll Number  
Traditional exact match search.

### 2) Search by Name  
- Case-insensitive  
- Supports **partial name search**  
  Example: Searching `ki` finds both **Kiran** and **KiranKumar**  
- Uses the newly added helper function with `tolower()` (requires `#include <ctype.h>`)


## File Structure
SRMS-Project/
│
├── student_app.c # Main C program (with password masking + new search feature)
├── credentials.txt # Username, password, role
├── students.txt # Student records database
├── README.md # Project documentation
└── simulation/ # Screenshots (program output)



## Technologies Used
- **C Language**
- **GCC Compiler (MinGW / VS Code)**
- `conio.h` for password masking
- `ctype.h` for lowercase conversions (new addition)
- Text-file database for persistent storage

## How to Compile & Run (Windows PowerShell)

### Compile:
gcc -o student_app.exe student_app.c

### Run:
.\student_app.exe

Use **PowerShell or CMD**, not Git Bash.


## Credentials Format (`credentials.txt`)
Format:
username password role

Example:
admin admin123 admin
staff staff123 staff
user user123 user

## Student File Format (`students.txt`)
Each record:
roll name marks


Example:
101 Kiran 89.5
102 Ravi 77.0
103 Priya 90.0


## Search System (Updated)

### 1. Search by Roll
- Enter roll number  
- Displays exact match  

### 2. Search by Name (New)
- Enter full or partial name  
- Case-insensitive  
- Supports substring matching  
- Displays all matching students  

Example search:
Enter name: ki

Results:
101 Kiran 89.50
104 KiranKumar 88.20

## How the System Works

### Login Module
- Username input  
- Password masked using `_getch()`  
- Authentication from `credentials.txt`  

###  Menu Based on Role
- Admin → Full menu  
- Staff → Limited menu  
- User → View-only menu  

### Operations

#### Admin:
- Add Student  
- Display All  
- Search (Roll/Name)  
- Update  
- Delete  

#### Staff:
- Display  
- Search (Roll/Name)  
- Update  

#### User:
- Display  
- Search (Roll/Name)  


## Simulation
All screenshots showing program execution are stored in:

simulation/


Includes:
- Login Screen  
- Admin Menu  
- Staff Menu  
- User Menu  
- Search by Name (New)  
- Add / Update / Display / Delete operations  


## Conclusion
The **Student Record Management System (SRMS)** is a complete implementation of:

- File handling  
- Authentication  
- Role-based access  
- Secure input handling  
- Modular programming  
- **Name-based search capability (new feature)**  

The project fulfills all academic requirements and demonstrates practical understanding of structured programming and real-world data management.


## Author
**Name:** D. Hemanth  
**Roll No:** AP24110011296  
**College:** SRM-AP UNIVERSITY  


## References
- *The C Programming Language* – Kernighan & Ritchie  
- GCC Documentation  
- StackOverflow C discussions  
- Microsoft Docs – conio.h, ctype.h  
- Classroom lecture notes  
