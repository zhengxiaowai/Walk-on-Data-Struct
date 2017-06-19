#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <time.h>

#include "heap.h"

#define heap_parent(npos) ((int)((npos - 1) / 2))
#define heap_left(npos) ((npos * 2) + 1)
#define heap_right(npos) ((npos * 2) + 2)

void heap_init(Heap *heap, int (*compare)(const void *key1, const void *key2), void (*destroy)(void *data))
{
    heap->size = 0;
    heap->compare = compare;
    heap->destroy = destroy;
    heap->tree = NULL;

    return;
}

void heap_destroy(Heap *heap)
{
    int i;

    if (heap->destroy != NULL)
    {
        for (i = 0; i < heap_size(heap); i++)
        {
            heap->destroy(heap->tree[i]);
        }
    }

    free(heap->tree);

    memset(heap, 0, sizeof(Heap));

    return;
}
int heap_insert(Heap *heap, void *data)
{
    void *temp;
    int ipos, ppos;

    if ((temp = (void **)realloc(heap->tree, (heap_size(heap) + 1) * sizeof(void *))) == NULL)
        return -1;
    else
        heap->tree = temp;

    heap->tree[heap_size(heap)] = (void *)data;

    ipos = heap_size(heap);
    ppos = heap_parent(ipos);

    while (ipos > 0 && heap->compare(heap->tree[ppos], heap->tree[ipos]) < 0)
    {
        temp = heap->tree[ppos];
        heap->tree[ppos] = heap->tree[ipos];
        heap->tree[ipos] = temp;

        ipos = ppos;
        ppos = heap_parent(ipos);
    }
    
    heap->size++;

    return 0;
}

int heap_extract(Heap *heap, void **data)
{
    void *save, *temp;
    int ipos, lpos, rpos, mpos;

    if (heap_size(heap) == 0)
        return -1;

    *data = heap->tree[0];

    save = heap->tree[heap_size(heap) - 1];

    if (heap_size(heap) - 1 > 0)
    {
        if ((temp = (void **)realloc(heap->tree, (heap_size(heap) + 1) * sizeof(void *))) == NULL)
            return -1;
        else
            heap->tree = temp;

        heap->size--;
    }
    else
    {
        // 只有最后一个
        free(heap->tree);
        heap->tree = NULL;
        heap->size = 0;
        return 0;
    }

    heap->tree[0] = save;

    ipos = 0;
    lpos = heap_left(ipos);
    rpos = heap_right(ipos);

    while (1)
    {
        lpos = heap_left(ipos);
        rpos = heap_right(ipos);

        if (lpos < heap_size(heap) && heap->compare(heap->tree[lpos], heap->tree[ipos]) > 0)
            mpos = lpos;
        else
            mpos = ipos;

        if (rpos < heap_size(heap) && heap->compare(heap->tree[rpos], heap->tree[mpos]) > 0)
            mpos = rpos;

        if (mpos == ipos)
            break;
        else
        {
            temp = heap->tree[mpos];
            heap->tree[mpos] = heap->tree[ipos];
            heap->tree[ipos] = temp;

            ipos = mpos;
        }
    }
    return 0;
}

static int compare(const void *key1, const void *key2)
{
    // printf("%d, %d\n", *(int *)key1, *(int *)key2);
    return (*(int *)key1 - *(int *)key2);
}

static void print_tree(Heap *heap)
{
    int i;
    int *data;
    for (i = 0; i < heap_size(heap); i++)
    {   
        data = (int *)(heap->tree[i]);
        printf("%d ", *data);
    }
    printf("\nTREE END ----\n");
}

int main()
{
    int i, *pi;
    srand(time(0));

    Heap *heap = (Heap *)malloc(sizeof(Heap));
    heap_init(heap, compare, free);
    print_tree(heap);

    int insert_count = 10;
    for (i = 0; i < insert_count; i++)
    {
        pi = (int *)malloc(sizeof(int));
        *pi = rand() % 100 + 1;
        printf("-> %d\n", *pi);
        heap_insert(heap, (void *)pi);
        // print_tree(heap);
    }

    print_tree(heap);

    for (i = 0; i < 5; i++)
    {
        pi = (int *)malloc(sizeof(int));
        heap_extract(heap, (void **)&pi);
        printf("> pick a %d\n", *pi);
        // print_tree(heap);
        
    }

    print_tree(heap);

    heap_destroy(heap);
    print_tree(heap);


}