#include <stdlib.h>
#include <string.h>
#include "bistree.h"

#define LEFT 0
#define RIGHT 1

static void destroy_left(BisTree *tree, BiTreeNode *node)
{
    return destroy_subtree(LEFT, tree, node)     
}

static void destroy_right(BisTree *tree, BiTreeNode *node)
{
    return destroy_subtree(RIGHT, tree, node)     
}

static void destroy_subtree(int subtree, BisTree *tree, BiTreeNode *node)
{
    BiTreeNode **position;
    

    if (bitree_size(tree) == 0) 
        return;

    if (node == NULL)
        *position = &(tree->root);
    else
    {
        if (subtree == LEFT)
            position = &(tree->left);
        else if (subtree == RIGHT)
            position = &(tree->right);
        else
            return;
    }

    if (*position != NULL)
    {
        destroy_left(tree, *position);
        destroy_right(tree, *position);

        if (tree->destroy != NULL)
            tree->destroy(((AvlNode *)(*position)->data)->data);

        free((*position)->data);
        free(*position);
        tree->size--;
    }

    return;
}

static int insert(BisTree *tree, BiTreeNode **node, const void *data, int *balanced)
{
    AvlNode *avl_data;
    int cmpval, retval;
    
    if (bitree_iseob(*node))
    {
        // 插入一个空树
        if ((avl_data = (AvlNode *)malloc(sizeof(AvlNode))) == NULL)
            return -1;

        avl_data->factor = AVL_BALANCED;
        avl_data->hidden = 0;
        avl_data->data = (void *)data;


        return bitree_ins_left(tree, *node , avl_data);
    }
    else
    {
        cmpval = tree->compare(data, ((AvlNode *)bitree_data(*node))->data); 
        if (cmpval < 0)
        {
            if (bitree_is_eob(bitree_left(*node)))                      
            {
                if ((avl_data = (AvlNode *)malloc(sizeof(AvlNode))) == NULL) 
                    return -1;

                avl_data->factor = AVL_BALANCED;
                avl_data->hidden= 0;
                avl_data->data = (void *)data;
                
               if (bitree_ins_left(tree, *node, avl_data) != 0) 
                   return -1;
                
                *balanced = 0;
            }
            else
            {
                if ((retval = insert(tree, &bitree_left(*node), data, balanced)) !=0)       
                    return retval;
            
            }

            if (!(*balanced))
            {
                switch (((AvlNode *)bitree_data(*node))0>factor)
                {
                    // TODO
                    //case AVL_LFT_HEAVY:

                }
            }
        }

    
    }
}


void bistree_init(BisTree *tree, int (*compare)(const void *key1, const void *key2), void (*destroy)(void *data))
{
    bitree_init(tree, destroy);
    tree->compare = compare;

    return;
}
void bistree_destroy(BisTree *tree)
{

    destroy_left(tree, NULL);

    memnset(tree, 0, sizeof(BisTree))
    return;
}
int bistree_insert(BisTree *tree, const void *data)
{

}
int bistree_remove(BisTree *tree, const void *data)
{

}
int bistree_lookup(BisTree *tree, void **data)
{

}




