#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "address_book.h"
#include "menu.h"

static int read_int(int *out)
{
    char buf[100];
    char *endptr;
    long value;

    if (fgets(buf, sizeof(buf), stdin) == NULL)
        return -1;

    value = strtol(buf, &endptr, 10);

    if (endptr == buf)
        return 0;

    while (*endptr == ' ' || *endptr == '\t')
        endptr++;

    if (*endptr != '\n' && *endptr != '\0')
        return 0;

    *out = (int)value;

    return 1;
}

static int read_str(char *buf, size_t size)
{
    if (fgets(buf, size, stdin) == NULL)
        return 0;

    if (strchr(buf, '\n') == NULL) {
        int c;

        while ((c = getchar()) != '\n' && c != EOF)
            ;
    } else {
        buf[strcspn(buf, "\n")] = '\0';
    }

    return 1;
}

static void display_addresses(const struct Address *head)
{
    print_list(head);
}

static void add_address(struct Address **head)
{
    char name[30];
    char surname[30];
    char email[50];
    char phone[20];

    printf("Enter name: ");
    if (!read_str(name, sizeof(name)))
        return;

    printf("Enter surname: ");
    if (!read_str(surname, sizeof(surname)))
        return;

    printf("Enter email: ");
    if (!read_str(email, sizeof(email)))
        return;

    printf("Enter phone: ");
    if (!read_str(phone, sizeof(phone)))
        return;

    printf("\n");

    struct Address *new_node =
        create_node(name, surname, email, phone);

    if (new_node == NULL) {
        printf("Failed to create address.\n");
        return;
    }

    add_to_list(head, new_node);

    printf("Address added successfully.\n");
}

static void add_address_at_position(struct Address **head)
{
    int position;
    char name[30];
    char surname[30];
    char email[50];
    char phone[20];

    printf("Enter position: ");

    if (read_int(&position) != 1 ||
        !is_valid_insert_position(*head, position)) {
        printf("Invalid position.\n");
        return;
    }

    printf("Enter name: ");
    if (!read_str(name, sizeof(name)))
        return;

    printf("Enter surname: ");
    if (!read_str(surname, sizeof(surname)))
        return;

    printf("Enter email: ");
    if (!read_str(email, sizeof(email)))
        return;

    printf("Enter phone: ");
    if (!read_str(phone, sizeof(phone)))
        return;

    printf("\n");

    struct Address *new_node =
        create_node(name, surname, email, phone);

    if (new_node == NULL) {
        printf("Failed to create address.\n");
        return;
    }

    if (add_at_position(head, new_node, position) != 0) {
        printf("Failed to add address at position %d.\n", position);
        free(new_node);
        return;
    }

    printf("Address added successfully at position %d.\n", position);
}

static void delete_address(struct Address **head)
{
    int position;

    printf("Enter position to delete: ");

    if (read_int(&position) != 1 ||
        !is_valid_position(*head, position)) {
        printf("Invalid position.\n");
        return;
    }

    printf("\n");

    if (delete_at_position(head, position) == 0)
        printf("Address at position %d deleted successfully.\n",
               position);
    else
        printf("Failed to delete address at position %d.\n",
               position);
}

static void delete_address_book(struct Address **head)
{
    if (*head == NULL) {
        printf("Address book is already empty.\n");
    } else {
        free_list(head);
        printf("Address book deleted successfully.\n");
    }
}

static void find_address_at_position(struct Address *head)
{
    int position;

    printf("Enter position: ");

    if (read_int(&position) != 1 ||
        !is_valid_position(head, position)) {
        printf("Invalid position.\n");
        return;
    }

    printf("\n");

    struct Address *address =
        find_by_position(head, position);

    if (address == NULL)
        printf("Address at position %d not found.\n", position);
    else
        print_address(address);
}

static void search_addresses(struct Address *head)
{
    int search_choice;
    char search_value[50];
    const char *field;

    printf("\nSearch by:\n");
    printf("1. Name\n");
    printf("2. Surname\n");
    printf("3. Email\n");
    printf("4. Phone\n");
    printf("Choose an option: ");

    if (read_int(&search_choice) != 1) {
        printf("Invalid search option.\n");
        return;
    }

    if (search_choice == 1)
        field = "name";
    else if (search_choice == 2)
        field = "surname";
    else if (search_choice == 3)
        field = "email";
    else if (search_choice == 4)
        field = "phone";
    else {
        printf("Invalid search option.\n");
        return;
    }

    printf("Enter %s: ", field);

    if (!read_str(search_value, sizeof(search_value)))
        return;

    printf("\n");

    int found = find_addresses(head, field, search_value);

    if (!found)
        printf("Address not found.\n");
}

void run_menu(struct Address **head,
              const volatile sig_atomic_t *interrupted)
{
    int choice;
    int running = 1;

    while (running && !*interrupted) {
        printf("\n===== ADDRESS BOOK =====\n");
        printf("1. Display all records\n");
        printf("2. Add new address\n");
        printf("3. Add new address at position\n");
        printf("4. Delete address by position\n");
        printf("5. Delete whole address book\n");
        printf("6. Find address by position\n");
        printf("7. Find addresses by name, surname, email or phone number\n");
        printf("8. Exit\n");
        printf("\nChoose an option: ");

        int status = read_int(&choice);

        if (status == -1) {
            printf("\nNo more input, exiting.\n");
            break;
        }

        if (status == 0) {
            printf("\nInvalid option, please enter a number\n");
            continue;
        }

        printf("\n");

        switch (choice) {
        case 1:
            display_addresses(*head);
            break;

        case 2:
            add_address(head);
            break;

        case 3:
            add_address_at_position(head);
            break;

        case 4:
            delete_address(head);
            break;

        case 5:
            delete_address_book(head);
            break;

        case 6:
            find_address_at_position(*head);
            break;

        case 7:
            search_addresses(*head);
            break;

        case 8:
            running = 0;
            break;

        default:
            printf("Invalid option.\n");
            break;
        }
    }
}