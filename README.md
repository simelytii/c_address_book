# C Address Book

A command-line address book written in C. This project demonstrates
linked lists, modular program design, Makefiles, CSV file handling,
signal handling, and dynamic shared library integration.

## Features

- Store contact details: name, surname, email, and phone number.
- Manage contacts using a singly linked list.
- Add contacts to the list.
- Insert and delete contacts at specified positions.
- Find contacts by a selected field and value.
- Display contacts and individual contact details.
- Load initial contact data from a CSV file.
- Handle termination signals and release allocated memory.
- Build linked-list functionality as a shared library.

## Technologies

- C
- Linux and POSIX APIs
- GNU Make
- Dynamic shared libraries (`.so`)
- CSV file handling
- Signal handling with `sigaction`
- Pointers and dynamic memory allocation

## Project Structure

```text
address_book/
├── Makefile
├── addresses.csv
├── include/
│   ├── address_book.h
│   ├── csv.h
│   └── menu.h
├── lib/
│   ├── linked_list.c
│   ├── linked_list.h
│   └── Makefile
└── src/
    ├── address_book.c
    ├── csv.c
    ├── main.c
    ├── menu.c
    └── Makefile
```

- `src/` — application implementation, menu, CSV handling, and entry point.
- `include/` — application header files.
- `lib/` — linked-list implementation and shared-library build rules.
- `addresses.csv` — example contact data.
- `Makefile` — coordinates the build of the library and application.

## Requirements

- Linux or a compatible Unix-like environment.
- A C compiler, such as GCC.
- GNU Make.

## Build

From the project root, build the shared library and application:

```bash
make
```

The build creates the linked-list shared library:

```text
lib/liblinked_list.so
```

It also builds the application executable:

```text
address_book
```

To remove generated build files, run:

```bash
make clean
```

## Run

The application attempts to load contacts from:

```text
$HOME/addresses.csv
```

To use the repository's example CSV file, copy it to your home directory:

```bash
cp addresses.csv "$HOME/addresses.csv"
```

Run the application from the project root:

```bash
./address_book
```

If the contact file is missing or cannot be loaded, the application
can start with an empty address list.

## Shared Library

The linked-list module is compiled with position-independent code
using `-fPIC` and linked into `liblinked_list.so` with the `-shared`
option.

The application links against the shared library during compilation.
Its runtime library search path is configured relative to the executable
so that the library can be found in the project's `lib/` directory.

## Memory Management

Contact records are represented by dynamically allocated linked-list
nodes. The application releases the allocated list before exiting.

## Learning Outcomes

This project provides practical experience with:

- Structs, pointers, and dynamic memory allocation in C.
- Implementing and manipulating a singly linked list.
- Separating application logic into modules and header files.
- Writing and using Makefiles.
- Building and linking a shared library.
- Reading structured data from a CSV file.
- Handling POSIX termination signals.
- Organizing a small C project for version control and portfolio use.
