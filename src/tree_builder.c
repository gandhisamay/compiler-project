#include "parser_table.c"

// void extend_tree(TreeNode* parent, Symbol* sym)
// {
// }

TreeNode *error_node(TreeNode *node)
{   
    // printf("in error, pre: %s\n",node->symbol->name);
    bool node_found = false;
    if (node->sibling != NULL)
    {
        node = node->sibling;
        node_found = true;
    }
    else
    {
        while (!node_found)
        {
            node = node->parent;
            if (node->sibling != NULL)
            {
                node = node->sibling;
                node_found = true;
            }
        }
    }
    // printf("in error, new: %s\n",node->symbol->name);
    return node;
}

TreeNode *next_node(TreeNode *node, Symbol *sym)
{
    // printf("next node called...1\n");
    // print_symbol_details(sym,stdout);
    bool node_found = false;
    // printf("in next, pre: %s\n",node->symbol->name);
    // printf("in next, sym: %s\n",sym->name);
    if (node->symbol->terminal == $)
    {
        // printf("next node called...2\n");

        node = NULL;
    }
    else if (node->symbol->is_terminal)
    {
        // printf("next node called...3\n");
        // print_symbol_details(sym,stdout);

        if (node->sibling != NULL)
        {
            node = node->sibling;
            node_found = true;
        }
        else
            while (!node_found)
            {
                node = node->parent;
                if (node->sibling != NULL)
                {
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
    // printf("in next, new: %s\n",node->symbol->name);
    return node;
}
