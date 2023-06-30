#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/*****************************************************************************
 *                                                                            *
 *  -------------------------------- list.h --------------------------------  *
 *                                                                            *
 *****************************************************************************/

#ifndef LIST_H
#define LIST_H

//  Define a structure for linked list elements.
typedef struct ListElmt_ {

    void               *data;
    struct ListElmt_   *next;

} ListElmt;

//  Define a structure for linked lists.

typedef struct List_ {

    int                size;

    int                (*match)(const void *key1, const void *key2);
    void               (*destroy)(void *data);

    ListElmt           *head;
    ListElmt           *tail;

} List;


/*****************************************************************************
 *                                                                            *
 *  ---------------------------- Public interface --------------------------- *
 *                                                                            *
 *****************************************************************************/


void list_init(List *list, void (*destroy)(void *data));

void list_destroy(List *list);

int list_ins_next(List *list, ListElmt *element, const void *data);

int list_remove_next(List *list, ListElmt *element, void **data);

#define list_size(list) ((list)->size)

#define list_head(list) ((list)->head)

#define list_tail(list) ((list)->tail)

#define list_is_head(list, element) ((element) == (list)->head ? 1 : 0)

#define list_is_tail(element) ((element)->next == NULL ? 1 : 0)

#define list_data(element) ((element)->data)

#define list_next(element) ((element)->next)


#endif


/*****************************************************************************
 * Initialize a linked list. Must be called before the list can be used with
 * any other operation
 *****************************************************************************/
void list_init(List *list, void (*destroy)(void *data)) {


    //  Initialize the list.
    list->size = 0;
    list->destroy = destroy;
    list->head = NULL;
    list->tail = NULL;

    return;
}


/*****************************************************************************
 * Destroy a linked list. No other operations are permitted after calling
 * destroy on a linked list unless list_init is called again
 *****************************************************************************/
void list_destroy(List *list) {
    void *data;

    //  Remove each element.
    while (list_size(list) > 0) {

        if (list_remove_next(list, NULL, (void **)&data) == 0 && list->destroy != NULL) {
            // Call a user-defined function to free dynamically allocated data.    *
            list->destroy(data);
        }
    }

    //  No operations are allowed now, but clear the structure as a precaution.
    memset(list, 0, sizeof(List));

    return;
}


/*****************************************************************************
 * Insert an element just after the `element` in the linked list specified by
 * list. If element is NULL, the new element will be inserted at the head.
 *****************************************************************************/
int list_ins_next(List *list, ListElmt *element, const void *data) {

    ListElmt           *new_element;


    // Allocate storage for the element.
    if ((new_element = (ListElmt *)malloc(sizeof(ListElmt))) == NULL)
        return -1;


    //  Insert the element into the list.
    new_element->data = (void *)data;

    if (element == NULL) {
        //  Handle insertion at the head of the list.
        if (list_size(list) == 0)
            list->tail = new_element;

        new_element->next = list->head;
        list->head = new_element;
    }
    else {

        //  Handle insertion somewhere other than at the head.

        if (element->next == NULL)
            list->tail = new_element;

        new_element->next = element->next;
        element->next = new_element;
    }


    //  Adjust the size of the list to account for the inserted element.
    list->size++;

    return 0;
}


/*****************************************************************************
 * Remove the element just after `element` from the linked list specified by
 * list. If element is NULL, the element at the head of list will be removed.
 *****************************************************************************/
int list_remove_next(List *list, ListElmt *element, void **data) {
    ListElmt   *old_element;

    //  Do not allow removal from an empty list.
    if (list_size(list) == 0) return -1;


    //  Remove the element from the list.
    if (element == NULL) {

        // Handle removal from the head of the list.
        *data = list->head->data;
        old_element = list->head;
        list->head = list->head->next;

        if (list_size(list) == 1) list->tail = NULL;
    }
    else {
        //  Handle removal from somewhere other than the head.

        if (element->next == NULL) return -1;

        *data = element->next->data;
        old_element = element->next;
        element->next = element->next->next;

        if (element->next == NULL) list->tail = element;
    }

    // Free the storage allocated by the abstract data type.
    free(old_element);

    //  Adjust the size of the list to account for the removed element.
    list->size--;

    return 0;
}


/*****************************************************************************
 *                                                                            *
 *  ------------------------------ print_list ------------------------------  *
 *                                                                            *
 *****************************************************************************/

static void print_list(const List *list) {

    ListElmt    *element;
    int         *data;
    int         i;

    fprintf(stdout, "List size is %d\n", list_size(list));

    i = 0;
    element = list_head(list);

    while (1) {

        data = list_data(element);
        fprintf(stdout, "list[%03d]=%03d\n", i, *data);

        i++;

        if (list_is_tail(element)) break;
        else element = list_next(element);

    }
    return;
}


/*****************************************************************************
 *                                                                            *
 *  --------------------------------- main ---------------------------------  *
 *                                                                            *
 *****************************************************************************/

int main(int argc, char **argv) {

    List        list;
    ListElmt    *element;
    int         *data, i;

    // Initialize the linked list.
    list_init(&list, free);

    /*****************************************************************************
     *                                                                            *
     *  Perform some linked list operations.                                      *
     *                                                                            *
     *****************************************************************************/

    element = list_head(&list);

    for (i = 10; i > 0; i--) {

        if ((data = (int *)malloc(sizeof(int))) == NULL)
            return 1;

        *data = i;

        if (list_ins_next(&list, NULL, data) != 0)
            return 1;

    }

    print_list(&list);

    element = list_head(&list);

    for (i = 0; i < 7; i++)
        element = list_next(element);

    data = list_data(element);

    fprintf(stdout, "Removing an element after the one containing %03d\n", *data);

    if (list_remove_next(&list, element, (void **)&data) != 0)
        return 1;

    print_list(&list);

    fprintf(stdout, "Inserting 011 at the tail of the list\n");

    *data = 11;
    if (list_ins_next(&list, list_tail(&list), data) != 0)
        return 1;

    print_list(&list);

    fprintf(stdout, "Removing an element after the first element\n");

    element = list_head(&list);
    if (list_remove_next(&list, element, (void **)&data) != 0)
        return 1;

    print_list(&list);

    fprintf(stdout, "Inserting 012 at the head of the list\n");

    *data = 12;
    if (list_ins_next(&list, NULL, data) != 0)
        return 1;

    print_list(&list);

    fprintf(stdout, "Iterating and removing the fourth element\n");

    element = list_head(&list);
    element = list_next(element);
    element = list_next(element);

    if (list_remove_next(&list, element, (void **)&data) != 0)
        return 1;

    print_list(&list);

    fprintf(stdout, "Inserting 013 after the first element\n");

    *data = 13;
    if (list_ins_next(&list, list_head(&list), data) != 0)
        return 1;

    print_list(&list);

    i = list_is_head(&list, list_head(&list));
    fprintf(stdout, "Testing list_is_head...Value=%d (1=OK)\n", i);
    i = list_is_head(&list, list_tail(&list));
    fprintf(stdout, "Testing list_is_head...Value=%d (0=OK)\n", i);
    i = list_is_tail(list_tail(&list));
    fprintf(stdout, "Testing list_is_tail...Value=%d (1=OK)\n", i);
    i = list_is_tail(list_head(&list));
    fprintf(stdout, "Testing list_is_tail...Value=%d (0=OK)\n", i);

    /*****************************************************************************
     *                                                                            *
     *  Destroy the linked list.                                                  *
     *                                                                            *
     *****************************************************************************/

    fprintf(stdout, "Destroying the list\n");
    list_destroy(&list);
	
    return 0;

}
