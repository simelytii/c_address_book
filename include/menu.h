#ifndef MENU_H
#define MENU_H

#include <signal.h>
#include "linked_list.h"

void run_menu(struct Address **head,
              const volatile sig_atomic_t *interrupted);

#endif