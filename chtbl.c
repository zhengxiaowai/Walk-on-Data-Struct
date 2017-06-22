#include <string.h>
#include <stdio.h>
#include <time.h>
#include "chtbl.h"

int chtbl_init(CHTbl *htbl,
               int buckets,
               unsigned int (*h)(const void *key),
               int (*match)(const void *key1, const void *key2),
               void (*destroy)(void *data))
{
    int i;

    // 初始化一个 table，由 buckets 个组成的 List
    if ((htbl->table = (List *)malloc(buckets * sizeof(List))) == NULL)
        return -1;

    // 初始化 bucket 的 List
    htbl->buckets = buckets;
    for (i = 0; i < htbl->buckets; i++)
        list_init(&htbl->table[i], destroy);

    htbl->h = h;
    htbl->match = match;
    htbl->destroy = destroy;
    htbl->size = 0;

    return 0;
}
void chtbl_destroy(CHTbl *htbl)
{
    int i;

    for (i = 0; i < htbl->buckets; i++)
        list_destroy(&htbl->table[i]);

    free(htbl->table);
    memset(htbl, 0, sizeof(CHTbl));
}
int chtbl_insert(CHTbl *htbl, const void *data)
{
    void *temp;
    int bucket, retval;

    // 已经存在
    temp = (void *)data;
    if (chtbl_lookup(htbl, &temp) == 0)
        return 1;

    // 求 key 的 hash 找出存在哪一个 bucket 中
    bucket = htbl->h(data) % htbl->buckets;

    if ((retval = list_ins_next(&htbl->table[bucket], NULL, data)) == 0)
        htbl->size++;

    return retval;
}
int chtbl_remove(CHTbl *htbl, void **data)
{
    ListElmt *element, *prev;
    int bucket;

    // 求 bucket
    bucket = htbl->h(data) % htbl->buckets;

    // 在 bucket 中查找s
    prev = NULL;
    List *pbucket = &(htbl->table[bucket]);
    for (element = list_head(pbucket); element != NULL; element = list_next(element))
    {
        if (htbl->match(list_data(element), *data))
        {
            if (list_rem_next(&htbl->table[bucket], prev, data) == 0)
            {
                htbl->size--;
                return 0;
            }
            else
                return -1;
        }
        prev = element;
    }

    return -1;
}
int chtbl_lookup(CHTbl *htbl, void **data)
{
    ListElmt *element;

    // 求出存在哪一个 bucket 中
    int bucket = htbl->h(*data) % htbl->buckets;

    // 在这个 bucket 中找出匹配的数据
    List *pbucket = &(htbl->table[bucket]);
    for (element = list_head(pbucket); element != NULL; element = list_next(element))
    {
        if (htbl->match(list_data(element), *data))
        {
            *data = list_data(element);
            return 0;
        }
    }

    return -1;
}

unsigned int hashpjw(const void *key)
{
    return *(int *)key;
}

int match(const void *key1, const void *key2)
{
    return *(int *)key1 == *(int *)key2;
}

void chtbl_print(CHTbl *chtbl)
{
    int i;
    List bucket_list;

    for (i = 0; i < chtbl->buckets; i++)
    {
        printf("Bucket %d: ", i);
        bucket_list = chtbl->table[i];

        ListElmt *node = bucket_list.head;
        while (node != NULL)
        {
            printf("%d ", *((int *)list_data(node)));
            node = node->next;
        }

        printf("\n");
    }
}

int main()
{
    srand(time(0));

    // 测试 chtbl_init
    CHTbl *htbl = (CHTbl *)malloc(sizeof(CHTbl));
    chtbl_init(htbl, 11, hashpjw, match, free);

    
    // 测试 chtbl_insert
    int i, *pi, created_count = 100;
    for (i = 0; i < created_count; i++)
    {
        pi = (int *)malloc(sizeof(int));
        *pi = rand() % 100 + 1;
        chtbl_insert(htbl, (void *)pi);
    }
    chtbl_print(htbl);
    printf("\n");

    // 测试 chtbl_lookup
    int find_count = 10;
    for (i = 0; i < find_count; i++)
    {
        pi = (int *)malloc(sizeof(int));
        *pi = rand() % 100 + 1;
        if (chtbl_lookup(htbl, (void **)&pi) == 0)
            printf("Found [%d] in hash table\n", *pi);
        else
            printf("Not Found [%d] in hash table\n", *pi);
    }
    printf("\n");

    // 测试 chtbl_remove
    int remove_count = 10;
    for (i = 0; i < remove_count; i++)
    {
        pi = (int *)malloc(sizeof(int));
        *pi = rand() % 100 + 1;
        if (chtbl_remove(htbl, (void **)&pi) == 0)
        {
            printf("Remove [%d] from hash table\n", *pi);
            free(pi);
        }
        else
            printf("Not Found [%d] in hash table\n", *pi);
    }
    printf("<------------------------------------>\n");
    chtbl_print(htbl);
    printf("\n");

    // 测试 chtbl_destroy
    chtbl_destroy(htbl);
    chtbl_print(htbl);
    printf("Current Bucket Count: %d\n", htbl->size);
}