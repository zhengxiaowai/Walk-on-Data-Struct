#include <stdlib.h>
#include <stdio.h>

#include "set.h"

void set_init(Set *set,
              int (*match)(const void *key1, const void *key2),
              void (*destroy)(void *data))
{
    list_init(set, destroy);
    set->match = match;

    return;
}

int set_insert(Set *set, const void *data)
{
    if (set_is_member(set, data))
        return 1;

    return list_ins_next(set, list_tail(set), data);
}

int set_remove(Set *set, void **data)
{
    ListElmt *member, *prev;

    for (member = list_head(set); member != NULL; member = list_next(member))
    {
        if (set->match(*data, list_data(member)))
            break;

        prev = member;
    }

    // not found
    if (member == NULL)
        return -1;
    
    return list_rem_next(set, prev, data);
}

int set_union(Set *setu, const Set *set1, const Set *set2)
{
    // 并集
    ListElmt *member;
    void *data;

    // 1. 初始化 setu
    set_init(setu, setu->match, NULL);

    // 2. 拷贝 set1 到 setu
    for (member = list_head(set1); member != NULL; member = list_next(member))
    {
        data = list_data(member);
        if (list_ins_next(setu, list_tail(setu), data) != 0)
        {
            set_destroy(setu);
            return -1;
        }
    }

    // 3. 拷贝 set2 到 setu，需要判断成员是否存在
    for (member = list_head(set2); member != NULL; member = list_next(member))
    {
        if (set_is_member(set1, list_data(member)))
            continue;

        data = list_data(member);
        if (list_ins_next(setu, list_tail(setu), data) != 0)
        {
            set_destroy(setu);
            return -1;
        }
    }

    return 0;
}

int set_intersection(Set *seti, const Set *set1, const Set *set2)
{
    // 交集
    ListElmt *member;
    void *data;

    // 1. 初始化 seti
    set_init(seti, seti->match, NULL);

    // 2. 拷贝 set1 到 seti，set1 中成员存在 set2 中
    for (member = list_head(set1); member != NULL; member = list_next(member))
    {
        if (set_is_member(set2, list_data(member)))
        {
            data = list_data(member);
            if (list_ins_next(seti, list_tail(seti), data) != 0)
            {
                set_destroy(seti);
                return -1;
            }
        }
    }

    return 0;
}

int set_difference(Set *setd, const Set *set1, const Set *set2)
{
    // 差集
    ListElmt *member;
    void *data;

    // 1. 初始化 setd
    set_init(setd, setd->match, NULL);

    // 2. 拷贝 set1 到 setd，set1 中成员不存在 set2 中
    for (member = list_head(set1); member != NULL; member = list_next(member))
    {
        if (!set_is_member(set2, list_data(member)))
        {
            data = list_data(member);
            if (list_ins_next(setd, list_tail(setd), data) != 0)
            {
                set_destroy(setd);
                return -1;
            }
        }
    }

    return 0;
}

int set_is_member(const Set *set, const void *data)
{
    ListElmt *member;
    for (member = list_head(set); member != NULL; member = list_next(member))
    {
        if (set->match(data, list_data(member)))
            return 1;
    }

    return 0;
}

int set_is_subset(const Set *set1, const Set *set2)
{
    ListElmt *member;

    if (set_size(set1) > set_size(set2))
        return 0;

    for (member = list_head(set1); member != NULL; member = list_next(member))
    {
        if (!set_is_member(set2, list_data(member)))
            return 0;
    }

    return 1;
}

int set_is_equal(const Set *set1, const Set *set2)
{
    if (set_size(set1) != set_size(set2))
        return 0;

    return set_is_subset(set1, set2);
}

int match_integer(const void *key1, const void *key2)
{
    int int_key1 = *(int *)key1;
    int int_key2 = *(int *)key2;
    return int_key1 == int_key2;
}

int main()
{
    Set *set = (Set *)malloc(sizeof(Set));

    // test set_init
    set_init(set, match_integer, free);
    printf("set_init: ");
    set_traverse(set);

    // test set_insert
    int first_data = 1, second_data = 2, third_data = 3, fourth_data = 4;
    int *p_first_data, *p_second_data, *p_third_data, *p_fourth_data;
    p_first_data = (int *)malloc(sizeof(int));
    p_second_data = (int *)malloc(sizeof(int));
    p_third_data = (int *)malloc(sizeof(int));
    p_fourth_data = (int *)malloc(sizeof(int));
    *p_first_data = first_data;
    *p_second_data = second_data;
    *p_third_data = third_data;
    *p_fourth_data = fourth_data;

    set_insert(set, (void *)p_first_data);
    set_insert(set, (void *)p_second_data);
    set_insert(set, (void *)p_third_data);
    set_insert(set, (void *)p_fourth_data);
    set_insert(set, (void *)p_first_data);
    printf("set_insert: ");
    set_traverse(set);

    // test set_remove
    int three = 3, four = 4, *p_three, *p_four;
    p_three = (int *)malloc(sizeof(int));
    p_four = (int *)malloc(sizeof(int));

    p_three = &three;
    p_four = &four;
    set_remove(set, (void **)&p_three);
    set_remove(set, (void **)&p_four);
    printf("set_remove: ");
    set_traverse(set);

    
    Set *setu = (Set *)malloc(sizeof(Set));
    Set *seti = (Set *)malloc(sizeof(Set));
    Set *setd = (Set *)malloc(sizeof(Set));
    Set *set1 = (Set *)malloc(sizeof(Set));
    Set *set2 = (Set *)malloc(sizeof(Set));
    set_init(setu, match_integer, free);
    set_init(seti, match_integer, free);
    set_init(setd, match_integer, free);
    set_init(set1, match_integer, free);
    set_init(set2, match_integer, free);

    int uone = 1, utwo = 2, uthree = 3, ufour = 4, ufive = 5;
    int *up_one = (int *)malloc(sizeof(int));
    int *up_two = (int *)malloc(sizeof(int));
    int *up_three = (int *)malloc(sizeof(int));
    int *up_four = (int *)malloc(sizeof(int));
    int *up_five = (int *)malloc(sizeof(int));
    *up_one = uone;
    *up_two = utwo;
    *up_three = uthree;
    *up_four = ufour;
    *up_five = ufive;
    
    set_insert(set1, (void *)up_one);
    set_insert(set1, (void *)up_two);
    set_insert(set1, (void *)up_five);

    set_insert(set2, (void *)up_one);
    set_insert(set2, (void *)up_two);
    set_insert(set2, (void *)up_three);
    set_insert(set2, (void *)up_four);

    // test set_union
    if (set_union(setu, set1, set2) == -1)
    {
        printf("set_union error\n");
    }
    else
    {
        printf("set_union: ");
        set_traverse(setu);
    }
    
    // test set_intersection
    if (set_intersection(seti, set1, set2) == -1)
    {
        printf("set_intersection error\n");
    }
    else
    {
        printf("set_intersection: ");
        set_traverse(seti);
    }

    // test set_difference
    if (set_difference(setd, set1, set2) == -1)
    {
        printf("set_difference error\n");
    }
    else
    {
        printf("set_difference: ");
        set_traverse(setd);
    }

    // test set_is_subset
    if (set_is_subset(seti, setu))
        printf("seti belong to setu\n");
    
    // test set_is_equal
    if (set_is_subset(seti, set))
        printf("seti equal to set\n");

    
    // test set_destroy
    set_destroy(set);
    printf("set_destroy: ");
    set_traverse(set);

}