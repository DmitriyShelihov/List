#include "list.h"
#include "list_help.h"
#include "list_dump.h"
#include <time.h>

void working_with_list(LIST* list)
{
    list_push_back(list, 1);
    list_push_back(list, 1);
    list_push_back(list, 1);
    list_push_back(list, 1);
    list_dump_png(list);
}

int main()
{
    LIST* list = list_ctor(4);
    working_with_list(list);
    list_dtor(list);
    free(list);
    return 0;
}
