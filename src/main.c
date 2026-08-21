#include <stdio.h>
#include <stdlib.h>
#include "address_book.h"

int main(void)
{
    struct Address *head = NULL;

    if (load_from_csv(&head) != 0) {
        printf("Failed to load addresses.csv\n");
    }

    int choice;

    while (1) {
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

        scanf("%d", &choice);

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
            scanf("%29s", name);

            printf("Enter surname: ");
            scanf("%29s", surname);

            printf("Enter email: ");
            scanf("%49s", email);

            printf("Enter phone: ");
            scanf("%19s", phone);

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
            scanf("%d", &position);

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
            scanf("%29s", name);

            printf("Enter surname: ");
            scanf("%29s", surname);

            printf("Enter email: ");
            scanf("%49s", email);

            printf("Enter phone: ");
            scanf("%19s", phone);

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
            scanf("%d", &position);

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
            scanf("%d", &position);

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

            scanf("%d", &search_choice);

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
            scanf("%49s", search_value);

            printf("\n");

            find_addresses(head, field, search_value);

            break;
        }

        case 8:
            free_list(&head);
            return 0;

        default:
            printf("Invalid option.\n");
            break;
        }
    }
}