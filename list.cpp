#include "list.h"

int main()
{
    LIST* list = list_ctor(SIZE_OF_LIST);
    /*...*/
    list_dtor(list);
    free(list);
    return 0;
}
