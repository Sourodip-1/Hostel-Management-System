# Hostel Management System

**C Language | File Handling | Role-Based Authentication**

A menu-driven Hostel Management System developed in **C** that allows a **Warden (Admin)** and **Students** to securely manage hostel operations using **file-based storage**.

This project simulates a **real-world hostel ERP system** using **structures, functions, file handling, authentication, and role-based access**.

---

## 📌 Problem Statement

Manual hostel record keeping leads to:

- Data loss
- No security
- Poor management
- No tracking of rooms, fees, or complaints

This system automates hostel management with:

- Secure login
- Permanent data storage
- Separate roles for Admin and Students

---

## 👥 System Users

| User               | Description                                        |
| ------------------ | -------------------------------------------------- |
| **Admin (Warden)** | Has full control over hostel data                  |
| **Student**        | Can view own data, pay fees, and submit complaints |

---

## 🔐 Authentication & Authorization

Users must log in using **ID and password**.

| Feature           | Admin | Student |
| ----------------- | ----- | ------- |
| Add student       | ✔     | ❌      |
| View all students | ✔     | ❌      |
| Assign rooms      | ✔     | ❌      |
| View fees         | ✔     | ❌      |
| Submit complaint  | ❌    | ✔       |
| View own data     | ❌    | ✔       |

This ensures **security and role-based access control**.

---

## 🧱 Software Architecture

```
User
  ↓
Menu System
  ↓
Login & Authentication
  ↓
Role Validation (Admin / Student)
  ↓
Function Execution
  ↓
File Read / Write
  ↓
Data Display
```

---

## 📂 File-Based Database Design

| Data       | File           |
| ---------- | -------------- |
| Students   | students.dat   |
| Admins     | admins.dat     |
| Rooms      | rooms.dat      |
| Fees       | fees.dat       |
| Complaints | complaints.dat |

Each file behaves like a **database table**.

---

## 🧩 Data Structures

```c
struct Student {
    int id;
    char name[50];
    char password[20];
    int roomNo;
};

struct Admin {
    char username[20];
    char password[20];
};

struct Room {
    int roomNo;
    int capacity;
    int occupied;
};

struct Fee {
    int studentId;
    float total;
    float paid;
};

struct Complaint {
    int studentId;
    char text[200];
};
```

---

## 📊 Data Flow

```
User Input
    ↓
Menu Selection
    ↓
Authentication
    ↓
Role Check
    ↓
Function Execution
    ↓
File Access
    ↓
Result Display
```

---

## 🗂 Folder Structure

```
hostel-management-system/
│
├── main.c
│
├── headers/
│   ├── student.h
│   ├── admin.h
│   ├── room.h
│   ├── fee.h
│   └── complaint.h
│
├── data/
│   ├── students.dat
│   ├── admins.dat
│   ├── rooms.dat
│   ├── fees.dat
│   └── complaints.dat
│
├── docs/
│   ├── flowchart.png
│   ├── er-diagram.png
│   └── screenshots/
│
└── README.md
```

---

## 🧠 Menu System

### Main Menu

```
1. Admin Login
2. Student Login
3. Exit
```

### Admin Menu

```
1. Add Student
2. View Students
3. Assign Room
4. View Fees
5. View Complaints
6. Delete Student
7. Logout
```

### Student Menu

```
1. View My Details
2. Pay Fees
3. Submit Complaint
4. Logout
```

---

## 🛠 Task List

### Phase 1 – Core System

- Login system
- Student registration
- File handling

### Phase 2 – Hostel Logic

- Room allocation
- Fee management

### Phase 3 – Role Control

- Admin & student permissions
- Secure access

### Phase 4 – Complaints

- Student complaint system
- Admin viewing

### Phase 5 – Finalization

- Testing
- Screenshots
- Documentation

---

## 🔧 Recent Code Fixes

### 1. Fixed `editStudent` Function Bug (Data Loss Issue)

**Problem:** When editing a student's data, only the edited student's record was saved to the file, causing all other student records to be lost.

**Root Cause:** The original implementation used a temporary file (`temp.dat`) to rewrite records. However, it only wrote the edited record back to the temp file, instead of writing all records (with the edited one updated).

**Solution:** Refactored the function to use an in-memory array approach:
- Load all student records from `students.dat` into a `struct student` array (max 1000 students).
- Find the index of the student to edit by matching `studentId`.
- Allow editing of name, password, or room number via a menu loop.
- Write the entire updated array back to `students.dat`, ensuring no data loss.

**Code Changes in `helpers/student.c`:**
- Replaced file-based temp file logic with array loading and bulk writing.
- Added error handling for file not found and student not found.
- Improved reliability by avoiding partial file writes.

**Benefits:** 
- Eliminates data loss risk.
- Enables easy indexing for future enhancements (e.g., deleting students).
- Simplifies the code logic.

### 2. Fixed Name Input Issue (Spaces in Names)

**Problem:** When entering student names with spaces (e.g., "John Doe"), only the first part ("John") was captured; the rest was ignored or caused input buffer issues.

**Root Cause:** Used `scanf("%19s", name)`, which stops reading at the first whitespace character.

**Solution:** Changed to `scanf(" %[^\n]", name)`:
- The space before `%[^\n]` consumes any leftover whitespace/newlines from previous inputs.
- `%[^\n]` reads the entire input line until the newline character, allowing full names with spaces.

**Code Changes in `helpers/student.c`:**
- Updated both `addStudent` and `editStudent` functions for consistency.
- Applied to name fields only (passwords and IDs typically don't need spaces).

**Benefits:**
- Supports full names accurately.
- Prevents input buffer corruption in interactive menus.

### How to Test the Fixes

1. **Compile the Code:**
   ```
   gcc helpers/student.c -I headers -o student.exe
   ```

2. **Add Sample Data:**
   - Run the program and use `addStudent()` to add a few students with full names (e.g., "Alice Johnson").

3. **Test Editing:**
   - Use `editStudent(studentId)` to modify a student's name, password, or room number.
   - Verify that all other students' data remains intact by viewing all records.

4. **Verify Name Handling:**
   - Ensure names with spaces are stored and displayed correctly.

**Files Affected:** `helpers/student.c`

These fixes improve data integrity and user experience without altering the overall system architecture.
