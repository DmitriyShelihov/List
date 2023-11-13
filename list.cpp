#include "list.h"

int list_resize(LIST* list, int new_size)
{
    if (list == NULL)
    {
        printf(RED "ERROR: List_realloc_down: list NULL pointer\n" END_OF_COLOUR);
        return -1;
    }

    if (new_size < DATA_SIZE)
    {
        printf(RED "ERROR: trying to decrease size of data without arranging\n" END_OF_COLOUR);
        return -2;
    }

    ARRAY = (ELEM*)realloc(ARRAY, new_size * sizeof(ELEM));

    int i = 0;
    for (i = DATA_SIZE; i < (2 * DATA_SIZE) -1 ; i++)
    {
        ARRAY[i].value = POISON;
        ARRAY[i].prev = -1;
        ARRAY[i].next = i + 1;
    }

    ARRAY[i].value = POISON;
    ARRAY[i].prev = -1;
    ARRAY[i].next = 0;

    FIRST_FREE = new_size/2;
    DATA_SIZE = new_size;

    return new_size;
}

int list_pop(LIST* list, int index)
{
    if (index >= DATA_SIZE || ARRAY[index].value == POISON)
    {
        printf(RED "You cannot delete non-existent element\n" END_OF_COLOUR);
        return -1;
    }

    if (index == 0)
    {
        printf(RED "You cannot pop [0] cell\n" END_OF_COLOUR);
        return 0;
    }

    list->elem_number--;
    int next_number = ARRAY[index].next;
    int prev_number = ARRAY[index].prev;

    ARRAY[next_number].prev = prev_number;
    ARRAY[prev_number].next = next_number;

    ARRAY[index].value = POISON;
    ARRAY[index].next = FIRST_FREE;
    ARRAY[index].prev = -1;

    FIRST_FREE = index;
    return index;
}

int list_insert_before(LIST* list, int index, double insert_value)
{
    if (index == 0)
    {
        printf(RED "Insert before 0 element\n" END_OF_COLOUR);
        return -1;
    }

    if (ARRAY[index].value == POISON && list->elem_number >= 1)
    {
        printf(RED "Insert before POISON element\n" END_OF_COLOUR);
        return -3;
    }

    if (index > DATA_SIZE)
    {
        printf(RED "INDEX > SIZE_OF_LIST you should increase SIZE_OF_LIST\n" END_OF_COLOUR);
        return -2;
    }

    if (FIRST_FREE == 0)
        int new_size = list_resize(list, DATA_SIZE*2);

    list->elem_number++;
    int result = FIRST_FREE;
    int new_free = ARRAY[FIRST_FREE].next;

    ARRAY[FIRST_FREE].value = insert_value;
    ARRAY[FIRST_FREE].next = index;
    ARRAY[FIRST_FREE].prev = ARRAY[index].prev;

    ARRAY[ARRAY[index].prev].next = FIRST_FREE;
    ARRAY[index].prev = FIRST_FREE;
    FIRST_FREE = new_free;
    return result;
}

int list_insert_after(LIST* list, int index, double insert_value)
{
    if (index == 0)
    {
        printf(RED "Insert after 0 element\n" END_OF_COLOUR);
        return -1;
    }

    if (ARRAY[index].value == POISON && list->elem_number >= 1)
    {
        printf(RED "Insert after POISON element\n" END_OF_COLOUR);
        return -3;
    }

    if (index > DATA_SIZE)
    {
        printf(RED "INDEX > SIZE_OF_LIST you should increase SIZE_OF_LIST\n" END_OF_COLOUR);
        return -2;
    }

    if (FIRST_FREE == 0)
    {
        int new_size = list_resize(list, DATA_SIZE*2);
        //printf(BLUE "List data reallocated(increased)! New list size is: %d\n" END_OF_COLOUR, new_size);
    }

    list->elem_number++;

    int result = FIRST_FREE;
    int new_free = ARRAY[FIRST_FREE].next;

    ARRAY[FIRST_FREE].value = insert_value;
    ARRAY[FIRST_FREE].next = ARRAY[index].next;
    ARRAY[FIRST_FREE].prev = index;

    ARRAY[ARRAY[index].next].prev = FIRST_FREE;
    ARRAY[index].next = FIRST_FREE;

    FIRST_FREE = new_free;
    return result;
}

int list_push_back(LIST* list, double insert_value)
{
    if (FIRST_FREE == 0 || (DATA_SIZE == 2 && list->elem_number == 0))
        int new_size = list_resize(list, (DATA_SIZE)*2);

    list->elem_number++;
    int result = FIRST_FREE;
    int new_free = ARRAY[FIRST_FREE].next;
    int last_elem = ARRAY[0].prev;

    ARRAY[FIRST_FREE].value = insert_value;
    ARRAY[FIRST_FREE].next = 0;
    ARRAY[FIRST_FREE].prev = last_elem;

    ARRAY[last_elem].next = FIRST_FREE;
    ARRAY[0].prev = FIRST_FREE;
    FIRST_FREE = new_free;

    return result;
}

int list_push_front(LIST* list, double insert_value)
{
    if (FIRST_FREE == 0)
        printf(BLUE "List data reallocated(increased)! New list size is: %d\n" END_OF_COLOUR, list_resize(list, (DATA_SIZE)*2));

    list->elem_number++;
    int result = FIRST_FREE;
    int new_free = ARRAY[FIRST_FREE].next;
    int first_elem = ARRAY[0].next;

    ARRAY[FIRST_FREE].value = insert_value;
    ARRAY[FIRST_FREE].next = first_elem;
    ARRAY[FIRST_FREE].prev = 0;

    ARRAY[first_elem].prev = FIRST_FREE;
    ARRAY[0].next = FIRST_FREE;
    FIRST_FREE = new_free;
    return result;
}

LIST* list_ctor(int size_of_list)
{
    ELEM* data = (ELEM*)calloc(size_of_list, sizeof(ELEM));

    data->value = POISON;
    data->next = 0;
    data->prev = 0;
    data++;

    for (int i = 1; i < size_of_list - 1; i++)
    {
        data->value = POISON;
        data->next = i + 1;
        data->prev = -1;
        data++;
    }

    data->value = POISON;
    data->next = 0;
    data->prev = -1;
    data -= size_of_list - 1;

    LIST* list = (LIST*)malloc(sizeof(LIST));

    ARRAY = data;
    FIRST_FREE = 1;
    ARRAY[0].next = 0;
    ARRAY[0].prev = 0;

    list->elem_number = 0;
    DATA_SIZE = size_of_list;

    return list;
}

int list_verify(LIST* list)
{
    printf(YELLOW "LIST VERIFY STARTED:\n" END_OF_COLOUR);

    if (list == NULL || ARRAY == NULL)
    {
        return -1;
        printf(RED "Verify: NULL POINTER TO LIST\n" END_OF_COLOUR);
    }

    int error = 0;
    int is_loop = 1;

    for (int i = ARRAY[0].next; i < DATA_SIZE -1 ; i = ARRAY[i].next)
    {
        if (ARRAY[i].next == 0)
        {
            is_loop = 0;
            printf(GREEN "Verify: CORRECT there is no loops\n" END_OF_COLOUR);
            break;
        }
    }

    if (is_loop == 1)
    {
        printf(RED "Verify: FAULT loop in a list: not found next = 0\n" END_OF_COLOUR);
        error += 10;
    }

    int elem_error = 0;

    for (int i = ARRAY[0].next; i != ARRAY[0].prev; i = ARRAY[i].next)
    {
        if (ARRAY[ARRAY[i].next].prev != i)
        {
            printf(RED "Verify: FAULT elem %d: prev(next) != elem\n" END_OF_COLOUR, i);
            error += 100;
            elem_error = 1;
            break;
        }
    }

    if (elem_error == 0)
        printf(GREEN "Verify: CORRECT for all elements: prev(next) = elem\n" END_OF_COLOUR);

    int is_free_error = 0;

    for (int i = FIRST_FREE; i < DATA_SIZE && i != 0; i = ARRAY[i].next)
    {
        if (ARRAY[i].prev != -1)
        {
            printf(RED "Verify: FAULT free elem %d has non -1 prev\n" END_OF_COLOUR, i);
            error += 1000;
            is_free_error = 1;
            break;
        }
    }

    if (is_free_error == 0)
        printf(GREEN "Verify: CORRECT all free elem has -1 prev\n" END_OF_COLOUR);
    printf(YELLOW "LIST VERIFY ENDED;\n" END_OF_COLOUR);

    return error;
}

int list_dtor(LIST* list)
{
    if (list == NULL)
    {
        printf(RED "ERROR: list_dtor: Null pointer to list\n" END_OF_COLOUR);
        return -1;
    }

    int filled_elem = ARRAY[0].next;

    do
    {
        int save_border = ARRAY[filled_elem].next;

        ARRAY[filled_elem].value = POISON;
        ARRAY[filled_elem].prev = 0;
        ARRAY[filled_elem].next = 0;

        filled_elem = save_border;

    } while (filled_elem != ARRAY[0].prev && filled_elem != 0);

    int free_elem = FIRST_FREE;

    while (free_elem != 0 && free_elem < DATA_SIZE-1 && ARRAY[free_elem].next != 0)
    {
        int save_border = ARRAY[free_elem].next;
        ARRAY[free_elem].prev = 0;
        ARRAY[free_elem].next = 0;
        free_elem = save_border;
    }

    ARRAY[free_elem].prev = 0;
    ARRAY[0].value = POISON;
    free(list);
    return 0;
}

