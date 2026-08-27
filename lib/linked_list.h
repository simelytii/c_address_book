#ifndef LINKED_LIST_H
#define LINKED_LIST_H

struct Address {
    char name[30];
    char surname[30];
    char email[50];
    char phone[20];

    struct Address *next;
};

struct Address *create_node(const char *name,
                            const char *surname,
                            const char *email,
                            const char *phone);

void add_to_list(struct Address **head, struct Address *new_node);

void free_list(struct Address **head);

int add_at_position(struct Address **head,
                     struct Address *new_node,
                     int position);

int delete_at_position(struct Address **head, int position);

struct Address *find_by_position(struct Address *head, int position);

int is_valid_position(const struct Address *head, int position);

int is_valid_insert_position(const struct Address *head, int position);

void print_list(const struct Address *head);

int find_addresses(struct Address *head, const char *field, const char *value);

void print_node(const struct Address *address);

#endif