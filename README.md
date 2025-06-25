# Hospital Management System (C++ OOP)

## Overview
This is a console-based Hospital Management System implemented in C++ using Object-Oriented Programming (OOP) principles. The system allows patients, doctors, and administrators to manage and view hospital data interactively.

## Features
- **OOP Design:** Uses encapsulation, inheritance, and polymorphism.
- **Role-based Access:** Separate menus for patients, doctors (password: `doctor`), and admin (password: `admin`).
- **Patient & Doctor Management:** Register, search, and display patients and doctors.
- **Consultation Management:** Schedule, view, and filter consultations by date, patient, or doctor.
- **Authentication:** Password protection for doctor and admin roles.
- **Input Validation:** Robust input handling for menu choices and IDs.

## OOP Concepts Demonstrated
- **Encapsulation:** Data and methods grouped in classes (`Person`, `Patient`, `Doctor`, `Consultation`, `Hospital`).
- **Inheritance:** `Patient` and `Doctor` inherit from `Person`.
- **Polymorphism:** Virtual methods for displaying information.
- **Abstraction:** Users interact with high-level operations without knowing internal details.

## How to Build and Run
1. **Clone or Download the Repository**
2. **Open a Terminal and Navigate to the Project Directory**
3. **Compile:**
   ```sh
   g++ main.cpp -o hospital
   # or
   clang++ main.cpp -o hospital
   ```
4. **Run:**
   ```sh
   ./hospital
   ```

## Usage Instructions
- **Start the program** and choose your role: Patient, Doctor, or Admin.
- **Patients/Doctors:**
  - If registered, enter your ID to view your consultations (upcoming, past, or by date).
  - If not registered, contact the admin.
- **Admin:**
  - Password: `admin`
  - Add patients/doctors, schedule consultations, search by name, and view consultations by date.
- **Doctor:**
  - Password: `doctor`
  - View your consultations after logging in with your ID.

## Example Credentials
- **Admin Password:** `admin`
- **Doctor Password:** `doctor`
- **Patient/Doctor IDs:** Assigned automatically when registered by admin. Use the displayed ID for login.

## Example Menu
```
--- Welcome to Hospital Management System ---
1. Patient
2. Doctor
3. Admin/Other
4. Exit
Enter your role: 
```

## Notes
- All data is stored in memory (no file/database persistence).
- For demonstration, register patients and doctors via the admin menu before logging in as them.

---
Feel free to modify or extend the system for your needs! 