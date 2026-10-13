# C Address Book

A command-line address book written in C. This project demonstrates modular programming, linked lists, CSV file handling, and automated compilation with GNU Make.

## Features

- Store contact details, including names, email addresses, and phone numbers.
- Manage contacts using a singly linked list.
- Add, insert, and delete contacts.
- Search for contacts by a selected field and value.
- Display contacts and individual contact details.
- Load initial contact data from a CSV file.
- Handle termination signals and release allocated memory.

## Technologies

- C
- Linux and POSIX APIs
- GNU Make
- Singly linked lists
- CSV file handling
- Dynamic memory allocation
- POSIX signal handling

## Project Structure

```text
address_book/
├── Makefile
├── addresses.csv
├── include/
│   ├── address_book.h
│   ├── csv.h
│   └── menu.h
└── src/
    ├── address_book.c
    ├── csv.c
    ├── main.c
    └── menu.c
```

- `src/` — application logic, menu, CSV handling, and program entry point.
- `include/` — header files shared between application modules.
- `addresses.csv` — example contact data.
- `Makefile` — coordinates application compilation.

## Requirements

- Linux or a compatible Unix-like environment.
- GCC or another C compiler.
- GNU Make.

## Build

From the project root, compile the application:

```bash
make
```

## Run

The application attempts to load contacts from `$HOME/addresses.csv`.

Copy the example CSV file to your home directory if needed:

```bash
cp addresses.csv "$HOME/addresses.csv"
```

Start the application from the project root:

```bash
./address_book
```

If the contact file cannot be loaded, the application may start with an empty address list.

## Memory Management

Contact records are stored in dynamically allocated linked-list nodes. The application releases the list before exiting.

## Learning Outcomes

This project provides practical experience with:

- Writing modular C programs.
- Working with structs, pointers, and dynamic memory.
- Implementing and manipulating a linked list.
- Organizing declarations in header files.
- Automating compilation with Makefiles.
- Reading structured data from CSV files.
- Handling POSIX termination signals.
- Managing source code with Git.
