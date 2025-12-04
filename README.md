# Student Record Management System (SRMS)

## Overview
The **Student Record Management System (SRMS)** is a console-based C application designed to manage student academic data efficiently using:

- File Handling  
- Modular Programming  
- Role-Based Access Control  
- Secure Login with Password Masking  

The system includes three roles:
- **Admin** (full access)
- **Staff** (limited access)
- **User** (view-only access)

This project contains the complete SRMS application, simulation outputs, and project documentation.


## Authentication System
- Username & Password login  
- Password masking using `_getch()`  
- Credentials stored in `credentials.txt`  
- 3 failed attempts → Auto exit  


## Role-Based Access Control
| Role      | Permissions                                   |
|-----------|-----------------------------------------------|
| **Admin** | Add, Display, Search, Update, Delete          |
| **Staff** | Display, Search, Update                       |
| **User**  | Display, Search                               |


## File Structure
SRMS-Project/
│
├── student_app.c # Main C program
├── credentials.txt # Username, password, role
├── students.txt # Student records database
├── README.md # Project documentation
└── simulation/ # Screenshots (program output)


## Technologies Used
- **C Language**
- **GCC Compiler (MinGW / VS Code)**
- **conio.h** for password masking
- **Text file database**

## How to Compile & Run (Windows PowerShell)

### Compile:
gcc -o student_app.exe student_app.c

### Run:
.\student_app.exe

Use **PowerShell or CMD**, not Git Bash.


## Credentials Format (`credentials.txt`)
username password role

Example:
admin admin123 admin
staff staff123 staff
user user123 user

## Student File Format (`students.txt`)
Each record:
roll name marks

Example:
1 John 88.5
2 Maya 90.0

## How the System Works

### 1)Login Module
- Takes username  
- Masked password using `_getch()`  
- Authenticates from `credentials.txt`

### 2)Menu Based on Role
- Admin → Admin Menu  
- Staff → Staff Menu  
- User → User Menu  

### 3)Operations

#### Admin:
- Add  
- Display  
- Search  
- Update  
- Delete  

#### Staff:
- Display  
- Search  
- Update  

#### User:
- Display  
- Search  

## Simulation
Screenshots demonstrating the working system are stored in:

simulation/



## Conclusion
The **Student Record Management System (SRMS)** is a complete implementation of:

- File handling  
- Authentication  
- Role-based access  
- Secure input handling  
- Modular programming  

The project fulfills all academic requirements and provides a working simulation of student data management.

## Author
**Name:** D.Hemanth
**Roll No:**  AP24110011296 
**College:** SRM-AP UNIVERSITY


## References
- The C Programming Language – Kernighan & Ritchie  
- GCC Documentation  
- StackOverflow C discussions  
- Microsoft Docs – conio.h  
- Classroom lecture notes  

