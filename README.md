# 🧾 Inventory Management System (C – Linked List)

This is a **menu-driven Inventory Management System written in C**, designed using **singly linked lists** and **file handling**.
It allows users to manage items efficiently by performing add, delete, update, search, save, and load operations from the terminal.

---

## ✨ Features

- ➕ Add new inventory items
- ❌ Delete existing items
- ✏️ Update item quantity and rate
- 🔍 Search item by name
- 📃 Display full inventory list
- 💰 Calculate total inventory amount
- 📂 Load inventory data from a text file
- 💾 Save inventory report to a separate file
- 🧠 Automatic amount calculation (`Quantity × Rate`)
- 🛡️ Safe memory handling using dynamic allocation

---

## 🧠 Data Structure Used

- Singly Linked List
- Each node contains:
  - Item Name
  - Quantity
  - Unit
  - Rate
  - Amount (Quantity × Rate)

---

## 📂 File Handling Details

### 📥 Load File

- Reads item data from a text file
- Clears existing memory before loading
- Prevents memory leaks

### 📤 Save File

- Saves inventory data in readable format
- Includes item name, quantity, unit, rate, and amount

---

## 🧪 Menu Options

1. Add item
2. Delete item
3. Print item list
4. Other options
   - Total inventory amount
   - Search item by name
5. Update item
6. Load data from file
7. Save data to file
   Any other key exits the program

---

## ⚠️ Input Validation

- Quantity and Rate must be non-negative
- Duplicate item names are not allowed
- Proper input handling using `fgets()` and buffer cleanup

---
