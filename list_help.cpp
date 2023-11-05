#include "list_help.h"

double list_elem(LIST* list, int index)
{
    int real_index = array[0].next;
    for (int i = 0; i < index; i++)
        real_index = array[real_index].next;
    return array[real_index].value;
}

double delete_max(LIST* list)
{
    double list_max = DBL_MIN;
    int index_max = -1;
    int current_elem = array[0].next;
    int lst_len = list->elem_number;
    for (int i; i < lst_len - 1; i++)
    {
        if (array[current_elem].value >= list_max)
        {
            list_max = array[current_elem].value;
            index_max = i;
        }
        current_elem = array[current_elem].next;
    }
    if (array[(list->data)[0].prev].value >= list_max)
    {
        list_max = (array[(list->data)[0].prev].value) ;
        index_max = lst_len - 1;
    }
    list_pop(list, index_max);
    return list_max;
}

double delete_min(LIST* list)
{
    double list_min = DBL_MAX;
    int index_min = -1;
    int current_elem = array[0].next;
    int i = 0;
    int lst_len = list->elem_number;
    for (i; i < lst_len - 1; i++)
    {
        if (array[current_elem].value <= list_min)
        {
            list_min = array[current_elem].value;
            index_min = i;
        }
        current_elem = array[current_elem].next;
    }
    if (array[(list->data)[0].prev].value <= list_min)
    {
        list_min = array[(list->data)[0].prev].value;
        index_min = lst_len;
    }
    list_pop(list, index_min);
    return list_min;
}
