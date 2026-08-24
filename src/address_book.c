#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>
#include "address_book.h"

/* Copies src into dest, never writing more than dest_size bytes and
 * always leaving dest null-terminated (truncates if src is too long).
 * Prevents heap buffer overflow when loading an oversized field from 
 * the CSV. */
static void safe_copy(char *dest, size_t dest_size, const char *src)
{
    strncpy(dest, src, dest_size - 1);
    dest[dest_size - 1] = '\0';
}

struct Address *create_node(const char *name,
                            const char *surname,
                            const char *email,
                            const char *phone)
{
    struct Address *new_node = malloc(sizeof(struct Address));

    if (new_node == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
    } else {
        safe_copy(new_node->name, sizeof(new_node->name), name);
        safe_copy(new_node->surname, sizeof(new_node->surname), surname);
        safe_copy(new_node->email, sizeof(new_node->email), email);
        safe_copy(new_node->phone, sizeof(new_node->phone), phone);
        new_node->next = NULL;
    }

    return new_node;
}

void add_to_list(struct Address **head, struct Address *new_node)
{
    if (*head == NULL) {
        *head = new_node;
    } else {
        struct Address *current = *head;

        while (current->next != NULL) {
            current = current->next;
        }
        current->next = new_node;
    }
}

void free_list(struct Address **head)
{
    struct Address *current = *head;

    while (current != NULL) {
        struct Address *next = current->next;

        free(current);

        current = next;
    }

    *head = NULL;
}

void print_list(const struct Address *head)
{
    const struct Address *current = head;

    if (current == NULL) {
        printf("Address book is empty.\n");
        return;
    }

    while (current != NULL) {
        print_address(current);
        current = current->next;
    }
}

int add_at_position(struct Address **head,
                     struct Address *new_node,
                     int position)
{
    if (new_node == NULL)
        return -1;

    if (position < 1)
        return -1;

    if (position == 1) {
        new_node->next = *head;
        *head = new_node;
        return 0;
    }

    struct Address *current = *head;

    for (int i = 1; i < position - 1 && current != NULL; i++)
        current = current->next;

    if (current == NULL)
        return -1;

    new_node->next = current->next;
    current->next = new_node;

    return 0;
}

int delete_at_position(struct Address **head, int position)
{
    if (*head == NULL)
        return -1;

    if (position < 1)
        return -1;

    if (position == 1) {
        struct Address *temp = *head;

        *head = (*head)->next;

        free(temp);

        return 0;
    }

    struct Address *current = *head;

    for (int i = 1; i < position - 1 && current != NULL; i++)
        current = current->next;

    if (current == NULL || current->next == NULL)
        return -1;

    struct Address *temp = current->next;

    current->next = temp->next;

    free(temp);

    return 0;
}

struct Address *find_by_position(struct Address *head, int position)
{
    if (head == NULL || position < 1)
        return NULL;

    struct Address *current = head;

    for (int i = 1; i < position; i++) {
        if (current->next == NULL)
            return NULL;

        current = current->next;
    }

    return current;
}

void find_addresses(struct Address *head, const char *field, const char *value)
{
    struct Address *current = head;
    int found = 0;

    while (current != NULL) {
        if (strcasecmp(field, "name") == 0 &&
            strcasecmp(current->name, value) == 0) {
            print_address(current);
            found = 1;
        } else if (strcasecmp(field, "surname") == 0 &&
                   strcasecmp(current->surname, value) == 0) {
            print_address(current);
            found = 1;
        } else if (strcasecmp(field, "email") == 0 &&
                   strcasecmp(current->email, value) == 0) {
            print_address(current);
            found = 1;
        } else if (strcasecmp(field, "phone") == 0 &&
                   strcasecmp(current->phone, value) == 0) {
            print_address(current);
            found = 1;
        }
        current = current->next;
    }
    if (!found)
        printf("Address not found.\n");
}

void print_address(const struct Address *address)
{
    printf("Name: %s\n", address->name);
    printf("Surname: %s\n", address->surname);
    printf("Email: %s\n", address->email);
    printf("Phone: %s\n", address->phone);
    printf("\n");
}

int load_from_csv(struct Address **head)
{
    char *home = getenv("HOME");

    if (home == NULL)
        return -1;

    char path[256];

    snprintf(path, sizeof(path), "%s/addresses.csv", home);

    FILE *file = fopen(path, "r");

    if (file == NULL)
        return 1;

    char line[256];

    while (fgets(line, sizeof(line), file) != NULL) {
        char *name = strtok(line, ",");
        char *surname = strtok(NULL, ",");
        char *email = strtok(NULL, ",");
        char *phone = strtok(NULL, ",\n");

        if (name == NULL || surname == NULL ||
            email == NULL || phone == NULL)
            continue;

        struct Address *new_node = create_node(name, surname, email, phone);

        if (new_node == NULL) {
            fclose(file);
            return -1;
        }

        add_to_list(head, new_node);
    }

    fclose(file);

    return 0;
}

int is_valid_position(const struct Address *head, int position)
{
    if (head == NULL || position < 1)
        return 0;

    const struct Address *current = head;

    for (int i = 1; i < position; i++) {
        if (current->next == NULL)
            return 0;

        current = current->next;
    }

    return 1;
}

int is_valid_insert_position(const struct Address *head, int position)
{
    if (position < 1)
        return 0;

    if (position == 1)
        return 1;

    const struct Address *current = head;

    for (int i = 1; i < position - 1 && current != NULL; i++)
        current = current->next;

    return (current != NULL);
}