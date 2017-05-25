#include <string.h>
#include <stdio.h>
#include <time.h>
#include "ohtbl.h"

#define O_HASHTBL_POSITIONS 11

static char vacated;

int ohtbl_init(
    OHTbl *htbl,
    int positions,
    int (*h1)(const void *key),
    int (*h2)(const void *key),
    int (*match)(const void *key1, const void *key2),
    void (*destroy)(void *data))
{
    int i;

    if ((htbl->table = (void **)malloc(positions * sizeof(void *))) == NULL)
        return -1;

    for (i = 0; i < positions; i++)
        htbl->table[i] = NULL;

    htbl->vacated = &vacated;

    htbl->h1 = h1;
    htbl->h2 = h2;
    htbl->match = match;
    htbl->destroy = destroy;
    htbl->positions = positions;
    htbl->size = 0;

    return 0;
}

void ohtbl_destroy(OHTbl *htbl)
{
    int i;

    if (htbl->destroy != NULL)
    {
        for (i = 0; i < htbl->positions; i++)
        {
            if (htbl->table[i] != NULL && htbl->table[i] != htbl->vacated)
                htbl->destroy(htbl->table[i]);
        }
    }

    free(htbl->table);
    memset(htbl, 0, sizeof(OHTbl));
}

int ohtbl_insert(OHTbl *htbl, const void *data)
{
    void *temp;
    int i, position;

    // full
    if (htbl->size == htbl->positions)
        return -1;

    temp = (void *)data;
    if (ohtbl_lookup(htbl, &temp) == 0)
        return 1;

    for (i = 0; i < htbl->positions; i++)
    {
        
        position = (htbl->h1(data) + (i * htbl->h2(data))) % htbl->positions;
        if (htbl->table[position] == NULL || htbl->table[position] == htbl->vacated)
        {
            htbl->table[position] = (void *)data;
            htbl->size++;
            return 0;
        }
    }

    return -1;
}

int ohtbl_remove(OHTbl *htbl, void **data)
{
    int i, position;

    for (i = 0; i < htbl->positions; i++)
    {   
        position = (htbl->h1(*data) + (i * htbl->h2(*data))) % htbl->positions;
        if (htbl->table[position] == NULL)
            return -1;

        if (htbl->table[position] == htbl->vacated)
            continue;

        if (htbl->match(htbl->table[position], *data))
        {
            *data = htbl->table[position];
            htbl->table[position] = htbl->vacated;
            htbl->size--;
            return 0;
        }
    }

    return -1;
}

int ohtbl_lookup(const OHTbl *htbl, void **data)
{
    int i, position;
    for (i = 0; i < htbl->positions; i++)
    {   
        position = (htbl->h1(*data) + (i * htbl->h2(*data))) % htbl->positions;
        if (htbl->table[position] == NULL)
            return -1;
        else if (htbl->match(htbl->table[position], *data))
        {   
            *data = htbl->table[position];
            return 0;
        }
    }

    return -1;
}

int match(const void *k1, const void *k2)
{
    return *(int *)k1 == *(int *)k2;
}

int hash1(const void *key)
{   
    return (*(const int *)key % O_HASHTBL_POSITIONS);
}

int hash2(const void *key)
{
    return (*(const int *)key % (O_HASHTBL_POSITIONS - 2));
}

void ohtbl_print(OHTbl *htbl)
{
    int i;
    for (i = 0; i < htbl->positions; i++)
    {
        printf("%d: ", i);
        if (htbl->table[i] == NULL)
            printf("NULL\n");
        else if (htbl->table[i] == htbl->vacated)
            printf("VACATED\n");
        else
            printf("%d\n", *((int *)htbl->table[i]));
    }
    printf("SIZE: %d\n", htbl->size);
}

int main()
{
    OHTbl *htbl = (OHTbl *)malloc(sizeof(OHTbl));
    ohtbl_init(htbl, O_HASHTBL_POSITIONS, hash1, hash2, match, free);
    //ohtbl_print(htbl);

    printf("[ 插入测试 ]\n");
    srand(time(0));

    int i, *pi, created_count = 10;
    for (i = 0; i < created_count; i++)
    {
        pi = (int *)malloc(sizeof(int));
        *pi = rand() % 100 + 1;
        if (ohtbl_insert(htbl, (void *)pi) == -1)
            printf("insert error\n");
    }
    ohtbl_print(htbl);

    int remove_count = 10;
    for (i = 0; i < remove_count; i++)
    {
        pi = (int *)malloc(sizeof(int));
        *pi = rand() % 100 + 1;
        if (ohtbl_remove(htbl, (void **)&pi) == 0)
        {
            printf("Remove [%d] from hash table\n", *pi);
            free(pi);
        }
        else
            printf("Not Found [%d] in hash table\n", *pi);
    }
    ohtbl_print(htbl);

    ohtbl_destroy(htbl);
    ohtbl_print(htbl);

    return 0;
}
