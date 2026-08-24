#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "address_book.h"
#include "csv.h"

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