#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <signal.h>
#include "address_book.h"

static volatile sig_atomic_t interrupted = 0;

static void handle_signal(int signal)
{
    (void)signal;
    interrupted = 1;
}

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

int main(void)
{
    struct sigaction sa;

    sa.sa_handler = handle_signal;
    sigemptyset(&sa.sa_mask);
    sa.sa_flags = 0;

    sigaction(SIGINT, &sa, NULL);
    sigaction(SIGQUIT, &sa, NULL);
    sigaction(SIGTERM, &sa, NULL);

    struct Address *head = NULL;
    
    int result = load_from_csv(&head);

    if (result == 1) {
        printf("addresses.csv not found. Starting with an empty address book.\n");
    } else if (result == -1) {
        printf("Failed to load addresses.csv. Starting with an empty address book.\n");
    }
    int choice;
    int running = 1;

    while (running && !interrupted) {
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
            print_list(head);
            break;

        case 2: {
            char name[30];
            char surname[30];
            char email[50];
            char phone[20];

            printf("Enter name: ");
            if (!read_str(name, sizeof(name))) {
                printf("\nNo more input, exiting.\n");
                running = 0;
                break;
            }

            printf("Enter surname: ");
            if (!read_str(surname, sizeof(surname))) {
                printf("\nNo more input, exiting.\n");
                running = 0;
                break;
            }

            printf("Enter email: ");
            if (!read_str(email, sizeof(email))) {
                printf("\nNo more input, exiting.\n");
                running = 0;
                break;
            }

            printf("Enter phone: ");
            if (!read_str(phone, sizeof(phone))) {
                printf("\nNo more input, exiting.\n");
                running = 0;
                break;
            }

            printf("\n");

            struct Address *new_node = create_node(name, surname, email, phone);

            if (new_node == NULL) {
                printf("Failed to create address.\n");
                break;
            }

            add_to_list(&head, new_node);
            printf("Address added successfully.\n");

            break;
        }

        case 3: {
            int position;
            char name[30];
            char surname[30];
            char email[50];
            char phone[20];

            printf("Enter position: ");

            if (read_int(&position) != 1 || !is_valid_position(head, position)) {
                printf("Invalid position.\n");
                break;
            }

            if (position < 1) {
                printf("Invalid position.\n");
                break;
            }

            if (position > 1) {
                struct Address *current = head;

                for (int i = 1; i < position - 1 && current!= NULL; i++)
                current = current->next;

                if (current == NULL) {
                    printf("Invalid position.\n");
                    break;
                }
            }

            printf("Enter name: ");
            if (!read_str(name, sizeof(name))) {
                printf("\nNo more input, exiting.\n");
                running = 0;
                break;
            }
 
            printf("Enter surname: ");
            if (!read_str(surname, sizeof(surname))) {
                printf("\nNo more input, exiting.\n");
                running = 0;
                break;
            }
 
            printf("Enter email: ");
            if (!read_str(email, sizeof(email))) {
                printf("\nNo more input, exiting.\n");
                running = 0;
                break;
            }
 
            printf("Enter phone: ");
            if (!read_str(phone, sizeof(phone))) {
                printf("\nNo more input, exiting.\n");
                running = 0;
                break;
            }

            printf("\n");

            struct Address *new_node = create_node(name, surname, email, phone);

            if (new_node == NULL) {
                printf("Failed to create address.\n");
                break;
            }

            if (add_at_position(&head, new_node, position) != 0) {
                printf("Failed to add address at position %d.\n", position);
                free(new_node);
                break;
            }

            printf("Address added successfully at position %d.\n", position);

            break;
        }

        case 4: {
            int position;

            printf("Enter position to delete: ");
            if (read_int(&position) != 1 || !is_valid_position(head, position)) {
                printf("Invalid position.\n");
                break;
            }

            printf("\n");

            if (delete_at_position(&head, position) == 0)
                printf("Address at position %d deleted successfully.\n",
                        position);
            else
                printf("Failed to delete address at position %d.\n", position);

            break;
        }

        case 5:
            if (head == NULL)
                printf("Address book is already empty.\n");
            else {
                free_list(&head);
                printf("Address book deleted successfully.\n");
            }

            break;

        case 6: {
            int position;

            printf("Enter position: ");
            
            if (read_int(&position) != 1 || !is_valid_position(head, position)) {
                printf("Invalid position.\n");
                break;
            }

            printf("\n");

            struct Address *address = find_by_position(head, position);

            if (address == NULL)
                printf("Address at position %d not found.\n", position);
            else
                print_address(address);

            break;
        }

        case 7: {
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
                break;
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
                break;
            }

            printf("Enter %s: ", field);
            if (!read_str(search_value, sizeof(search_value))) {
                printf("\nNo more input, exiting.\n");
                running = 0;
                break;
            }

            printf("\n");

            find_addresses(head, field, search_value);

            break;
        }

        case 8:
            running = 0;
            break;

        default:
            printf("Invalid option.\n");
            break;
        }
    }

    if (interrupted)
        printf("\nSignal received. Exiting\n");

    free_list(&head);

    return 0;
}