# 🩺 Calcare – Doctor-Patient Record System (C++)

**Calcare** is a simple C++ console-based program that manages a doctor-patient record system. It uses a **singly linked list** to maintain a sorted list of users and stores each user's data in a dedicated file. It supports two types of users: **Doctor (Admin)** and **Patient (Viewer)**.

---

##  Features

###  Doctor Login
- Add a new user (name + ID) – ensures unique ID
- Search a user by ID and view their file
- Display all users in sorted order by ID
- Edit user file in **Notepad**
- Delete a user and remove their file

###  Patient Access
- Enter ID to view associated file

###  File System
- Stores all users in `users.txt`
- Each user has their own file: `<id>.txt`

---

##  Data Structure Used
- **Singly Linked List**
  - Sorted insert based on ID
  - Search, display, delete operations

---

## 🗂 File Structure

```bash
Calcare/
│
├── main.cpp                # Complete source code
├── users.txt               # Stores all users (name and ID)
├── <id>.txt                # Individual file for each user
````

---

## 🧑‍💻 How to Use

1. **Compile** the program:

   ```bash
   g++ main.cpp -o calcare
   ```

2. **Run** the program:

   ```bash
   ./calcare    # or calcare.exe on Windows
   ```

3. Choose:

   * `1` for Doctor login
   * `2` for Patient access
   * `3` to Exit

---

## ✨ Sample Output

```text
                   Calcare

                 1-Doctor Login
                 2-Patient Access
                   3-Exit
            Your choice: _
```

---

## 🧹 Notes

* Only supports **plain text** file editing via Notepad.
* Automatically creates files if they don’t exist.
* Validates duplicate IDs on insert.

---

## 🛠 Built With

* **C++**
* **File I/O**
* **Linked List**

---

## 📄 License

This project is open-source and free to use for educational or learning purposes.

---

## 👨‍⚕️ Developed by

Sameer Ahmed – 2024

