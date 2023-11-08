#include "list_help.h"

double list_elem(LIST* list, int index)
{
    int real_index = ARRAY[0].next;
    for (int i = 0; i < index; i++)
        real_index = ARRAY[real_index].next;

    return ARRAY[real_index].value;
}

int list_arrange(LIST* list)
{
    ELEM* data_new = (ELEM*)calloc(DATA_SIZE, sizeof(ELEM));

    data_new->value = POISON;
    data_new->next = 0;
    data_new->prev = 0;
    data_new++;

    for (int i = 1; i < DATA_SIZE - 1; i++)
    {
        data_new->value = POISON;
        data_new->next = i + 1;
        data_new->prev = -1;
        data_new++;
    }

    data_new->value = POISON;
    data_new->next = 0;
    data_new->prev = -1;
    data_new -= DATA_SIZE -1;

    int current_index = ARRAY[0].next;
    int new_index = 1;

    while (current_index != ARRAY[0].prev)
    {
        int new_current_index = ARRAY[current_index].next;

        ARRAY[ARRAY[current_index].next].prev = new_index;
        ARRAY[ARRAY[current_index].prev].next = new_index;

        data_new[new_index].value = ARRAY[current_index].value;
        data_new[new_index].next = new_index + 1;
        data_new[new_index].prev = new_index - 1;

        new_index++;
        current_index = new_current_index;
    }

    data_new[new_index].value = ARRAY[current_index].value;
    data_new[new_index].next = 0;
    data_new[new_index].prev = ARRAY[current_index].prev;

    data_new[0].prev = new_index;
    ARRAY = data_new;

    if (new_index + 1 == DATA_SIZE)
        FIRST_FREE = 0;
    else
        FIRST_FREE = new_index + 1;

    if (list->elem_number * 2 < DATA_SIZE)
    {
        ARRAY = (ELEM*)realloc(ARRAY, DATA_SIZE/2 * sizeof(ELEM));
        return 1;
    }

    return 2;
}

double delete_max(LIST* list)
{
    double list_max = DBL_MIN;
    int index_max = -1;

    for (int i = 1; i < DATA_SIZE; i++)
    {
        if (ARRAY[i].value >= list_max)
        {
            list_max = ARRAY[i].value;
            index_max = i;
        }
    }

    list_pop(list, index_max);

    return list_max;
}

double delete_min(LIST* list)
{
    double list_min = DBL_MAX;
    int index_min = -1;

    for (int i = 1; i < DATA_SIZE; i++)
    {
        if (ARRAY[i].value <= list_min && ARRAY[i].value != POISON)
        {
            list_min = ARRAY[i].value;
            index_min = i;
        }
    }

    list_pop(list, index_min);

    return list_min;
}
