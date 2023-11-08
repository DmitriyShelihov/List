#include "list.h"
#include "list_help.h"
#include "list_dump.h"
#include <time.h>

void working_with_list(LIST* list)
{
    list_push_back(list, 1221);
    list_arrange(list);
}

int main()
{
    LIST* list = list_ctor(8);
    working_with_list(list);
    list_dump_png(list);
    list_dtor(list);
    return 0;
}
