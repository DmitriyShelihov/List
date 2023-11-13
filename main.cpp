#include "list.h"
#include "list_help.h"
#include "list_dump.h"

void working_with_list(LIST* list)
{
    int a = list_push_back(list, 100);
    int b = list_push_front(list, 5);
    list_dump_verbose(list);
    int c = list_insert_before(list, 2, 1);
    list_dump_verbose(list);
    printf("%d %d %d", a, b, c);
    list_arrange(list);
    list_dump_verbose(list);
    delete_max(list);

    list_dump_png(list);
}

int main()
{
    LIST* list = list_ctor(8); //starting capacity
    working_with_list(list);

    list_dump_png(list);
    list_dtor(list);
    return 0;
}
