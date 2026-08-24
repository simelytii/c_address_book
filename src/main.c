#include <stdio.h>
#include <signal.h>
#include "address_book.h"
#include "csv.h"
#include "menu.h"

static volatile sig_atomic_t interrupted = 0;

static void handle_signal(int signal)
{
    (void)signal;
    interrupted = 1;
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

    run_menu(&head, &interrupted);

    if (interrupted)
        printf("\nSignal received. Exiting\n");

    free_list(&head);

    return 0;
}