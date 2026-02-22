# ShoppingApp — README

> Command-line C++ Shopping Application (No GUI)  
> Project structure and implementation used for coursework in Data Structures and Algorithms
> This README provides: overview, build/run instructions, file formats, API summary, and troubleshooting.

---

## Table of contents
1. [Project overview](#project-overview)  
2. [Repository layout](#repository-layout)  
3. [Build & run instructions (CMake)](#build--run-instructions-cmake)  
4. [Data file formats](#data-file-formats)  
5. [Runtime behavior & assumptions](#runtime-behavior--assumptions)  
6. [Key code modules & API summary](#key-code-modules--api-summary)  
7. [Configuration points you can change quickly](#configuration-points-you-can-change-quickly)  
8. [Troubleshooting & common fixes](#troubleshooting--common-fixes)  
9. [Planned/optional enhancements](#plannedoptional-enhancements)  
10. [License & credits](#license--credits)

---

## Project overview

ShoppingApp is a terminal-based shopping application that supports:
- user registration and login (users can be buyers and/or sellers),
- seller operations (add items, edit stock, view low-stock),
- buyer operations (view products, add-to-cart, edit cart, check out),
- admin reporting (show users, show sellers, sum sales in a date range),
- persistent storage in **text files** inside `..data/` (per project requirement).

The program is intentionally beginner-friendly: simple, explicit C++ constructs, limited STL usage, and clear separation of responsibilities.

---

## Repository layout


```
ShoppingApp/
├── CMakeLists.txt
├── main.cpp
├── data/
│   ├── carts/                # per-user cart files
│   ├── Items.txt             # saved items
│   ├── Transactions.txt      # saved transactions
│   └── Users.txt             # saved users
├── include/
│   ├── shopping_app.h
│   ├── menu/
│   │   ├── main_menu.h
│   │   ├── admin/
│   │   │   ├── admin_menu.h
│   │   │   └── actions/
│   │   │       └── admin_actions.h
│   │   └── user/
│   │       ├── buyer_menu.h
│   │       ├── seller_menu.h
│   │       ├── user_menu.h
│   │       └── actions/
│   │           ├── buyer_actions.h
│   │           ├── seller_actions.h
│   │           └── user_actions.h
│   ├── models/
│   │   ├── cart.h
│   │   ├── item.h
│   │   ├── transaction.h
│   │   └── user.h
│   ├── services/
│   │   └── file_handling.h
│   └── utils/
│       └── utils.h
└── src/
├── (corresponding .cpp files)

````

---

## Build & run instructions (CMake)

**Requirements**:
- A C++17-compatible compiler (g++, clang, or MSVC).
- CMake (3.x or newer).

**CMakeLists.txt**:

```bash
cmake_minimum_required(VERSION 4.1)
project(ShoppingAppFinal)

set(CMAKE_CXX_STANDARD 14)

include_directories(include)
include_directories(include/menu)
include_directories(include/menu/admin)
include_directories(include/menu/admin/actions)
include_directories(include/menu/user)
include_directories(include/menu/user/actions)
include_directories(include/models)
include_directories(include/services)
include_directories(include/utils)

add_executable(ShoppingAppFinal
        include/menu/admin/actions/admin_actions.h
        include/menu/admin/admin_menu.h
        include/menu/user/actions/buyer_actions.h
        include/menu/user/actions/seller_actions.h
        include/menu/user/actions/user_actions.h
        include/menu/user/buyer_menu.h
        include/menu/user/seller_menu.h
        include/menu/user/user_menu.h
        include/menu/main_menu.h
        include/models/cart.h
        include/models/item.h
        include/models/transaction.h
        include/models/user.h
        include/services/file_handling.h
        include/utils/utils.h
        include/shopping_app.h
        src/menu/admin/actions/admin_actions.cpp
        src/menu/admin/admin_menu.cpp
        src/menu/user/actions/buyer_actions.cpp
        src/menu/user/actions/seller_actions.cpp
        src/menu/user/actions/user_actions.cpp
        src/menu/user/buyer_menu.cpp
        src/menu/user/seller_menu.cpp
        src/menu/user/user_menu.cpp
        src/menu/main_menu.cpp
        src/models/cart.cpp
        src/models/item.cpp
        src/models/transaction.cpp
        src/models/user.cpp
        src/services/file_handling.cpp
        src/utils/utils.cpp
        src/shopping_app.cpp
        main.cpp)

```

**Notes**:

* The program expects `../data/` relative to the executable's location (i.e., assumes the executable is in `build/` and `data/` is in the project root). `main.cpp` attempts to create `data/` and `data/carts/` on startup (best-effort).
* Run the executable from the `build/` directory to ensure paths resolve correctly.

---

## Data file formats

**All persistent files are *text* files** (per your requirement). Keep exact formats if you intend to edit them manually.

### `data/Users.txt`

One user block per user:

```
<userID> <password>
<name>
<address>
<contact number>

<next user block...>
```

Example:

```
1001 Secur3Pass
James Alexander
421 Maple Avenue, Quezon City
9171234567

1002 BlueSky88
Maria Santos
15B Riverside Drive, Makati
9189876543

(eof)
```

### `data/Items.txt`

One product block per product:

```
<productID> <sellerID>
<item name>
<category>
<description>
<quantity> <unit price>

<next item...>
```

Example:

```
5001 1001
Mechanical Keyboard
Electronics
Compact mechanical keyboard, blue switches
15 2500.00

(eof)
```

### `data/Transactions.txt`

Human-readable appended transaction blocks. Format is implementation-specific but consistent with the append/load functions. Each transaction records:

* date (month/day/year),
* buyer ID, seller ID,
* items with productID, itemName, quantity, unitPrice,
* transaction total.

### `data/carts/<userId>.bag` (per-user cart)

A simple, student-decided text format. The implementation uses lines with cart item data such as:

```
<productID> <sellerID> <quantity> <unitPrice> <itemName...>
```

The cart files use the `.bag` extension by default. If you want `.txt` instead, change the file extension where the cart path is constructed (see configuration points below).

---

## Runtime behavior & assumptions

* On startup, `main` tries to load `../data/Users.txt`, `../data/Items.txt`, and `../data/Transactions.txt` (relative to executable in `build/`) if they exist. If files are missing, program starts with empty collections.
* `main` ensures `../data/` and `../data/carts/` exist (best-effort); if creation fails, saves may fail later.
* Cart load/save: carts are loaded from/saved to `../data/carts/` when a user enters/exits the Buy Menu.
* Limits enforced by the app:

    * Max 100 users total.
    * Max 20 items per seller.
    * Max 10 distinct items in a cart.
    * Max 5 items per transaction.
* Field-length limits (spec):

    * password ≤ 10 chars
    * name ≤ 20 chars
    * address ≤ 30 chars
    * itemName ≤ 20 chars
    * category ≤ 15 chars
    * description ≤ 30 chars
      These are documented but some checks are enforced at UI level; you can strengthen validation in setters or UI prompts.

---

## Key code modules & API summary

This summary lists core classes and the main public functions you will interact with in the code.

### `ShoppingApp` (application state)

* `bool LoadUsersFromFile(const std::string& path)`
* `bool SaveUsersToFile(const std::string& path)`
* `bool LoadItemsFromFile(const std::string& path)`
* `bool SaveItemsToFile(const std::string& path)`
* `bool LoadTransactionsFromFile(const std::string& path)`
* `bool SaveTransactionsToFile(const std::string& path)`
* `const std::vector<User>& GetUsers() const`
* `std::vector<Item>& GetItems()`
* `const std::vector<Transaction>& GetTransactions() const`
* `bool RegisterUser(const User& user)` — enforces unique userID and max-100 rule.
* `bool AddTransaction(const Transaction& t)` — validates and applies transaction (updates stock).

### Models

* `User` — getters/setters for userID, password, name, address, contact.
* `Item` — getters/setters for productID, itemName, category, description, quantity, unitPrice, sellerID.
* `Cart` / `CartItem` — add/remove items, update quantities, enforce 10 distinct items.
* `Transaction`, `TransactionItem`, `Date` — construct transactions; `Transaction::AddItem` enforces max 5 items.

### Services

* `FileHandling` (static helpers)

    * `LoadUsersText`, `SaveUsersText`
    * `LoadItemsText`, `SaveItemsText`
    * `AppendTransactionText`, `LoadTransactionsText`
    * `LoadCartText`, `SaveCartText`

### Utils

* `Utils::LeftJustify`, `Utils::RightJustify` — used for table printing.
* `Utils::PrintItemsTable(const std::vector<Item>& items)` — prints dynamic-width table.
* `Utils::ContainsIgnoreCase(const std::string&, const std::string&)` — case-insensitive substring search.

### Menus & Actions

* `MainMenu::Show()` — top-level menu (Register, User Menu, Admin Menu, Exit).
* `UserMenu::Show()` — login & user menu; greets user with `Welcome, <name>!`.
* `BuyerMenu::Show()` — buy features: viewing, searching, add-to-cart, edit cart, checkout.
* `SellerMenu::Show()` — seller features: add item, edit stock, show products.
* `AdminMenu::Show()` — admin reports; requires admin password (`H3LLo?` default).
* `AdminActions` — table printing & reports (ShowAllUsers, ShowAllSellers, ShowTotalSalesInDuration, ShowSellersSales, ShowShopaholics).

---

## Configuration points you can change quickly

* **Cart filename extension & path**: `BuyerMenu::Show()` constructs cart file path like:

  ```cpp
  std::string cartPath = "../data/carts/" + std::to_string(userId) + ".bag";
  ```

  Change `".bag"` to `".txt"` if desired.

* **Admin password**: default `"H3LLo?"` is set in `AdminActions` constructor. Update there to change admin password.

* **Column spacing for printed tables**:

    * `admin_actions.cpp` contains `static const size_t COLUMN_SPACING = <value>` for admin tables.
    * `utils.cpp` contains `static const size_t COLUMN_SPACING = <value>` for item tables.
      Adjust these to control spaces between columns.

* **Directory paths**: `main.cpp` creates `../data/` and `../data/carts/` (relative to executable). If you want to store data elsewhere, update paths in `main.cpp` and file handling calls.

---

## Troubleshooting & common fixes

**Q: `Registration failed (duplicate ID or user limit)` after starting with empty files**
A: Check that `data/Users.txt` is truly empty and you're running the program with the correct working directory. The loader prints loaded user IDs on startup if enabled in `main.cpp` debug prints. Make sure you are editing the same `Users.txt` file that the program reads.

**Q: `Type std::ofstream is incomplete` compile error**
A: Usually caused by missing `#include <fstream>` in a source file that uses `std::ofstream`. Ensure all file I/O sources include `<fstream>` and `<sstream>` where needed. Also check that you didn't accidentally forward-declare `std::ofstream` somewhere.

**Q: Saving fails because path does not exist**
A: Ensure `data/` and `data/carts/` exist. `main.cpp` attempts to create them at startup; if it fails (permission issue), create the folders manually.

**Q: Tables look misaligned or wrap**
A: Terminal width may be smaller than the table width. Either increase terminal width, reduce `COLUMN_SPACING`, or truncate very long address/name strings before printing.

**Q: Cart or transaction behaviors inconsistent**
A: Check `data/carts/<userId>.bag` and `data/Transactions.txt` formats — malformed lines may cause the loader to skip entries. The loader is resilient but not infallible; fix corrupted entries manually or remove them.

---

## Planned / optional enhancements (suggestions)

* Add Admin actions to delete users, items, or transactions (with optional cascade).
* Strengthen input validation (field lengths, contact format such as `09XXXXXXXXX`, date validation).
* Provide a small test dataset generator or a sample `data/` folder with example files.
* Add unit tests for `Cart`, `Transaction`, `FileHandling` parsing.
* Replace text transaction format with JSON or CSV for easier parsing (requires changing `FileHandling` implementation).
* Add confirmation prompts for destructive actions (deletes) and backups when saving.

---

## License & credits

* Implementation and README authored for a student project. Use and modify freely for coursework.
* No third-party libraries required. Standard C++ library only.