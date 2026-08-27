#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>
#include "linked_list.h"

struct Address *create_node(const char *name,
                            const char *surname,
                            const char *email,
                            const char *phone)
{
    struct Address *new_node = malloc(sizeof(struct Address));

    if (new_node == NULL)
        return NULL;

    strncpy(new_node->name, name, sizeof(new_node->name) - 1);
    new_node->name[sizeof(new_node->name) - 1] = '\0';

    strncpy(new_node->surname, surname, sizeof(new_node->surname) - 1);
    new_node->surname[sizeof(new_node->surname) - 1] = '\0';

    strncpy(new_node->email, email, sizeof(new_node->email) - 1);
    new_node->email[sizeof(new_node->email) - 1] = '\0';

    strncpy(new_node->phone, phone, sizeof(new_node->phone) - 1);
    new_node->phone[sizeof(new_node->phone) - 1] = '\0';
    
    new_node->next = NULL;
    
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

void print_list(const struct Address *head)
{
    const struct Address *current = head;

    if (current == NULL) {
        printf("Address book is empty.\n");
        return;
    }

    while (current != NULL) {
        print_node(current);
        current = current->next;
    }
}

int find_addresses(struct Address *head, const char *field, const char *value)
{
    struct Address *current = head;
    int found = 0;

    while (current != NULL) {
        if (strcasecmp(field, "name") == 0 &&
            strcasecmp(current->name, value) == 0) {
            print_node(current);
            found = 1;
        } else if (strcasecmp(field, "surname") == 0 &&
                   strcasecmp(current->surname, value) == 0) {
            print_node(current);
            found = 1;
        } else if (strcasecmp(field, "email") == 0 &&
                   strcasecmp(current->email, value) == 0) {
            print_node(current);
            found = 1;
        } else if (strcasecmp(field, "phone") == 0 &&
                   strcasecmp(current->phone, value) == 0) {
            print_node(current);
            found = 1;
        }

        current = current->next;
    }

    return found;
}

void print_node(const struct Address *address)
{
    printf("Name: %s\n", address->name);
    printf("Surname: %s\n", address->surname);
    printf("Email: %s\n", address->email);
    printf("Phone: %s\n", address->phone);
    printf("\n");
}