#include "stdbool.h"
typedef struct TreeNode{
    struct TreeNode* parent;
    struct TreeNode* head;
    struct TreeNode* tail;
    struct TreeNode* sibling;
    struct Symbol *symbol;
} TreeNode;

TreeNode* ParseTree;
/* typedef struct LinkedList LinkedList; */
