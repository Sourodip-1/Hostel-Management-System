# Hostel Management System - Project Index

## Project Overview
Menu-driven C application for hostel management with role-based authentication (Admin/Student), file handling, and secure operations.

## File Structure
```
Hostel-Management-System/
├── main.c                 # Main entry point and menus
├── README.md              # Project documentation
├── TASKS.md               # Development tasks
├── build_error.txt        # Build logs
├── data/                  # Data files (.dat)
├── headers/               # Header files
│   ├── admin.h            # Admin structures/functions
│   ├── complaint.h        # Complaint structures/functions
│   ├── fee.h              # Fee structures/functions
│   ├── room.h             # Room structures/functions
│   ├── security.h         # Password hashing
│   ├── student.h          # Student structures/functions
│   └── ui.h               # UI utilities
└── helpers/               # Implementations
    ├── admin.c            # Admin operations
    ├── complaint.c        # Complaint handling
    ├── fee.c              # Fee management
    ├── room.c             # Room allocation
    ├── security.c         # Security functions
    ├── student.c          # Student operations
    └── ui.c               # UI helpers
```

## File Descriptions

### Core Files
- **main.c**: Entry point, login, menus, authentication routing
- **README.md**: Documentation, features, user roles
- **TASKS.md**: Development progress tracking

### Headers (headers/)
- **admin.h**: Admin struct (ID, name, password) and CRUD functions
- **complaint.h**: Complaint struct (ID, student, room, date, desc, status) and management functions
- **fee.h**: Fee struct (student ID, amount, payment status) and payment functions
- **room.h**: Room struct (number, capacity, type, charges, occupancy) and allocation functions
- **security.h**: Password hashing utilities
- **student.h**: Student struct (ID, name, password, room) and CRUD functions
- **ui.h**: ANSI colors and UI helper functions

### Implementations (helpers/)
- **admin.c**: Admin CRUD with file persistence
- **complaint.c**: Complaint submission/viewing with file ops
- **fee.c**: Fee calculation and payment tracking
- **room.c**: Room management and assignment logic
- **security.c**: Password hashing implementation
- **student.c**: Student CRUD and authentication
- **ui.c**: Console UI enhancements

### Data
- **data/**: Binary .dat files for persistent storage

## Key Features
- Role-based access (Admin/Student)
- Secure login with hashing
- File-based persistence
- Console menus
- Room allocation
- Fee tracking
- Complaint system
- Search/view functions

## Development Phases
1. Core System (menus, login, files)
2. Hostel Logic (rooms, fees, structures)
3. Role Control (permissions, security)
4. Complaints (submission/viewing)
5. Testing & Documentation