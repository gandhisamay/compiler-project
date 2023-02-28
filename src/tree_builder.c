#include "parser_table.c"

// void extend_tree(TreeNode* parent, Symbol* sym)
// {
// }

TreeNode* next_node(TreeNode* node, Symbol* sym)
{   
    // printf("next node called...1\n");
    bool node_found = false;
    if (node->symbol->terminal == $)
    {
        // printf("next node called...2\n");

        node = NULL;
    }
    else if (node->symbol->is_terminal)
    {   
        // printf("next node called...3\n");

        if (node->sibling != NULL){
            node = node->sibling;
            node_found = true;
        }
        else while (!node_found)
        {
            node = node->parent;
            if (node->sibling != NULL){
                node = node->sibling;
                node_found = true;
            }
        }
    }
    else
    {
        // printf("next node called...4\n");

        insert_child(node, sym);
        node = node->head;
        node_found = true;
        // printf("node: %s\n",node->symbol->name);

        // printf("next node called...5\n");

    }
    return node;
}

