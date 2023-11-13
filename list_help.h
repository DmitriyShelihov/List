#ifndef LIST_HELP_H
#define LIST_HELP_H

#include <stdio.h>
#include "list.h"

double delete_max(LIST* list);

double delete_min(LIST* list);

double list_elem(LIST* list, int index);  //возвращает элемент по номеру

int list_arrange(LIST* list);

#endif
