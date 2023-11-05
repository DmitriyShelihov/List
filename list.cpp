#include "list.h"

int data_ctor(ELEM* data, int size_of_data)
{
    data->value = POISON;
    data->next = 0;
    data->prev = 0;
    data++;

    for (int i = 1; i < size_of_data - 1; i++)
    {
        data->value = POISON;
        data->next = i + 1;
        data->prev = -1;
        data++;
    }
    data->value = POISON;
    data->next = 0;
    data->prev = -1;
    return 1;
}

int list_resize(LIST* list, int new_size)
{
    if (list == NULL)
    {
        printf(RED "List_realloc_down: Didn't found list: NULL pointer\n" END_OF_COLOUR);
        return -1;
    }

    if (new_size < list->data_size) //realloc_down
    {
        ELEM* data_new = (ELEM*)calloc(new_size, sizeof(ELEM));
        data_ctor(data_new, new_size);
        int current_index = array[0].next;
        int new_index = 1;
        data_new[0].next = 1;
        for (;current_index != array[0].prev; )
        {
            int new_current_index = array[current_index].next;
            array[array[current_index].next].prev = new_index;
            array[array[current_index].prev].next = new_index;
            data_new[new_index].value = array[current_index].value;
            data_new[new_index].next = new_index + 1;
            data_new[new_index].prev = new_index - 1;
            new_index++;
            current_index = new_current_index;
        }
        data_new[new_index].value = array[current_index].value;
        data_new[new_index].next = 0;
        data_new[new_index].prev = array[current_index].prev;
        data_new[0].prev = new_index;
        list->data = data_new;
        if (new_index + 1 == new_size)
            list->first_free = 0;
        else
            list->first_free = new_index + 1;
    }

    else //realloc_up
    {
        list->data = (ELEM*)realloc(list->data, new_size * sizeof(ELEM));
        int i = 0;
        for (i = list->data_size; i < (2 * list->data_size) -1 ; i++)
        {
            array[i].value = POISON;
            array[i].prev = -1;
            array[i].next = i + 1;
        }
        array[i].value = POISON;
        array[i].prev = -1;
        array[i].next = 0;
        list->first_free = new_size/2;
    }
    list->data_size = new_size;
    return new_size;
}

int list_dump(LIST* list)
{
    printf(YELLOW "USER LIST DUMP:\n" END_OF_COLOUR);
    if (list == NULL)
    {
        printf(RED "List_dump cannot find list, <NULL POINTER>" END_OF_COLOUR);
        return -1;
    }
    printf(RED "[" END_OF_COLOUR);
    for (int i = array[0].next; i != array[0].prev; i = array[i].next)
    {
        printf(" %11lf " RED "," END_OF_COLOUR, array[i].value);

    }
    if (array[0].next == array[0].prev && array[array[0].next].next != 0)
    {
        printf(RED "]" END_OF_COLOUR);
        printf("\n\n");
        return 0;
    }
    printf(" %11lf " RED "]" END_OF_COLOUR, array[array[0].prev].value);
    printf("\n\n");
    return 0;
}

int list_dump_verbose(LIST* list)
{
    printf(YELLOW "Main info: head: %d, tail: %d, free: %d, data_size: %d, elem_number: %d\n" END_OF_COLOUR,
          array[0].next, array[0].prev, list->first_free, list->data_size, list->elem_number);
    printf(YELLOW "LIST DUMP:\n" END_OF_COLOUR);
    if (list == NULL)
    {
        printf(RED "List_dump cannor find list <NULL POINTER>" END_OF_COLOUR);
        return -1;
    }
    printf("Number: " RED "|" END_OF_COLOUR);

    for (int i = 0; i < list->data_size; i++)
        printf(BLUE " %11d " RED "|" END_OF_COLOUR, i);
    printf("\n");
    printf("Data  : " RED "|" END_OF_COLOUR);

    for (int i = 0; i < list->data_size; i++)
    {
        if (array[i].value != POISON)
            printf(" %11lf " RED "|" END_OF_COLOUR, (array[i].value));
        else
            printf(GREEN"     Poison  " RED "|" END_OF_COLOUR);
    }
    printf("\n");
    printf("Next  : " RED "|" END_OF_COLOUR);

    for (int i = 0; i < list->data_size; i++)
        printf(" %11d " RED "|" END_OF_COLOUR, array[i].next);
    printf("\n");
    printf("Prev  : " RED "|" END_OF_COLOUR);

    for (int i = 0; i < list->data_size; i++)
        printf(" %11d " RED "|" END_OF_COLOUR, array[i].prev);
    printf("\n\n");
    return 0;
}

int list_pop(LIST* list, int index)
{
    if (index >= list->data_size || array[index].value == POISON)
    {
        printf(RED "You cannot delete non-existent element\n" END_OF_COLOUR);
        return -1;
    }
    if (index == 0)
    {
        printf(RED "You cannot pop [0] cell\n" END_OF_COLOUR);
        return index;
    }
    (list->elem_number) --;
    int next_number = array[index].next;
    int prev_number = array[index].prev;
    array[next_number].prev = prev_number;
    array[prev_number].next = next_number;
    array[index].value = POISON;
    array[index].next = list->first_free;
    array[index].prev = -1;
    list->first_free = index;
    if (list->elem_number * 2 < list->data_size)
    {
        int new_size = list_resize(list, (list->data_size)/2);
        //printf(BLUE "List data reallocated (decreased)! New list size is: %d\n" END_OF_COLOUR, new_size);
    }
    return index;
}

int list_insert_before(LIST* list, int index, double insert_value)
{
    if (index == 0)
    {
        printf(RED "Insert before 0 element\n" END_OF_COLOUR);
        return -1;
    }
    if (array[index].value == POISON && list->elem_number >= 1)
    {
        printf(RED "Insert before POISON element\n" END_OF_COLOUR);
        return -3;
    }
    if (index > list->data_size)
    {
        printf(RED "INDEX > SIZE_OF_LIST you should increase SIZE_OF_LIST\n" END_OF_COLOUR);
        return -2;
    }
    if (list->first_free == 0)
    {
        int new_size = list_resize(list, (list->data_size)*2);
        //printf(BLUE "List data reallocated(increased)! New list size is: %d\n" END_OF_COLOUR, new_size);
    }
    if (list->elem_number == 0)
    {
        array[1].value = insert_value;
        array[1].next = 0;
        array[1].prev = 0;
        array[0].next = 1;
        array[0].prev = 1;
        list->first_free = 2;
        list->elem_number++;
        return 1;
    }
    list->elem_number++;
    int result = list->first_free;
    int new_free = array[list->first_free].next;
    array[list->first_free].value = insert_value;
    array[list->first_free].next = index;
    array[list->first_free].prev = array[index].prev;
    array[(array[index].prev)].next = list->first_free;
    array[index].prev = list->first_free;
    list->first_free = new_free;
    return result;
}

int list_insert_after(LIST* list, int index, double insert_value)
{
    if (index == 0)
    {
        printf(RED "Insert after 0 element\n" END_OF_COLOUR);
        return -1;
    }
    if (array[index].value == POISON && list->elem_number >= 1)
    {
        printf(RED "Insert after POISON element\n" END_OF_COLOUR);
        return -3;
    }
    if (index > list->data_size)
    {
        printf(RED "INDEX > SIZE_OF_LIST you should increase SIZE_OF_LIST\n" END_OF_COLOUR);
        return -2;
    }
    if (list->first_free == 0)
    {
        int new_size = list_resize(list, (list->data_size)*2);
        //printf(BLUE "List data reallocated(increased)! New list size is: %d\n" END_OF_COLOUR, new_size);
    }
    if (list->elem_number == 0)
    {
        array[1].value = insert_value;
        array[1].next = 0;
        array[1].prev = 0;
        array[0].next = 1;
        array[0].prev = 1;
        list->first_free = 2;
        list->elem_number++;
        return 1;
    }
    list->elem_number++;
    int result = list->first_free;
    int new_free = array[list->first_free].next;
    array[list->first_free].value = insert_value;
    array[list->first_free].next = array[index].next;
    array[list->first_free].prev = index;
    array[(array[index].next)].prev = list->first_free;
    array[index].next = list->first_free;
    list->first_free = new_free;
    return result;
}

int list_push_back(LIST* list, double insert_value)
{
    if (list->first_free == 0 || (list->data_size == 2 && list->elem_number == 0))
    {
        int new_size = list_resize(list, (list->data_size)*2);
        //printf(BLUE "List data reallocated(increased)! New list size is: %d\n" END_OF_COLOUR, new_size);
    }
    if (list->elem_number == 0)
    {
        array[1].value = insert_value;
        array[1].next = 0;
        array[1].prev = 0;
        array[0].next = 1;
        array[0].prev = 1;
        list->first_free = 2;
        list->elem_number++;
        return 1;
    }
    list->elem_number++;
    int result = list->first_free;
    int new_free = array[list->first_free].next;
    int last_elem = array[0].prev;
    array[list->first_free].value = insert_value;
    array[list->first_free].next = 0;
    array[list->first_free].prev = last_elem;
    array[last_elem].next = list->first_free;
    array[0].prev = list->first_free;
    list->first_free = new_free;
    return result;
}

int list_push_front(LIST* list, double insert_value)
{
    if (list->first_free == 0)
        printf(BLUE "List data reallocated(increased)! New list size is: %d\n" END_OF_COLOUR, list_resize(list, (list->data_size)*2));
    if (list->elem_number == 0)
    {
        array[1].value = insert_value;
        array[1].next = 0;
        array[1].prev = 0;
        array[0].next = 1;
        array[0].prev = 1;
        list->first_free = 2;
        (list->elem_number)++;
        return 1;
    }
    list->elem_number++;
    int result = list->first_free;
    int new_free = array[list->first_free].next;
    int first_elem = array[0].next;
    array[list->first_free].value = insert_value;
    array[list->first_free].next = first_elem;
    array[list->first_free].prev = 0;
    array[first_elem].prev = list->first_free;
    array[0].next = list->first_free;
    list->first_free = new_free;
    return result;
}

LIST* list_ctor(int size_of_list)
{
    ELEM* data = (ELEM*)calloc(size_of_list, sizeof(ELEM));
    data_ctor(data, size_of_list);
    LIST* List = (LIST*)malloc(sizeof(LIST));

    List->data = data;
    List->first_free = 1;
    (List->data)[0].next = 0;
    (List->data)[0].prev = 0;

    List->elem_number = 0;
    List->data_size = size_of_list;
    return List;
}

int list_verify(LIST* list)
{
    printf(YELLOW "LIST VERIFY STARTED:\n" END_OF_COLOUR);
    if (list == NULL || list->data == NULL || list == NULL)
    {
        return - 1;
        printf(RED "Verify: NULL POINTER IN LIST\n" END_OF_COLOUR);
    }
    int error = 0;
    int is_loop = 1;
    for (int i = array[0].next; i < list->data_size -1 ; i = array[i].next)
    {
        if (array[i].next == 0)
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
    for (int i = array[0].next; i != array[0].prev; i = array[i].next)
    {
        if (array[array[i].next].prev != i)
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
    for (int i = list->first_free; i < list->data_size && i != 0; i = array[i].next)
    {
        if (array[i].prev != -1)
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
    int filled_elem = array[0].next;
    int save_border = -1;
    while (filled_elem != array[0].prev && filled_elem != 0)
    {
        save_border = array[filled_elem].next;
        array[filled_elem].value = POISON;
        array[filled_elem].prev = 0;
        array[filled_elem].next = 0;
        filled_elem = save_border;
    }

    array[filled_elem].value = POISON;
    array[filled_elem].prev = 0;
    array[filled_elem].next = 0;
    int free_elem = list->first_free;

    while (free_elem != 0 && free_elem < list->data_size - 1 && array[free_elem].next != 0)
    {
        int save_border = array[free_elem].next;
        array[free_elem].prev = 0;
        array[free_elem].next = 0;
        free_elem = save_border;
    }
    array[free_elem].prev = 0;
    array[0].value = POISON;
    free(list);
    return 0;
}

