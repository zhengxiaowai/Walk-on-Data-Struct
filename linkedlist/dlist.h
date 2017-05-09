#ifndef DLIST_H
#define DLIST_H

#include <stdlib.h>

typedef struct DListElmt_
{
    void *data;
    struct DListElmt_ *prev;
    struct DListElmt_ *next;
} DListElmt;

typedef struct DList_
{
    int size;
    void (*destroy)(void *data);
    DListElmt *head;
    DListElmt *tail;

} DList;

void dlist_init(DList *list, void (*destroy)(void *data));
void dlist_destroy(DList *list);
int dlist_ins_next(DList *list, DListElmt *element, const void *data);
int dlist_ins_prev(DList *list, DListElmt *element, const void *data);
int dlist_remove(DList *list, DListElmt *element, void **data);
void dlist_traverse(DList *list);

#define dlist_size(list) (list->size)
#define dlist_head(list) (list->head)
#define dlist_tail(list) (list->tail)
#define dlist_is_head(list, element) (element == list->head ? 1 : 0)
#define dlist_is_tail(element) (element->next == NULL ? 1 : 0)
#define dlist_data(element) (element->data)
#define dlist_next(element) (element->next)
#define dlist_prev(element) (element->prev)

#endif