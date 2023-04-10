#include "scope.c"

AST_Node_List *create_AST_Node_list() {
  AST_Node_List *list = (AST_Node_List *)malloc(sizeof(AST_Node_List));
  list->head = NULL;
  list->tail = NULL;
  return list;
}
AST_Node *create_AST_Node(char *label, Symbol *data) {
  AST_Node *node = (AST_Node *)malloc(sizeof(AST_Node));
  // AST_Node *node = (AST_Node *)malloc(sizeof(AST_Node *));
  strcpy(node->label, label);
  node->data = data;
  node->next = NULL;
  node->token_set = 0;
  return node;
}
AST_Node *copy_AST_Node(AST_Node *node) {
  AST_Node *tmp = create_AST_Node(node->label, node->data);
  tmp->next = node->next;
  if (node->token_set == 1) {
    tmp->token_set = 1;
    tmp->token = node->token;
  }
  return tmp;
}
void insert_AST_head(AST_Node_List *list, AST_Node *astnode) {
  if (list->head == NULL) {
    list->head = astnode;
  } else {
    AST_Node *tmp = copy_AST_Node(astnode);
    tmp->next = list->head;
    list->head = tmp;
  }
}
void print_astnodes(TreeNode *node) {
  AST_Node *tmp = node->list->head;
  while (tmp != NULL) {
    print_astnode_details(tmp, stdout);
    tmp = tmp->next;
  }
}
void insert_AST_tail(AST_Node_List *AST_list, AST_Node *astnode) {
  if (AST_list->head == NULL) {
    AST_list->head = astnode;
  } else {
    AST_Node *curr = AST_list->head;
    while (curr->next != NULL) {
      curr = curr->next;
    }
    curr->next = copy_AST_Node(astnode);
  }
}
void append_helper(AST_Node_List *list1, AST_Node *node) {
  if (node->next == NULL) {
    AST_Node *temp = copy_AST_Node(node);
    insert_AST_head(list1, temp);
  } else {
    append_helper(list1, node->next);
    AST_Node *temp = copy_AST_Node(node);
    insert_AST_head(list1, temp);
  }
}
void append_AST_lists_tail(AST_Node_List *list1, AST_Node_List *list2) {
  if (list1->head == NULL) {
    list1->head = list2->head;
    // list1->tail = list2->tail;
  } else {
    AST_Node *temp1 = list1->head;
    AST_Node *temp2 = list2->head;
    while (temp1->next != NULL) {
      temp1 = temp1->next;
    }

    while (temp2 != NULL) {
      temp1->next = copy_AST_Node(temp2);
      temp1 = temp1->next;
      temp2 = temp2->next;
    }
    // free(temp);
  }
}
void append_AST_lists_head(AST_Node_List *list1, AST_Node_List *list2) {
  AST_Node *curr = list2->head;
  AST_Node *next;
  if (curr != NULL) {
    append_helper(list1, list2->head);
  } else {
    return;
  }
}

void resolve(TreeNode *node) {
  /* print_symbol_details(node->symbol, stdout); */
  if (TYPE_CHECKING == false) {
    node->list = create_AST_Node_list();
  }
  if (node->symbol->is_terminal) {
    if (TYPE_CHECKING == true) {
      node->node_type = find_symtable_el_by_id(
          find_scope(GLOBAL_SCOPE, node->token.line), node->token.id);
      return;
    } else if (node->symbol->terminal == iD) {
      AST_Node *ast_id = create_AST_Node("", node->symbol);
      ast_id->token = node->token;
      ast_id->token_set = 1;
      insert_AST_tail(node->list, ast_id);
    } else if (node->symbol->terminal == iNTEGER) {
      AST_Node *ast_id = create_AST_Node("", node->symbol);
      ast_id->token = node->token;
      ast_id->token_set = 1;
      insert_AST_tail(node->list, ast_id);
    } else if (node->symbol->terminal == rEAL) {
      AST_Node *ast_id = create_AST_Node("", node->symbol);
      ast_id->token = node->token;
      ast_id->token_set = 1;
      insert_AST_tail(node->list, ast_id);
    } else if (node->symbol->terminal == bOOLEAN) {
      AST_Node *ast_id = create_AST_Node("", node->symbol);
      ast_id->token = node->token;
      ast_id->token_set = 1;
      insert_AST_tail(node->list, ast_id);
    } else if (node->symbol->terminal == nUM) {
      AST_Node *ast_id = create_AST_Node("", node->symbol);
      ast_id->token = node->token;
      ast_id->token_set = 1;
      insert_AST_tail(node->list, ast_id);
    } else if (node->symbol->terminal == rNUM) {
      AST_Node *ast_id = create_AST_Node("", node->symbol);
      ast_id->token = node->token;
      ast_id->token_set = 1;
      insert_AST_tail(node->list, ast_id);
    }
    // else if (node->symbol->terminal == aND)
    // {
    //     AST_Node *ast_id = create_AST_Node("", node->symbol);
    //     ast_id->token = node->token;
    //     ast_id->token_set = 1;
    //     insert_AST_tail(node->list, ast_id);
    // }
    // else if (node->symbol->terminal == oR)
    // {
    //     AST_Node *ast_id = create_AST_Node("", node->symbol);
    //     ast_id->token = node->token;
    //     ast_id->token_set = 1;
    //     insert_AST_tail(node->list, ast_id);
    // }
    // else if (node->symbol->terminal == mUL)
    // {
    //     AST_Node *ast_id = create_AST_Node("", node->symbol);
    //     ast_id->token = node->token;
    //     ast_id->token_set = 1;
    //     insert_AST_tail(node->list, ast_id);
    // }
    // else if (node->symbol->terminal == dIV)
    // {
    //     AST_Node *ast_id = create_AST_Node("", node->symbol);
    //     ast_id->token = node->token;
    //     ast_id->token_set = 1;
    //     insert_AST_tail(node->list, ast_id);
    // }
    else if (node->symbol->terminal == pLUS) {
      AST_Node *ast_id = create_AST_Node("", node->symbol);
      ast_id->token = node->token;
      ast_id->token_set = 1;
      insert_AST_tail(node->list, ast_id);
    } else if (node->symbol->terminal == mINUS) {
      AST_Node *ast_id = create_AST_Node("", node->symbol);
      ast_id->token = node->token;
      ast_id->token_set = 1;
      insert_AST_tail(node->list, ast_id);
    } else if (node->symbol->terminal == tRUE) {
      AST_Node *ast_id = create_AST_Node("", node->symbol);
      ast_id->token = node->token;
      ast_id->token_set = 1;
      insert_AST_tail(node->list, ast_id);
    } else if (node->symbol->terminal == fALSE) {
      AST_Node *ast_id = create_AST_Node("", node->symbol);
      ast_id->token = node->token;
      ast_id->token_set = 1;
      insert_AST_tail(node->list, ast_id);
    }
    // else if (node->symbol->terminal == lT)
    // {
    //     AST_Node *ast_id = create_AST_Node("", node->symbol);
    //     ast_id->token = node->token;
    //     ast_id->token_set = 1;
    //     insert_AST_tail(node->list, ast_id);
    // }
    // else if (node->symbol->terminal == lE)
    // {
    //     AST_Node *ast_id = create_AST_Node("", node->symbol);
    //     ast_id->token = node->token;
    //     ast_id->token_set = 1;
    //     insert_AST_tail(node->list, ast_id);
    // }
    // else if (node->symbol->terminal == gE)
    // {
    //     AST_Node *ast_id = create_AST_Node("", node->symbol);
    //     ast_id->token = node->token;
    //     ast_id->token_set = 1;
    //     insert_AST_tail(node->list, ast_id);
    // }
    // else if (node->symbol->terminal == gT)
    // {
    //     AST_Node *ast_id = create_AST_Node("", node->symbol);
    //     ast_id->token = node->token;
    //     ast_id->token_set = 1;
    //     insert_AST_tail(node->list, ast_id);
    // }
    // else if (node->symbol->terminal == eQ)
    // {
    //     AST_Node *ast_id = create_AST_Node("", node->symbol);
    //     ast_id->token = node->token;
    //     ast_id->token_set = 1;
    //     insert_AST_tail(node->list, ast_id);
    // }
    // else if (node->symbol->terminal == nE)
    // {
    //     AST_Node *ast_id = create_AST_Node("", node->symbol);
    //     ast_id->token = node->token;
    //     ast_id->token_set = 1;
    //     insert_AST_tail(node->list, ast_id);
    // }
  } else {
    if (node->head == NULL) {
      return;
    } else if (node->symbol->non_terminal == Program) {
      if (TYPE_CHECKING == false) {
        resolve(node->head); // ModuleDeclarations
        AST_Node *main_program = create_AST_Node("MAINPROGRAM", NULL);
        AST_Node *module_declarations =
            create_AST_Node("MODULEDECLARATIONS", NULL);
        AST_Node *module_definitions =
            create_AST_Node("MODULEDEFINITIONS", NULL);
        AST_Node *module_definitions1 =
            create_AST_Node("MODULEDEFINITIONS", NULL);
        AST_Node *module_declarations_end =
            create_AST_Node("MODULEDECLARATIONS_END", NULL);
        AST_Node *module_definitions_end =
            create_AST_Node("MODULEDEFINITIONS_END", NULL);
        AST_Node *module_definitions_end1 =
            create_AST_Node("MODULEDEFINITIONS_END", NULL);
        insert_AST_head(node->list, main_program);
        insert_AST_tail(node->list, module_declarations);
        append_AST_lists_tail(node->list,
                              node->head->list); // append ModuleDeclarations
        insert_AST_tail(node->list, module_declarations_end);
        insert_AST_tail(node->list, module_definitions);
        resolve(node->head->sibling); // OtherModules
        append_AST_lists_tail(node->list,
                              node->head->sibling->list); // append OtherModules
        insert_AST_tail(node->list, module_definitions_end);
        resolve(node->head->sibling->sibling); // DriverModule
        append_AST_lists_tail(
            node->list,
            node->head->sibling->sibling->list); // append DriverModule
        insert_AST_tail(node->list, module_definitions1);
        resolve(node->tail); // OtherModules1
        append_AST_lists_tail(node->list,
                              node->tail->list); // append OtherModules1
        insert_AST_tail(node->list, module_definitions_end1);
      } else {
        resolve(node->head->sibling);          // OtherModules
        resolve(node->head->sibling->sibling); // DriverModule
        resolve(node->tail);                   // OtherModules1
      }
    } else if (node->symbol->non_terminal == ModuleDeclarations) {
      if (TYPE_CHECKING == false) {
        if (node->head->sibling == NULL) {
          // ModuleDeclarations => #
        } else {
          resolve(node->tail); // ModuleDeclarations1 child
          resolve(node->head); // ModuleDeclaration
          append_AST_lists_head(node->list, node->tail->list);
          append_AST_lists_head(node->list, node->head->list);
        }
      } else {
      }
    } else if (node->symbol->non_terminal == ModuleDeclaration) {
      if (TYPE_CHECKING == false) {
        resolve(node->head->sibling->sibling); // iD
        insert_AST_head(node->list, node->head->sibling->sibling->list->head);
      } else {
      }
    } else if (node->symbol->non_terminal == OtherModules) {
      if (TYPE_CHECKING == false) {
        if (node->head->sibling == NULL) {
          // OtherModules => #
        } else {
          resolve(node->tail); // OtherModules1 child
          resolve(node->head); // Module
          append_AST_lists_tail(node->list, node->tail->list);
          append_AST_lists_head(node->list, node->head->list);
        }
      } else {
        resolve(node->tail); // OtherModules1 child
        resolve(node->head); // Module
      }
    } else if (node->symbol->non_terminal == Module) {
      if (TYPE_CHECKING == false) {
        AST_Node *module = create_AST_Node("MODULE", NULL);
        AST_Node *input_plist = create_AST_Node("INPUT_PARAMETERS_LIST", NULL);
        AST_Node *module_end = create_AST_Node("MODULE_END", NULL);
        AST_Node *input_plist_end =
            create_AST_Node("INPUT_PARAMETERS_LIST_END", NULL);
        insert_AST_head(node->list, module);
        // resolve and add ID
        resolve(node->head->sibling->sibling); // iD
        insert_AST_tail(node->list,
                        node->head->sibling->sibling->list->head); // insert iD
        // resolve and add Input_plist
        resolve(node->head->sibling->sibling->sibling->sibling->sibling->sibling
                    ->sibling); // Input_plist
        insert_AST_tail(node->list, input_plist);
        append_AST_lists_tail(
            node->list, node->head->sibling->sibling->sibling->sibling->sibling
                            ->sibling->sibling->list); // insert plist
        insert_AST_tail(node->list, input_plist_end);

        CURR_OFFSET = 0;
        int start_line = node->tail->head->token.line;
        Scope *module_scope = find_scope(GLOBAL_SCOPE, start_line);
        module_scope->is_a_module = true;
        strcpy(module_scope->module_name,
               node->head->sibling->sibling->list->head->token.id);
        // input_plist
        AST_Node *tmp =
            copy_AST_Node(node->head->sibling->sibling->sibling->sibling
                              ->sibling->sibling->sibling->list->head);
        while (tmp != NULL) {
          if (strcmp(tmp->next->label, "ARRAY") == 0) {
            int start;
            int end;
            char *id = tmp->token.id;
            terminals type = tmp->next->next->token.name;
            int nUM_or_iD = 1;
            if (tmp->next->next->next->next->next->data->terminal == mINUS) {
              if (tmp->next->next->next->next->next->next->token.name == nUM) {
                start = 0 - tmp->next->next->next->next->next->next->token.num;
                tmp = tmp->next->next->next->next->next->next->next->next;
              } else {
                nUM_or_iD = 0;
                tmp = tmp->next->next->next->next->next->next->next->next;
              }

            } else if (tmp->next->next->next->next->next->data->terminal ==
                       pLUS) {
              if (tmp->next->next->next->next->next->next->token.name == nUM) {
                start = tmp->next->next->next->next->next->next->token.num;
                tmp = tmp->next->next->next->next->next->next->next->next;
              } else {
                nUM_or_iD = 0;
                tmp = tmp->next->next->next->next->next->next->next->next;
              }
            } else {
              if (tmp->next->next->next->next->next->token.name == nUM) {
                start = tmp->next->next->next->next->next->token.num;
                tmp = tmp->next->next->next->next->next->next->next;
              } else {
                nUM_or_iD = 0;
                tmp = tmp->next->next->next->next->next->next->next;
              }
            }

            if (tmp->data->terminal == mINUS) {
              if (tmp->next->token.name == nUM) {
                end = 0 - tmp->next->token.num;
                tmp = tmp->next->next;
              } else {
                nUM_or_iD = 0;
                tmp = tmp->next->next;
              }
            } else if (tmp->data->terminal == pLUS) {
              if (tmp->next->token.name == nUM) {
                end = tmp->next->token.num;
                tmp = tmp->next->next;
              } else {
                nUM_or_iD = 0;
                tmp = tmp->next->next;
              }
            } else {
              if (tmp->token.name == nUM) {
                end = tmp->token.num;
                tmp = tmp->next;
              } else {
                nUM_or_iD = 0;
                tmp = tmp->next;
              };
            }
            SYMBOL_TABLE_ELEMENT *temp = create_symbol_table_element(
                id, true, type, start, end, CURR_OFFSET, start_line);
            // ID = ID->next;
            // printf("\n :-------: \n");
            // print_symbol_table(find_scope(GLOBAL_SCOPE, start_line)->table);
            if (nUM_or_iD) {
              if (type == iNTEGER) {
                CURR_OFFSET += 4 * (end - start + 1);
              } else if (type == rEAL) {
                CURR_OFFSET += 8 * (end - start + 1);
              } else if (type == bOOLEAN) {
                CURR_OFFSET += 2 * (end - start + 1);
              }
            } else {
            }
            // tmp = tmp->next->next->next->next->next->next->next->next;
            // tmp = tmp->next;
            temp->next_offset = CURR_OFFSET;
            insert_symbol_table(temp,
                                find_scope(GLOBAL_SCOPE, start_line)->table);
          } else {
            SYMBOL_TABLE_ELEMENT *temp = create_symbol_table_element(
                tmp->token.id, false, tmp->next->token.name, 0, 0, CURR_OFFSET,
                start_line);
            if (tmp->next->token.name == iNTEGER) {
              CURR_OFFSET += 4;
            } else if (tmp->next->token.name == rEAL) {
              CURR_OFFSET += 8;
            } else if (tmp->next->token.name == bOOLEAN) {
              CURR_OFFSET += 2;
            }
            temp->next_offset = CURR_OFFSET;
            insert_symbol_table(temp,
                                find_scope(GLOBAL_SCOPE, start_line)->table);
            tmp = tmp->next;
            if (tmp != NULL)
              tmp = tmp->next;
          }
        }

        /* printf("\nAFTER_IPLIST_MODULE_OFFSET = %d\n", CURR_OFFSET); */
        find_scope(GLOBAL_SCOPE, start_line)->iplist_offset = CURR_OFFSET;

        // resolve and add Return_plist
        resolve(node->head->sibling->sibling->sibling->sibling->sibling->sibling
                    ->sibling->sibling->sibling->sibling); // RET
        append_AST_lists_tail(
            node->list,
            node->head->sibling->sibling->sibling->sibling->sibling->sibling
                ->sibling->sibling->sibling->sibling->list); // insert RET

        // output_plist
        if (node->head->sibling->sibling->sibling->sibling->sibling->sibling
                ->sibling->sibling->sibling->sibling->head->sibling ==
            NULL) { // ret
        } else {
          AST_Node *tmp = copy_AST_Node(
              node->head->sibling->sibling->sibling->sibling->sibling->sibling
                  ->sibling->sibling->sibling->sibling->head->sibling->sibling
                  ->list->head); // output_plist
          while (tmp != NULL) {
            SYMBOL_TABLE_ELEMENT *temp = create_symbol_table_element(
                tmp->token.id, false, tmp->next->token.name, 0, 0, CURR_OFFSET,
                start_line);
            if (tmp->next->token.name == iNTEGER) {
              CURR_OFFSET += 4;
            } else if (tmp->next->token.name == rEAL) {
              CURR_OFFSET += 8;
            } else if (tmp->next->token.name == bOOLEAN) {
              CURR_OFFSET += 2;
            }
            temp->next_offset = CURR_OFFSET;
            insert_symbol_table(temp,
                                find_scope(GLOBAL_SCOPE, start_line)->table);
            tmp = tmp->next;
            if (tmp != NULL)
              tmp = tmp->next;
          }
        }

        /* printf("\nAFTER_OPLIST_MODULE_OFFSET = %d\n", CURR_OFFSET); */
        find_scope(GLOBAL_SCOPE, start_line)->oplist_offset = CURR_OFFSET;

        // resolve and add ModuleDef
        resolve(node->head->sibling->sibling->sibling->sibling->sibling->sibling
                    ->sibling->sibling->sibling->sibling->sibling); // ModuleDef
        append_AST_lists_tail(node->list,
                              node->head->sibling->sibling->sibling->sibling
                                  ->sibling->sibling->sibling->sibling->sibling
                                  ->sibling->sibling->list); // insert ModuleDef

        // Scope *scope = find_scope(GLOBAL_SCOPE, node->head->token.line); //
        // line no of 'dECLARE' SYMBOL_TABLE_ELEMENT **table = scope->table; if
        // (node->head->sibling->sibling->sibling->sibling->sibling->sibling->sibling->head->sibling->sibling
        // == NULL){ // Not Array
        //     AST_Node *ID = node->head->sibling->list->head;
        //     while (ID != NULL)
        //     {
        //         // print_astnode_details(ID, stdout);
        //         // TODO: FIX Offset
        //         SYMBOL_TABLE_ELEMENT *el =
        //         create_symbol_table_element(ID->token.id, false,
        //         ID->token.name, 0, 0, 0, ID->token.line);
        //         insert_symbol_table(el, scope->table);
        //         ID = ID->next;
        //     }
        // }
        // else { // Is an Array
        //     TreeNode *range_array =
        //     node->head->sibling->sibling->sibling->head->sibling->sibling;
        //     int start, end;
        //     // Start Index_arr
        //     if (range_array->head->head->sibling == NULL){              //
        //     Index_arr => New_index
        //         if (range_array->head->head->head->token.name == nUM){
        //             start = range_array->head->head->head->token.num;
        //         } else { // iD type

        //         }
        //     } else {                                                    //
        //     Index_arr => Sign New_index
        //         if (range_array->head->head->head->token.name == pLUS){
        //             if (range_array->head->head->sibling->head->token.name ==
        //             nUM){
        //                 start =
        //                 range_array->head->head->sibling->head->token.num;
        //             } else { // iD type

        //             }
        //         } else { // mINUS
        //             if (range_array->head->head->sibling->head->token.name ==
        //             nUM){
        //                 start = 0 -
        //                 range_array->head->head->sibling->head->token.num;
        //             } else { // iD type

        //             }
        //         }
        //     }
        //     // End Index_arr
        //     if (range_array->head->sibling->sibling->head->sibling == NULL){
        //     // Index_arr => New_index
        //         if
        //         (range_array->head->sibling->sibling->head->head->token.name
        //         == nUM){
        //             end =
        //             range_array->head->sibling->sibling->head->head->token.num;
        //         } else { // iD type

        //         }
        //     } else {                                                    //
        //     Index_arr => Sign New_index
        //         if
        //         (range_array->head->sibling->sibling->head->head->token.name
        //         == pLUS){
        //             if
        //             (range_array->head->sibling->sibling->head->sibling->head->token.name
        //             == nUM){
        //                 end =
        //                 range_array->head->sibling->sibling->head->sibling->head->token.num;
        //             } else { // iD type

        //             }
        //         } else { // mINUS
        //             if
        //             (range_array->head->sibling->sibling->head->sibling->head->token.name
        //             == nUM){
        //                 end = 0 -
        //                 range_array->head->sibling->sibling->head->sibling->head->token.num;
        //             } else { // iD type

        //             }
        //         }
        //     }
        //     AST_Node *ID = node->head->sibling->list->head;
        //     while(ID != NULL){
        //         // printf("\n_________________ start %d end %d\n",start,
        //         end);
        //         // print_astnode_details(ID, stdout);
        //         // TODO: FIX Offset
        //         SYMBOL_TABLE_ELEMENT *el =
        //         create_symbol_table_element(ID->token.id, true,
        //         ID->token.name, start, end, 0, ID->token.line);
        //         insert_symbol_table(el, scope->table);
        //         ID = ID->next;
        //     }
        // }
        printf("\n Module Scope Symbol Table ------------------ \n");
        // printf("\n :-------: \n");
        print_symbol_table(find_scope(GLOBAL_SCOPE, start_line)->table);
        insert_AST_tail(node->list, module_end);
      } else {
        resolve(node->head->sibling->sibling); // iD
        resolve(node->head->sibling->sibling->sibling->sibling->sibling->sibling
                    ->sibling); // Input_plist
        resolve(node->head->sibling->sibling->sibling->sibling->sibling->sibling
                    ->sibling->sibling->sibling->sibling); // RET
        resolve(node->head->sibling->sibling->sibling->sibling->sibling->sibling
                    ->sibling->sibling->sibling->sibling->sibling); // ModuleDef
      }
    } else if (node->symbol->non_terminal == Ret) {
      if (TYPE_CHECKING == false) {
        AST_Node *return_plist =
            create_AST_Node("RETURN_PARAMETERS_LIST", NULL);
        AST_Node *return_plist_end =
            create_AST_Node("RETURN_PARAMETERS_LIST_END", NULL);

        insert_AST_tail(node->list, return_plist);
        if (node->head->sibling == NULL) {
          // Ret => #
        } else {
          resolve(node->head->sibling->sibling); // Output_plist
          append_AST_lists_tail(
              node->list,
              node->head->sibling->sibling->list); // insert Output_plist
        }
        insert_AST_tail(node->list, return_plist_end);
      } else {
      }
    } else if (node->symbol->non_terminal == Input_plist) {
      if (TYPE_CHECKING == false) {
        resolve(node->head);                            // iD
        resolve(node->head->sibling->sibling);          // Type
        resolve(node->head->sibling->sibling->sibling); // N1
        append_AST_lists_tail(
            node->list,
            node->head->sibling->sibling->sibling->list); // appending to N1
        append_AST_lists_head(
            node->list,
            node->head->sibling->sibling->list); // append Type at head to N1
        insert_AST_head(node->list,
                        node->head->list->head); // insert iD at head to N1
      } else {
      }
    } else if (node->symbol->non_terminal == Output_plist) {
      if (TYPE_CHECKING == false) {
        resolve(node->head);                            // iD
        resolve(node->head->sibling->sibling);          // Type
        resolve(node->head->sibling->sibling->sibling); // N2
        append_AST_lists_tail(
            node->list,
            node->head->sibling->sibling->sibling->list); // appending to N2
        insert_AST_head(node->list, node->head->sibling->sibling->list
                                        ->head); // insert type at head to N2
        insert_AST_head(node->list,
                        node->head->list->head); // insert iD at head to N2
      } else {
      }
    } else if (node->symbol->non_terminal == DataType) {
      if (TYPE_CHECKING == false) {
        if (node->head->sibling == NULL) {
          AST_Node *type = create_AST_Node("", node->head->symbol);
          type->token_set = 1;
          type->token = node->head->token;
          insert_AST_head(node->list, type);
        } else {
          AST_Node *array = create_AST_Node("ARRAY", node->head->symbol);
          insert_AST_head(node->list, array);
          resolve(node->tail);                                 // Type
          insert_AST_tail(node->list, node->tail->list->head); // add Type
          resolve(node->head->sibling->sibling);               // Range_arrays
          append_AST_lists_tail(
              node->list,
              node->head->sibling->sibling->list); // append Range_arrays
        }
      } else {
      }
    } else if (node->symbol->non_terminal == Range_arrays) {
      if (TYPE_CHECKING == false) {
        resolve(node->head); // Index_arr1
        resolve(node->tail); // Index_arr2
        AST_Node *range = create_AST_Node("RANGE_ARRAY", node->head->symbol);
        insert_AST_head(node->list, range);
        append_AST_lists_tail(node->list,
                              node->head->list); // append Index_arr1
        append_AST_lists_tail(node->list,
                              node->tail->list); // append Index_arr2
      } else {
      }
    } else if (node->symbol->non_terminal == Index_arr) {
      if (TYPE_CHECKING == false) {
        AST_Node *range_index =
            create_AST_Node("RANGE_ARRAY_INDEX", node->head->symbol);
        insert_AST_head(node->list, range_index);
        if (node->head->sibling == NULL) {
          resolve(node->head); // New_index
          append_AST_lists_tail(node->list,
                                node->head->list); // append New_index
          /* AST_Node *new_index = create_AST_Node("",
           * node->head->head->symbol); */
          /* new_index->token_set = 1; */
          /* new_index->token = node->head->head->token; */
          /* insert_AST_tail(node->list, new_index); // insert new_index */
        } else {
          resolve(node->head);                                 // Sign
          resolve(node->head->sibling);                        // New_index
          append_AST_lists_tail(node->list, node->head->list); // append Sign
          append_AST_lists_tail(node->list,
                                node->head->sibling->list); // append New_index
          /* AST_Node *sign = create_AST_Node("", node->head->head->symbol); */
          /* sign->token_set = 1; */
          /* sign->token = node->head->head->token; */
          /* insert_AST_tail(node->list, sign); // insert sign */
          /* AST_Node *new_index = create_AST_Node("",
           * node->head->sibling->head->symbol); */
          /* new_index->token_set = 1; */
          /* new_index->token = node->head->sibling->head->token; */
          /* insert_AST_tail(node->list, new_index); // insert new_index */
        }
      } else {
      }
    } else if (node->symbol->non_terminal == Type) {
      if (TYPE_CHECKING == false) {
        AST_Node *type = create_AST_Node("", node->head->symbol);
        type->token_set = 1;
        type->token = node->head->token;
        insert_AST_head(node->list, type);
      } else {
      }
    } else if (node->symbol->non_terminal == N2) {
      if (TYPE_CHECKING == false) {
        if (node->head->sibling == NULL) {
          // N2 => #
        } else {
          resolve(node->tail);                            // N21 child
          resolve(node->head->sibling);                   // iD
          resolve(node->head->sibling->sibling->sibling); // Type
          append_AST_lists_tail(node->list,
                                node->tail->list); // N2.syn_list = N21.syn_list
          insert_AST_head(node->list,
                          node->head->sibling->sibling->sibling->list
                              ->head); // add type to list head
          insert_AST_head(
              node->list,
              node->head->sibling->list->head); // add iD to list head
        }
      } else {
      }
    } else if (node->symbol->non_terminal == N1) {
      if (TYPE_CHECKING == false) {
        if (node->head->sibling == NULL) {
          // N1 => #
        } else {
          resolve(node->tail);                            // N11 child
          resolve(node->head->sibling);                   // iD
          resolve(node->head->sibling->sibling->sibling); // Type
          append_AST_lists_tail(node->list,
                                node->tail->list); // N1.syn_list = N11.syn_list
          insert_AST_head(node->list,
                          node->head->sibling->sibling->sibling->list
                              ->head); // add type to list head
          insert_AST_head(
              node->list,
              node->head->sibling->list->head); // add iD to list head
        }
      } else {
      }
    } else if (node->symbol->non_terminal == DriverModule) {
      if (TYPE_CHECKING == false) {
        AST_Node *DRIVER = create_AST_Node("DRIVER", NULL);
        AST_Node *DRIVER_END = create_AST_Node("DRIVER_END", NULL);

        CURR_OFFSET = 0;
        insert_AST_tail(node->list, DRIVER);
        resolve(node->tail); // ModuleDef
        append_AST_lists_tail(node->list, node->tail->list);
        insert_AST_tail(node->list, DRIVER_END);
        // Driver Scope
        printf("\n Driver Scope Symbol Table ------------------ \n");
        Scope *driver_scope =
            find_scope(GLOBAL_SCOPE, node->tail->head->token.line);
        driver_scope->is_a_module = true;
        strcpy(driver_scope->module_name, "DRIVER_MODULE");
        print_symbol_table(driver_scope->table);
      } else {
        resolve(node->tail); // ModuleDef
      }
    } else if (node->symbol->non_terminal == ModuleDef) {
      if (TYPE_CHECKING == false) {
        AST_Node *STATEMENTS = create_AST_Node("STATEMENTS", NULL);
        AST_Node *STATEMENTS_END = create_AST_Node("STATEMENTS_END", NULL);
        insert_AST_tail(node->list, STATEMENTS);
        resolve(node->head->sibling); // Statements
        append_AST_lists_tail(node->list, node->head->sibling->list);
        insert_AST_tail(node->list, STATEMENTS_END);
      } else {
        resolve(node->head->sibling); // Statements
      }
    } else if (node->symbol->non_terminal == Statements) {
      if (TYPE_CHECKING == false) {
        if (node->head->sibling == NULL) { // Statements => #
                                           // node->list_head = NULL;
        } else {
          resolve(node->head); // Statement
          resolve(node->tail); // Statements1
          append_AST_lists_tail(node->list, node->tail->list);
          append_AST_lists_head(node->list, node->head->list);
        }
      } else {
        resolve(node->head); // Statement
        resolve(node->tail); // Statements1
      }
    } else if (node->symbol->non_terminal == Statement) {
      if (TYPE_CHECKING == false) {
        resolve(node->head); // Statement type (io/cond/iter/etc)
        append_AST_lists_tail(node->list, node->head->list);
        /* if (node->head->symbol == IoStmt){ */
        /*  */
        /* } else if (node->head->symbol == SimpleStmt){ */
        /*  */
        /* } else if (node->head->symbol == DeclareStmt){ */
        /*  */
        /* } else if (node->head->symbol == ConditionalStmt){ */
        /*  */
        /* } else if (node->head->symbol == IterativeStmt){ */
        /*  */
        /* } */
      } else {
        resolve(node->head); // Statement type (io/cond/iter/etc)
      }
    } else if (node->symbol->non_terminal == ConditionalStmt) {
      if (TYPE_CHECKING == false) {
        resolve(node->head->sibling->sibling); // iD
        AST_Node *switch_node = create_AST_Node("SWITCH", NULL);
        AST_Node *cases = create_AST_Node("CASES", NULL);
        AST_Node *switch_end = create_AST_Node("SWITCH_END", NULL);
        insert_AST_tail(node->list, switch_node); // insert SWITCH
        insert_AST_tail(node->list,
                        node->head->sibling->sibling->list->head); // insert iD
        insert_AST_tail(node->list, cases); // insert CASES
        resolve(node->head->sibling->sibling->sibling->sibling
                    ->sibling); // CaseStmts
        resolve(node->head->sibling->sibling->sibling->sibling->sibling
                    ->sibling); // Default
        append_AST_lists_tail(node->list,
                              node->head->sibling->sibling->sibling->sibling
                                  ->sibling->list); // appending CaseStmts
        append_AST_lists_tail(
            node->list, node->head->sibling->sibling->sibling->sibling->sibling
                            ->sibling->list); // appending Default
        insert_AST_tail(node->list, switch_end);
      } else {
        resolve(node->head->sibling->sibling->sibling->sibling
                    ->sibling); // CaseStmts
        resolve(node->head->sibling->sibling->sibling->sibling->sibling
                    ->sibling); // Default
      }
    } else if (node->symbol->non_terminal == CaseStmts) {
      if (TYPE_CHECKING == false) {
        AST_Node *stmts = create_AST_Node("STATEMENTS", NULL);
        AST_Node *stmts_end = create_AST_Node("STATEMENTS_END", NULL);
        AST_Node *case_node = create_AST_Node("CASE", NULL);
        resolve(node->head->sibling);                        // Value
        resolve(node->head->sibling->sibling->sibling);      // Statements
        resolve(node->tail);                                 // N9
        append_AST_lists_tail(node->list, node->tail->list); // append N9 list
        append_AST_lists_head(node->list,
                              node->head->sibling->sibling->sibling
                                  ->list);  // append Statements list to head
        insert_AST_head(node->list, stmts); // insert STATEMENTS to head
        insert_AST_head(
            node->list,
            node->head->sibling->list->head);   // insert Value to head
        insert_AST_head(node->list, case_node); // insert CASE to head
        insert_AST_tail(node->list,stmts_end);
      } else {
        resolve(node->head->sibling->sibling->sibling); // Statements
        resolve(node->tail);                            // N9
      }
    } else if (node->symbol->non_terminal == Value) {
      if (TYPE_CHECKING == false) {
        AST_Node *val = create_AST_Node("", node->head->symbol);
        val->token_set = 1;
        val->token = node->head->token;
        insert_AST_head(node->list, val);
      } else {
      }
    } else if (node->symbol->non_terminal == N9) {
      if (TYPE_CHECKING == false) {
        if (node->head->sibling == NULL) {
          // N9 => #
        } else {
          AST_Node *stmts = create_AST_Node("STATEMENTS", NULL);
          AST_Node *stmts_end = create_AST_Node("STATEMENTS_END", NULL);
          AST_Node *case_node = create_AST_Node("CASE", NULL);
          resolve(node->head->sibling);                   // Value
          resolve(node->head->sibling->sibling->sibling); // Statements
          resolve(node->tail);                            // N91 child
          append_AST_lists_tail(node->list,
                                node->tail->list); // append N91 child
          append_AST_lists_tail(node->list,
                                node->head->sibling->sibling->sibling
                                    ->list);  // append Statements to head
          insert_AST_head(node->list, stmts); // insert STATEMENTS to head
          insert_AST_head(
              node->list,
              node->head->sibling->list->head);   // insert Value to head
          insert_AST_head(node->list, case_node); // insert CASE to head
          insert_AST_tail(node->list,stmts_end);
        }
      } else {
        if (node->head->sibling != NULL) {
          resolve(node->head->sibling->sibling->sibling); // Statements
          resolve(node->tail);                            // N91 child
        }
      }
    } else if (node->symbol->non_terminal == Default) {
      if (TYPE_CHECKING == false) {
        if (node->head->sibling == NULL) {
          // Default => #
        } else {
          AST_Node *default_node = create_AST_Node("DEFAULTCASE", NULL);
          AST_Node *stmts = create_AST_Node("STATEMENTS", NULL);
          AST_Node *stmts_end = create_AST_Node("STATEMENTS_END", NULL);
          insert_AST_tail(node->list, default_node); // insert DEFAULTCASE
          insert_AST_tail(node->list, stmts);        // insert STATEMENTS
          resolve(node->head->sibling->sibling);     // Statements
          append_AST_lists_tail(
              node->list,
              node->head->sibling->sibling->list); // append Statements list
          insert_AST_tail(node->list,stmts_end);
        }
      } else {
        if (node->head->sibling != NULL) {
          resolve(node->head->sibling->sibling); // Statements
        }
      }
    } else if (node->symbol->non_terminal == IoStmt) {
      if (TYPE_CHECKING == false) {
        if (node->head->symbol->terminal == pRINT) {
          AST_Node *PRINT = create_AST_Node("PRINT", NULL);
          insert_AST_tail(node->list, PRINT);
          resolve(node->head->sibling->sibling); // Var_print
          append_AST_lists_tail(node->list, node->head->sibling->sibling->list);
        } else {
          AST_Node *GET_VALUE = create_AST_Node("GET_VALUE", NULL);
          insert_AST_tail(node->list, GET_VALUE);
          resolve(node->head->sibling->sibling); // iD
          insert_AST_tail(node->list, node->head->sibling->sibling->list->head);
        }
      } else {
      }
    } else if (node->symbol->non_terminal == Var_print) {
      if (TYPE_CHECKING == false) {
        if (node->head->sibling != NULL) {
          if (node->head->sibling->head->sibling == NULL) {      // only iD
            resolve(node->head);                                 // iD
            append_AST_lists_tail(node->list, node->head->list); // append iD
          } else { // iD with ARRAY_ACCESS
            AST_Node *array_access = create_AST_Node("ARRAY_ACCESS", NULL);
            resolve(node->head);                       // iD
            resolve(node->head->sibling);              // P1
            insert_AST_head(node->list, array_access); // insert ARRAY_ACCESS
            append_AST_lists_tail(node->list, node->head->list); // append iD
            append_AST_lists_tail(node->list,
                                  node->head->sibling->list); // append P1
          }
        } else {
          if (node->head->head == NULL) {
            resolve(node->head); // nUM/rNUM
            insert_AST_head(node->list,
                            node->head->list->head); // insert nUM/rNUM
          } else {
            resolve(node->head); // BoolConstt
            append_AST_lists_head(node->list,
                                  node->head->list); // append BoolConstt
          }
        }
      } else {
      }
    } else if (node->symbol->non_terminal == P1) {
      if (TYPE_CHECKING == false) {
        if (node->head->sibling == NULL) {
          // P1 => #
        } else {
          resolve(node->head->sibling); // Index_arr
          append_AST_lists_head(node->list,
                                node->head->sibling->list); // append Index_arr
        }
      } else {
      }
    } else if (node->symbol->non_terminal == BoolConstt) {
      if (TYPE_CHECKING == false) {
        resolve(node->head); // tRUE/fALSE
        insert_AST_head(node->list,
                        node->head->list->head); // insert tRUE/fALSE
      } else {
      }
    } else if (node->symbol->non_terminal == DeclareStmt) {
      if (TYPE_CHECKING == false) {
        AST_Node *DECLARE = create_AST_Node("DECLARE", NULL);
        insert_AST_tail(node->list, DECLARE);
        resolve(node->head->sibling);                   // IdList
        resolve(node->head->sibling->sibling->sibling); // DataType
        append_AST_lists_tail(node->list, node->head->sibling->list);
        append_AST_lists_tail(node->list,
                              node->head->sibling->sibling->sibling->list);
        // Add to symbol table
        Scope *scope = find_scope(
            GLOBAL_SCOPE, node->head->token.line); // line no of 'dECLARE'
        SYMBOL_TABLE_ELEMENT **table = scope->table;
        if (node->head->sibling->sibling->sibling->head->sibling ==
            NULL) { // Not Array
          terminals type =
              node->head->sibling->sibling->sibling->head->token.name;
          AST_Node *ID = node->head->sibling->list->head;
          while (ID != NULL) {
            // TODO: FIX Offset
            SYMBOL_TABLE_ELEMENT *el = create_symbol_table_element(
                ID->token.id, false, type, 0, 0, CURR_OFFSET, ID->token.line);
            ID = ID->next;
            if (type == iNTEGER) {
              CURR_OFFSET += 4;
            } else if (type == rEAL) {
              CURR_OFFSET += 8;
            } else if (type == bOOLEAN) {
              CURR_OFFSET += 2;
            }
            el->next_offset = CURR_OFFSET;
            insert_symbol_table(el, scope->table);
          }
        } else { // Is an Array
          TreeNode *range_array =
              node->head->sibling->sibling->sibling->head->sibling->sibling;
          terminals type =
              node->head->sibling->sibling->sibling->tail->head->token.name;
          int start, end;
          int nUM_or_iD = 1;
          // Start Index_arr
          if (range_array->head->head->sibling ==
              NULL) { // Index_arr => New_index
            if (range_array->head->head->head->token.name == nUM) {
              start = range_array->head->head->head->token.num;
            } else { // iD type
              nUM_or_iD = 0;
            }
            // else
            // { // iD type
            // }
          } else { // Index_arr => Sign New_index
            if (range_array->head->head->head->token.name == pLUS) {
              if (range_array->head->head->sibling->head->token.name == nUM) {
                start = range_array->head->head->sibling->head->token.num;
              } else { // iD type
                nUM_or_iD = 0;
              }
              // else
              // { // iD type
              // }
            } else { // mINUS
              if (range_array->head->head->sibling->head->token.name == nUM) {
                start = 0 - range_array->head->head->sibling->head->token.num;
              } else { // iD type
                nUM_or_iD = 0;
              }
            }
          }
          // End Index_arr
          if (range_array->head->sibling->sibling->head->sibling ==
              NULL) { // Index_arr => New_index
            if (range_array->head->sibling->sibling->head->head->token.name ==
                nUM) {
              end = range_array->head->sibling->sibling->head->head->token.num;
            } else { // iD type
              nUM_or_iD = 0;
            }
            // else
            // { // iD type
            // }
          } else { // Index_arr => Sign New_index
            if (range_array->head->sibling->sibling->head->head->token.name ==
                pLUS) {
              if (range_array->head->sibling->sibling->head->sibling->head
                      ->token.name == nUM) {
                end = range_array->head->sibling->sibling->head->sibling->head
                          ->token.num;
              } else { // iD type
                nUM_or_iD = 0;
              }
              // else
              // { // iD type
              // }
            } else { // mINUS
              if (range_array->head->sibling->sibling->head->sibling->head
                      ->token.name == nUM) {
                end = 0 - range_array->head->sibling->sibling->head->sibling
                              ->head->token.num;
              } else { // iD type
                nUM_or_iD = 0;
              }
            }
          }
          AST_Node *ID = node->head->sibling->list->head;
          while (ID != NULL) {
            // TODO: FIX Offset
            SYMBOL_TABLE_ELEMENT *el =
                create_symbol_table_element(ID->token.id, true, type, start,
                                            end, CURR_OFFSET, ID->token.line);
            ID = ID->next;
            if (nUM_or_iD) {
              if (type == iNTEGER) {
                CURR_OFFSET += 4 * (end - start + 1);
              } else if (type == rEAL) {
                CURR_OFFSET += 8 * (end - start + 1);
              } else if (type == bOOLEAN) {
                CURR_OFFSET += 2 * (end - start + 1);
              }
            }
            el->next_offset = CURR_OFFSET;
            insert_symbol_table(el, scope->table);
          }
        }
        // printf("\n::::::: :::::\n");
        // print_symbol_table(scope->table);
      } else {
      }
    } else if (node->symbol->non_terminal == IdList) {
      if (TYPE_CHECKING == false) {
        resolve(node->head); // iD
        resolve(node->tail); // N3
        append_AST_lists_tail(node->list, node->head->list);
        append_AST_lists_head(node->list, node->tail->list);
      } else {
      }
    } else if (node->symbol->non_terminal == N3) {
      if (TYPE_CHECKING == false) {
        if (node->head->sibling == NULL) {
        } else {
          resolve(node->head->sibling); // iD
          resolve(node->tail);          // N3
          append_AST_lists_tail(node->list, node->head->sibling->list);
          append_AST_lists_tail(node->list, node->tail->list);
        }
      } else {
      }
    }
    // else if( node->symbol->non_terminal == DataType){
    //     if(node->head->sibling==NULL){
    //         resolve(node->head);
    //         insert_AST_tail(node->list,node->head->list->head);
    //     }
    //     else {
    //         AST_Node* ARRAY = create_AST_Node("ARRAY",NULL);
    //         insert_AST_tail(node->list, ARRAY);
    //         resolve(node->head->sibling->sibling);
    //         resolve(node->tail);
    //         append_AST_lists_tail(node->list,
    //         node->head->sibling->sibling->list);
    //     }
    // }
    else if (node->symbol->non_terminal == IterativeStmt) {
      if (TYPE_CHECKING == false) {
        if (node->head->symbol->terminal == fOR) {
          AST_Node *FORLOOP = create_AST_Node("FORLOOP", NULL);
          AST_Node *STATEMENTS = create_AST_Node("STATEMENTS", NULL);
          AST_Node *STATEMENTS_END = create_AST_Node("STATEMENTS_END", NULL);
          insert_AST_tail(node->list, FORLOOP);
          resolve(node->head->sibling->sibling); // iD
          resolve(
              node->head->sibling->sibling->sibling->sibling); // Range_for_loop
          resolve(node->head->sibling->sibling->sibling->sibling->sibling
                      ->sibling->sibling); // Statements
          append_AST_lists_tail(node->list, node->head->sibling->sibling->list);
          append_AST_lists_tail(
              node->list, node->head->sibling->sibling->sibling->sibling->list);
          insert_AST_tail(node->list, STATEMENTS);
          append_AST_lists_tail(node->list,
                                node->head->sibling->sibling->sibling->sibling
                                    ->sibling->sibling->sibling->list);
          insert_AST_tail(node->list, STATEMENTS_END);
        } else {
          AST_Node *WHILELOOP = create_AST_Node("WHILELOOP", NULL);
          AST_Node *STATEMENTS = create_AST_Node("STATEMENTS", NULL);
          AST_Node *STATEMENTS_END = create_AST_Node("STATEMENTS_END", NULL);
          insert_AST_tail(node->list, WHILELOOP);
          resolve(node->head->sibling->sibling); // ArithmeticOrBooleanExpr
          resolve(node->head->sibling->sibling->sibling->sibling
                      ->sibling); // Statements
          append_AST_lists_tail(node->list, node->head->sibling->sibling->list);
          insert_AST_tail(node->list, STATEMENTS);
          append_AST_lists_tail(
              node->list,
              node->head->sibling->sibling->sibling->sibling->sibling->list);
          insert_AST_tail(node->list, STATEMENTS_END);
        }
      } else {
        if (node->head->symbol->terminal == fOR) {
          resolve(node->head->sibling->sibling->sibling->sibling->sibling
                      ->sibling->sibling); // Statements
        } else {
          resolve(node->head->sibling->sibling); // ArithmeticOrBooleanExpr
          resolve(node->head->sibling->sibling->sibling->sibling
                      ->sibling); // Statements
        }
      }
    } else if (node->symbol->non_terminal == Range_for_loop) {
      if (TYPE_CHECKING == false) {
        resolve(node->head); // Index_for_loop
        resolve(node->tail); // Index_for_loop
        append_AST_lists_tail(node->list, node->head->list);
        append_AST_lists_tail(node->list, node->tail->list);
      } else {
      }
    } else if (node->symbol->non_terminal == Index_for_loop) {
      if (TYPE_CHECKING == false) {
        AST_Node *INDEX_FOR_LOOP = create_AST_Node("INDEX_FOR_LOOP", NULL);

        insert_AST_tail(node->list, INDEX_FOR_LOOP);
        resolve(node->head); // Sign_for_loop
        resolve(node->tail); // New_index_for_loop

        append_AST_lists_tail(node->list, node->head->list);
        append_AST_lists_tail(node->list, node->tail->list);
      } else {
      }
    } else if (node->symbol->non_terminal == Sign_for_loop) {
      if (TYPE_CHECKING == false) {
        if (node->head == NULL) {
        } else {
          resolve(node->head); // plus/minus
          insert_AST_tail(node->list, node->head->list->head);
        }
      } else {
      }
    } else if (node->symbol->non_terminal == New_index_for_loop) {
      if (TYPE_CHECKING == false) {
        resolve(node->head); // num
        insert_AST_tail(node->list, node->head->list->head);
      } else {
      }
    } else if (node->symbol->non_terminal == SimpleStmt) {
      if (TYPE_CHECKING == false) {
        resolve(node->head); // AssignStmt/ModuleReuseStmt
        append_AST_lists_tail(node->list, node->head->list);
      } else {
        resolve(node->head); // AssignStmt/ModuleReuseStmt
      }
    } else if (node->symbol->non_terminal == AssignmentStmt) {
      if (TYPE_CHECKING == false) {
        AST_Node *ASSIGNSTMT = create_AST_Node("ASSIGNSTMT", NULL);
        AST_Node *ASSIGNSTMT_END = create_AST_Node("ASSIGNSTMT_END", NULL);
        insert_AST_tail(node->list, ASSIGNSTMT);
        resolve(node->head); // id
        resolve(node->tail); // WhichStmt
        insert_AST_tail(node->list, node->head->list->head);
        append_AST_lists_tail(node->list, node->tail->list);
        insert_AST_tail(node->list, ASSIGNSTMT_END);
      } else {
        resolve(node->head); // iD
        resolve(node->tail); // WhichStmt
        SYMBOL_TABLE_ELEMENT *type1 = node->head->node_type;
        SYMBOL_TABLE_ELEMENT *type2 = node->tail->node_type;
        // printf("%d\n\n",node->head->node_type->type);
        // printf("%d\n\n",node->tail->node_type->type);
        /* printf("%d\n\n",node->head->token.line); */

        if ((type1->type == bOOLEAN) &&
            ((type2->type == bOOLEAN) || (type2->type == fALSE) ||
             (type1->type == tRUE))) {
          node->node_type = type1;
        } else if ((type1->type == iNTEGER) &&
                   ((type2->type == iNTEGER) || (type2->type == nUM))) {
          node->node_type = type1;
        } else if ((type1->type == rEAL) &&
                   ((type2->type == iNTEGER) || (type2->type == nUM) ||
                    (type2->type == rEAL) || (type2->type == rNUM))) {
          node->node_type = type1;
        } else {
          printf("Type check error!!!!!!!!!!!!!!------>1\n");
        }
      }
    } else if (node->symbol->non_terminal == WhichStmt) {
      if (TYPE_CHECKING == false) {
        resolve(node->head); // LvalueID/LvalueARR
        append_AST_lists_tail(node->list, node->head->list);
      } else {
        resolve(node->head); // LvalueID/LvalueARR
        // printf("%d\n\n",node->head->node_type->type);
        node->node_type = node->head->node_type;
      }
    } else if (node->symbol->non_terminal == LvalueIDStmt) {
      if (TYPE_CHECKING == false) {
        AST_Node *LVALUEID = create_AST_Node("LVALUEID", NULL);
        insert_AST_tail(node->list, LVALUEID);
        resolve(node->head->sibling); // Expression
        append_AST_lists_tail(node->list, node->head->sibling->list);
      } else {
        resolve(node->head->sibling); // Expression
        // printf("%d\n\n",node->head->sibling->node_type->type);
        node->node_type = node->head->sibling->node_type;
      }
    } else if (node->symbol->non_terminal == Expression) {
      if (TYPE_CHECKING == false) {
        resolve(node->head); // ArithmeticOrBool/U
        append_AST_lists_tail(node->list, node->head->list);
      } else {
        // printf("\nPRINTING EXPRESSION TYPE: type U %d\n",
        // node->head->symbol->non_terminal == U);
        resolve(node->head); // ArithmeticOrBool/U
        // printf("%d\n\n",node->head->node_type->type);
        print_astnodes(node);
        node->node_type = node->head->node_type;
        // printf("\n EXp PR done\n");
        // print_symbol_table_element(node->node_type);
      }
    } else if (node->symbol->non_terminal == ArithmeticOrBooleanExpr) {
      if (TYPE_CHECKING == false) {
        AST_Node *ARITHORBOOLEXP = create_AST_Node("ARITHORBOOLEXP", NULL);
        AST_Node *ARITHORBOOLEXP_END =
            create_AST_Node("ARITHORBOOLEXP_END", NULL);

        insert_AST_tail(node->list, ARITHORBOOLEXP);
        resolve(node->head); // AnyTerm
        resolve(node->tail); // N7
        AST_Node *LOGIC;
        if (node->tail->head->sibling == NULL) {
        } else {
          if (node->tail->head->head->symbol->terminal == aND) {
            LOGIC = create_AST_Node("AND", NULL);
          } else {
            LOGIC = create_AST_Node("OR", NULL);
          }
          insert_AST_tail(node->list, LOGIC);
        }
        append_AST_lists_tail(node->list, node->head->list);
        append_AST_lists_tail(node->list, node->tail->list);
        insert_AST_tail(node->list, ARITHORBOOLEXP_END);
      } else {
        /* printf("\n INSIDE AR OR BOOL EXP\n"); */
        resolve(node->head); // AnyTerm
        /* printf("\n BETWEEN AR OR BOOL EXP\n"); */
        resolve(node->tail); // N7
        SYMBOL_TABLE_ELEMENT *type1 = node->head->node_type;
        SYMBOL_TABLE_ELEMENT *type2;
        // printf("%d\n\n",node->head->node_type==NULL);
        if (node->tail->head->sibling == NULL) {
          node->node_type = type1;
          // printf("heeerrrrrrrrrr\n");
        } else {
          // printf("heeerrrrrrrrrr11111111111111\n");

          type2 = node->tail->node_type;
          if (((type1->type == bOOLEAN) || (type1->type == fALSE) ||
               (type1->type == tRUE)) &&
              ((type2->type == bOOLEAN) || (type2->type == fALSE) ||
               (type2->type == tRUE))) {
            node->node_type = type1;
          } else if (((type1->type == iNTEGER) || (type1->type == nUM)) &&
                     ((type2->type == iNTEGER) || (type2->type == nUM))) {
            node->node_type = type1;
          } else if (((type1->type == rEAL) || (type1->type == rNUM)) &&
                     ((type2->type == rEAL) || (type2->type == rNUM))) {
            node->node_type = type1;
          } else if (((type1->type == rEAL) || (type1->type == rNUM)) &&
                     ((type2->type == iNTEGER) || (type2->type == nUM))) {
            node->node_type = type1;
          } else if (((type1->type == iNTEGER) || (type1->type == nUM)) &&
                     ((type2->type == rEAL) || (type2->type == rNUM))) {
            node->node_type = type2;
          } else {
            printf("Type check error!!!!!!!!!!!!!!------>2\n");
          }
        }
        /* printf("\n OUTSIDE AR OR BOOL EXP\n"); */
        /* print_symbol_table_element(node->node_type); */
      }
    } else if (node->symbol->non_terminal == AnyTerm) {
      if (TYPE_CHECKING == false) {
        resolve(node->head); // ArithmeticExpr
        resolve(node->tail); // N8
        AST_Node *REL;
        if (node->tail->head->sibling == NULL) {
        } else {
          if (node->tail->head->head->symbol->terminal == lT) {
            REL = create_AST_Node("LT", NULL);
          } else if (node->tail->head->head->symbol->terminal == lE) {
            REL = create_AST_Node("LE", NULL);
          } else if (node->tail->head->head->symbol->terminal == gT) {
            REL = create_AST_Node("GT", NULL);
          } else if (node->tail->head->head->symbol->terminal == gE) {
            REL = create_AST_Node("GE", NULL);
          } else if (node->tail->head->head->symbol->terminal == eQ) {
            REL = create_AST_Node("EQ", NULL);
          } else if (node->tail->head->head->symbol->terminal == nE) {
            REL = create_AST_Node("NE", NULL);
          }
          insert_AST_tail(node->list, REL);
        }
        append_AST_lists_tail(node->list, node->head->list);
        append_AST_lists_tail(node->list, node->tail->list);
      } else {
        resolve(node->head); // ArithmeticExpr
        resolve(node->tail); // N8
        SYMBOL_TABLE_ELEMENT *type1 = node->head->node_type;
        SYMBOL_TABLE_ELEMENT *type2;
        // printf("ertyui%d\n\n",node->head->node_type==NULL);
        // printf("look here ------->\n");
        print_astnodes(node);
        // printf("look over-----------\n");
        if (node->tail->head->sibling == NULL) {
          // printf("heeerrrrrrrrrr\n");
          node->node_type = type1;
        } else {
          // printf("heeerrrrrrrrrr11111111111111\n");
          type2 = node->tail->node_type;
          if (((type1->type == iNTEGER) || (type1->type == nUM) ||
               (type1->type == rEAL) || (type1->type == rNUM)) &&
              ((type2->type == iNTEGER) || (type2->type == nUM) ||
               (type2->type == rNUM) || (type2->type == rEAL))) {
            SYMBOL_TABLE_ELEMENT *temp =
                create_symbol_table_element("", false, bOOLEAN, -1, -1, -1, -1);
            node->node_type = temp;
          } else {
            printf("Type check error!!!!!!!!!!!!!!------>3\n");
          }
        }
      }
    } else if (node->symbol->non_terminal == ArithmeticExpr) {
      if (TYPE_CHECKING == false) {
        resolve(node->head); // Term
        resolve(node->tail); // N4
        AST_Node *OP1;
        if (node->tail->head->sibling == NULL) {
        } else {
          if (node->tail->head->head->symbol->terminal == pLUS) {
            OP1 = create_AST_Node("ADD", NULL);
          } else {
            OP1 = create_AST_Node("SUBTRACT", NULL);
          }
          insert_AST_tail(node->list, OP1);
        }
        append_AST_lists_tail(node->list, node->head->list);
        append_AST_lists_tail(node->list, node->tail->list);
      } else {
        /* printf("\n\n ::::::::::::::::::::: ArithmeticExpr\n"); */
        resolve(node->head);                     // Term
        resolve(node->tail);                     // N4
        if (node->tail->head->sibling == NULL) { // N4 => #
          node->node_type = node->head->node_type;
        } else {
          node->node_type =
              create_symbol_table_element("", false, iNTEGER, -1, -1, -1, -1);
          if (node->head->node_type->type == bOOLEAN ||
              node->tail->node_type->type == bOOLEAN) {
            printf("\n,,,, THROWING ERROR ArithmeticExpr!\n");
            // throw Error
          } else {
            if (node->head->node_type->type == rEAL ||
                node->tail->node_type->type == rEAL) {
              node->node_type->type = rEAL;
            } else {
              node->node_type->type = iNTEGER;
            }
          }
        }
        /* printf("\n donedone\n"); */
      }
    } else if (node->symbol->non_terminal == Term) {
      if (TYPE_CHECKING == false) {
        resolve(node->head); // Factor
        resolve(node->tail); // N5
        AST_Node *OP2;
        if (node->tail->head->sibling == NULL) {
        } else {
          if (node->tail->head->head->symbol->terminal == mUL) {
            OP2 = create_AST_Node("MUL", NULL);
          } else {
            OP2 = create_AST_Node("DIV", NULL);
          }
          insert_AST_tail(node->list, OP2);
        }
        append_AST_lists_tail(node->list, node->head->list);
        append_AST_lists_tail(node->list, node->tail->list);
      } else {
        /* printf("\n\n ::::::::::::::::::::: Term if %d\n",
         * node->tail->head->sibling == NULL); */
        resolve(node->head);                     // Factor
        resolve(node->tail);                     // N5
        if (node->tail->head->sibling == NULL) { // N5 => #
          node->node_type = node->head->node_type;
        } else {
          node->node_type =
              create_symbol_table_element("", false, iNTEGER, -1, -1, -1, -1);
          if (node->head->node_type->type == bOOLEAN ||
              node->tail->node_type->type == bOOLEAN) {
            printf("\n,,,, THROWING ERROR term!\n");
            // throw Error
          } else {
            if (node->head->node_type->type == rEAL ||
                node->tail->node_type->type == rEAL) {
              node->node_type->type = rEAL;
            } else {
              node->node_type->type = iNTEGER;
            }
          }
        }
        /* print_symbol_table_element(node->node_type); */
        /* printf("\n done\n"); */
      }
    } else if (node->symbol->non_terminal == Factor) {
      if (TYPE_CHECKING == false) {
        if (node->head->sibling == NULL) {
          resolve(node->head); // num/rnum/boolconst
          insert_AST_tail(node->list, node->head->list->head);
        } else if (node->head->sibling->sibling == NULL) {
          resolve(node->head); // iD
          resolve(node->tail); // N11
          append_AST_lists_tail(node->list, node->head->list);
          append_AST_lists_tail(node->list, node->tail->list);
        } else {
          resolve(node->head->sibling); // ArithmeticOrBool
          append_AST_lists_tail(node->list, node->head->sibling->list);
        }
      } else {
        /* printf("\n\n ::::::::::::::::::::: Factor\n"); */
        node->node_type =
            create_symbol_table_element("", false, iNTEGER, -1, -1, -1, -1);
        if (node->head->sibling == NULL) {
          /* printf("\n easey \n"); */
          /* resolve(node->head); // num/rnum/boolconst */
          node->node_type->type = node->head->token.name;
        } else if (node->head->sibling->sibling == NULL) {
          /* printf("\n here??\n"); */
          /* print_token_details(node->head->token, stdout); */
          Scope *scope = find_scope(GLOBAL_SCOPE, node->head->token.line);
          /* print_scope(scope); */
          node->node_type = find_symtable_el_by_id(scope, node->head->token.id);
          // TODO: CHECK N11 range
          /* resolve(node->head); // iD */
          /* resolve(node->tail); // N11 */
        } else {
          /* printf("\n here!\n"); */
          resolve(node->head->sibling); // ArithmeticOrBool
          node->node_type = node->head->sibling->node_type;
        }
        /* print_symbol_table_element(node->node_type); */
        /* printf("\n factor done\n"); */
      }
    } else if (node->symbol->non_terminal == N11) {
      if (TYPE_CHECKING == false) {
        if (node->head->sibling == NULL) {
        } else {
          resolve(node->head->sibling); // Element_index_with_expression
          append_AST_lists_tail(node->list, node->head->sibling->list);
        }
      } else {
      }
    } else if (node->symbol->non_terminal == Element_index_with_expressions) {
      if (TYPE_CHECKING == false) {
        if (node->head->sibling == NULL) {
          // AST_Node* ARR_EXP = create_AST_Node("ARR_EXP",NULL);
          resolve(node->head); // ArrExpr
          // insert_AST_tail(node->list,ARR_EXP);
          append_AST_lists_tail(node->list, node->head->list);
        } else {
          AST_Node *ARR_INDEX = create_AST_Node("ARR_INDEX", NULL);
          AST_Node *ARR_INDEX_END = create_AST_Node("ARR_INDEX_END", NULL);

          resolve(node->head); // Sign
          resolve(node->tail); // N10
          insert_AST_tail(node->list, ARR_INDEX);
          append_AST_lists_tail(node->list, node->head->list);
          append_AST_lists_tail(node->list, node->tail->list);
          insert_AST_tail(node->list, ARR_INDEX_END);
        }
      } else {
        AST_Node *temp = node->list->head;
        while (temp != NULL) {
          switch (temp->token.name) {
          case lE:
          case lT:
          case gE:
          case gT:
          case oR:
          case aND:
          case bOOLEAN:
          case eQ:
          case nE:
            printf("Type check error ------------------->4\n");
            break;
          default:
            break;
          }
          temp = temp->next;
        }
      }
    } else if (node->symbol->non_terminal == Sign) {
      if (TYPE_CHECKING == false) {
        resolve(node->head); // plus/minus
        insert_AST_tail(node->list, node->head->list->head);
      } else {
      }
    } else if (node->symbol->non_terminal == N10) {
      if (TYPE_CHECKING == false) {
        if (node->head->sibling == NULL) {
          resolve(node->head); // New_index
          insert_AST_tail(node->list, node->head->list->head);
        } else {
          resolve(node->head->sibling); // ArrExpr
          // resolve(node->tail); // New_index
          append_AST_lists_tail(node->list, node->head->sibling->list);
          // insert_AST_tail(node->list, node->tail->list->head);
        }
      } else {
      }
    } else if (node->symbol->non_terminal == New_index) {
      if (TYPE_CHECKING == false) {
        resolve(node->head); // num/ind
        insert_AST_tail(node->list, node->head->list->head);
      } else {
      }
    } else if (node->symbol->non_terminal == ArrExpr) {
      if (TYPE_CHECKING == false) {
        AST_Node *ARREXPR = create_AST_Node("ARREXPR", NULL);
        AST_Node *ARREXPR_END = create_AST_Node("ARREXPR_END", NULL);
        insert_AST_tail(node->list, ARREXPR);
        resolve(node->head); // ArrTerm
        resolve(node->tail); // Arr_N4
        AST_Node *OP1;
        if (node->tail->head->sibling == NULL) {
        } else {
          if (node->tail->head->head->symbol->terminal == pLUS) {
            OP1 = create_AST_Node("ADD", NULL);
          } else {
            OP1 = create_AST_Node("SUBTRACT", NULL);
          }
          insert_AST_tail(node->list, OP1);
        }
        append_AST_lists_tail(node->list, node->head->list);
        append_AST_lists_tail(node->list, node->tail->list);
        insert_AST_tail(node->list, ARREXPR_END);
      } else {
      }
    } else if (node->symbol->non_terminal == ArrTerm) {
      if (TYPE_CHECKING == false) {
        resolve(node->head); // ArrFactor
        resolve(node->tail); // Arr_N5
        AST_Node *OP2;
        if (node->tail->head->sibling == NULL) {
        } else {
          if (node->tail->head->head->symbol->terminal == mUL) {
            OP2 = create_AST_Node("MUL", NULL);
          } else {
            OP2 = create_AST_Node("DIV", NULL);
          }
          insert_AST_tail(node->list, OP2);
        }
        append_AST_lists_tail(node->list, node->head->list);
        append_AST_lists_tail(node->list, node->tail->list);
      } else {
      }
    } else if (node->symbol->non_terminal == ArrFactor) {
      if (TYPE_CHECKING == false) {
        if (node->head->sibling == NULL) {
          resolve(node->head); // id/num/boolconst
          insert_AST_tail(node->list, node->head->list->head);
        } else {
          resolve(node->head->sibling); // ArrExpr
          insert_AST_tail(node->list, node->head->sibling->list->head);
        }
      } else {
      }
    } else if (node->symbol->non_terminal == Arr_N4) {
      if (TYPE_CHECKING == false) {
        if (node->head->sibling == NULL) {
        } else {
          resolve(node->head);          // Op1
          resolve(node->head->sibling); // ArrTerm
          resolve(node->tail);          // Arr_N4

          append_AST_lists_tail(node->list, node->head->list);
          AST_Node *OP1;
          if (node->tail->head->sibling == NULL) {
          } else {
            if (node->tail->head->head->symbol->terminal == pLUS) {
              OP1 = create_AST_Node("ADD", NULL);
            } else {
              OP1 = create_AST_Node("SUBTRACT", NULL);
            }
            insert_AST_tail(node->list, OP1);
          }
          append_AST_lists_tail(node->list, node->head->sibling->list);
          append_AST_lists_tail(node->list, node->tail->list);
        }
      } else {
      }
    } else if (node->symbol->non_terminal == Arr_N5) {
      if (TYPE_CHECKING == false) {
        if (node->head->sibling == NULL) {
        } else {
          resolve(node->head);          // Op2
          resolve(node->head->sibling); // ArrFactor
          resolve(node->tail);          // Arr_N5
          append_AST_lists_tail(node->list, node->head->list);
          AST_Node *OP2;
          if (node->tail->head->sibling == NULL) {
          } else {
            if (node->tail->head->head->symbol->terminal == mUL) {
              OP2 = create_AST_Node("MUL", NULL);
            } else {
              OP2 = create_AST_Node("DIV", NULL);
            }
            insert_AST_tail(node->list, OP2);
          }
          append_AST_lists_tail(node->list, node->head->sibling->list);
          append_AST_lists_tail(node->list, node->tail->list);
        }
      } else {
      }
    } else if (node->symbol->non_terminal == Op1) {
      if (TYPE_CHECKING == false) {
        resolve(node->head);
        // insert_AST_tail(node->list, node->head->list->head);
      } else {
      }
    } else if (node->symbol->non_terminal == Op2) {
      if (TYPE_CHECKING == false) {
        resolve(node->head);
        insert_AST_tail(node->list, node->head->list->head);
      } else {
      }
    } else if (node->symbol->non_terminal == N5) {
      if (TYPE_CHECKING == false) {
        if (node->head->sibling == NULL) {
        } else {
          resolve(node->head);          // Op2
          resolve(node->head->sibling); // Factor
          resolve(node->tail);          // N5
          insert_AST_tail(node->list, node->head->list->head);
          AST_Node *OP2;
          if (node->tail->head->sibling == NULL) {
          } else {
            if (node->tail->head->head->symbol->terminal == mUL) {
              OP2 = create_AST_Node("MUL", NULL);
            } else {
              OP2 = create_AST_Node("DIV", NULL);
            }
            insert_AST_tail(node->list, OP2);
          }
          append_AST_lists_tail(node->list, node->head->sibling->list);
          append_AST_lists_tail(node->list, node->tail->list);
        }
      } else {
        /* printf("\n\n ::::::::::::::::::::: N5\n"); */
        if (node->head->sibling != NULL) {
          resolve(node->head->sibling);            // Factor
          resolve(node->tail);                     // N5
          if (node->tail->head->sibling == NULL) { // N5 => #
            node->node_type = node->head->sibling->node_type;
          } else {
            node->node_type =
                create_symbol_table_element("", false, iNTEGER, -1, -1, -1, -1);
            if (node->head->sibling->node_type->type == bOOLEAN ||
                node->tail->node_type->type == bOOLEAN) {
              printf("\n,,,, THROWING ERROR n5!\n");
              // throw Error
            } else {
              if (node->head->sibling->node_type->type == rEAL ||
                  node->tail->node_type->type == rEAL) {
                node->node_type->type = rEAL;
              } else {
                node->node_type->type = iNTEGER;
              }
            }
          }
        }
      }
    } else if (node->symbol->non_terminal == N4) {
      if (TYPE_CHECKING == false) {
        if (node->head->sibling == NULL) {
        } else {
          resolve(node->head);          // Op1
          resolve(node->head->sibling); // Term
          resolve(node->tail);          // N4
          insert_AST_tail(node->list, node->head->list->head);
          AST_Node *OP1;
          if (node->tail->head->sibling == NULL) {
          } else {
            if (node->tail->head->head->symbol->terminal == pLUS) {
              OP1 = create_AST_Node("ADD", NULL);
            } else {
              OP1 = create_AST_Node("SUBTRACT", NULL);
            }
            insert_AST_tail(node->list, OP1);
          }
          append_AST_lists_tail(node->list, node->head->sibling->list);
          append_AST_lists_tail(node->list, node->tail->list);
        }
      } else {
        /* printf("\n ::::::: N4\n"); */
        if (node->head->sibling != NULL) {
          /* printf("\n : : : from n4 %d\n", node->tail->head->sibling == NULL);
           */
          resolve(node->head->sibling);            // Term
          resolve(node->tail);                     // N4
          if (node->tail->head->sibling == NULL) { // N4 => #
            node->node_type = node->head->sibling->node_type;
          } else {
            node->node_type =
                create_symbol_table_element("", false, iNTEGER, -1, -1, -1, -1);
            /* printf("\ncheck %d\n", node->head->sibling->node_type == NULL);
             */
            if (node->head->sibling->node_type->type == bOOLEAN ||
                node->tail->node_type->type == bOOLEAN) {
              printf("\n,,,, THROWING ERROR n4!\n");
              // throw Error
            } else {
              if (node->head->sibling->node_type->type == rEAL ||
                  node->tail->node_type->type == rEAL) {
                node->node_type->type = rEAL;
              } else {
                node->node_type->type = iNTEGER;
              }
            }
          }
        }
        /* printf("\n dno\n"); */
      }
    } else if (node->symbol->non_terminal == N8) {
      if (TYPE_CHECKING == false) {
        if (node->head->sibling == NULL) {
        } else {
          resolve(node->head);          // RelationalOp
          resolve(node->head->sibling); // ArithmeticExpr
          resolve(node->tail);          // N8
          append_AST_lists_tail(node->list, node->head->list);
          AST_Node *REL;
          if (node->tail->head->sibling == NULL) {
          } else {
            if (node->tail->head->head->symbol->terminal == lT) {
              REL = create_AST_Node("LT", NULL);
            } else if (node->tail->head->head->symbol->terminal == lE) {
              REL = create_AST_Node("LE", NULL);
            } else if (node->tail->head->head->symbol->terminal == gT) {
              REL = create_AST_Node("GT", NULL);
            } else if (node->tail->head->head->symbol->terminal == gE) {
              REL = create_AST_Node("GE", NULL);
            } else if (node->tail->head->head->symbol->terminal == eQ) {
              REL = create_AST_Node("EQ", NULL);
            } else if (node->tail->head->head->symbol->terminal == nE) {
              REL = create_AST_Node("NE", NULL);
            }
            insert_AST_tail(node->list, REL);
          }
          append_AST_lists_tail(node->list, node->head->sibling->list);
          append_AST_lists_tail(node->list, node->tail->list);
        }
      } else {
        /* printf("\n ENETERED N8 \n"); */
        if (node->head->sibling == NULL) {

        } else {
          resolve(node->tail);          // N7
          resolve(node->head->sibling); // AnyTerm
          SYMBOL_TABLE_ELEMENT *type1 = node->head->sibling->node_type;
          /* SYMBOL_TABLE_ELEMENT* type2 = node->tail->node_type; */
          SYMBOL_TABLE_ELEMENT *type2;
          if (node->tail->head->sibling == NULL) {
            node->node_type = type1;
          } else {
            type2 = node->tail->node_type;
            if (((type1->type == nUM) || (type1->type == rNUM) ||
                 (type1->type == iNTEGER) || (type1->type == rEAL)) &&
                ((type2->type == nUM) || (type2->type == rNUM) ||
                 (type2->type == iNTEGER) || (type2->type == rEAL))) {
              SYMBOL_TABLE_ELEMENT *temp = create_symbol_table_element(
                  "", false, bOOLEAN, -1, -1, -1, -1);
              node->node_type = temp;
            } else {
              printf("Type check error!!!!!!!!!!!!!!------>5\n");
            }
          }
        }
        /* printf("\n EXITING N8\n"); */
      }
    } else if (node->symbol->non_terminal == RelationalOp) {
      if (TYPE_CHECKING == false) {
        resolve(node->head); // lt/le/gt.....
        insert_AST_tail(node->list, node->head->list->head);
      } else {
      }
    } else if (node->symbol->non_terminal == N7) {
      if (TYPE_CHECKING == false) {
        if (node->head->sibling == NULL) {
        } else {
          resolve(node->head);          // LogicalalOp
          resolve(node->tail);          // N7
          resolve(node->head->sibling); // AnyTerm
          append_AST_lists_tail(node->list, node->head->list);
          AST_Node *LOGIC;
          if (node->tail->head->sibling == NULL) {
          } else {
            if (node->tail->head->head->symbol->terminal == aND) {
              LOGIC = create_AST_Node("AND", NULL);
            } else {
              LOGIC = create_AST_Node("OR", NULL);
            }
            insert_AST_tail(node->list, LOGIC);
          }
          append_AST_lists_tail(node->list, node->head->sibling->list);
          append_AST_lists_tail(node->list, node->tail->list);
        }
      } else {
        if (node->head->sibling == NULL) {

        } else {
          resolve(node->tail);          // N7
          resolve(node->head->sibling); // AnyTerm
          SYMBOL_TABLE_ELEMENT *type1 = node->head->sibling->node_type;
          SYMBOL_TABLE_ELEMENT *type2 = node->tail->node_type;
          if (((type1->type == bOOLEAN) || (type1->type == fALSE) ||
               (type1->type == tRUE)) &&
              ((type2->type == bOOLEAN) || (type2->type == fALSE) ||
               (type2->type == tRUE))) {
            SYMBOL_TABLE_ELEMENT *temp =
                create_symbol_table_element("", false, bOOLEAN, -1, -1, -1, -1);
            node->node_type = temp;
          } else {
            printf("Type check error!!!!!!!!!!!!!!------>6\n");
          }
        }
      }
    } else if (node->symbol->non_terminal == LogicalOp) {
      if (TYPE_CHECKING == false) {
        resolve(node->head); // and/or
        insert_AST_tail(node->list, node->head->list->head);
      } else {
      }
    } else if (node->symbol->non_terminal == U) {
      if (TYPE_CHECKING == false) {
        resolve(node->head); // Unary_op
        resolve(node->tail); // New_nt
        insert_AST_tail(node->list, node->head->list->head);
        append_AST_lists_tail(node->list, node->tail->list);
      } else {
        /* printf("\n\n ::::::::::::::::::::: U\n"); */
        resolve(node->tail); // New_nt
        node->node_type = node->tail->node_type;
        /* printf("\n done processing U\n"); */
        /* print_symbol_table_element(node->node_type); */
      }
    } else if (node->symbol->non_terminal == Unary_op) {
      if (TYPE_CHECKING == false) {
        resolve(node->head); // plus/minus
        AST_Node *UNARY_OP = create_AST_Node("UNARY_OP", NULL);
        insert_AST_tail(node->list, UNARY_OP);
        insert_AST_tail(node->list, node->head->list->head);
        /* AST_Node *unary_op; */
        /* if (node->head->list->head->token.name == pLUS) { */
        /*   unary_op = create_AST_Node("UNARY_PLUS", NULL); */
        /* } else { */
        /*   unary_op = create_AST_Node("UNARY_MINUS", NULL); */
        /* } */
        /* unary_op->token = node->head->list->head->token; */
        /* unary_op->token_set = 1; */
      } else {
      }
    } else if (node->symbol->non_terminal == New_NT) {
      if (TYPE_CHECKING == false) {
        if (node->head->sibling == NULL) {
          resolve(node->head); // var_id_num
          append_AST_lists_tail(node->list, node->head->list);
        } else {
          resolve(node->head->sibling); // ArithmeticExpr
          append_AST_lists_tail(node->list, node->head->sibling->list);
        }
      } else {
        if (node->head->sibling == NULL) {
          /* printf("\n:::::::::::::::::: Newnt varidnum\n"); */
          resolve(node->head); // var_id_num
          node->node_type = node->head->node_type;
        } else {
          /* printf("\n:::::::::::::::::: Newnt arth\n"); */
          resolve(node->head->sibling); // ArithmeticExpr
          node->node_type = node->head->sibling->node_type;
        }
      }
    } else if (node->symbol->non_terminal == Var_id_num) {
      if (TYPE_CHECKING == false) {
        resolve(node->head); // id/num/rnum
        append_AST_lists_tail(node->list, node->head->list);
      } else {
        SYMBOL_TABLE_ELEMENT *el = NULL;
        if (node->head->list->head->token.name == nUM) {
          el = create_symbol_table_element("", false, nUM, -1, -1, -1, -1);
        } else if (node->head->list->head->token.name == rNUM) {
          el = create_symbol_table_element("", false, rNUM, -1, -1, -1, -1);
        } else if (node->head->list->head->token.name == iD) {
          Scope *scope =
              find_scope(GLOBAL_SCOPE, node->head->list->head->token.line);
          el = find_symtable_el_by_id(scope, node->head->list->head->token.id);
        }
        node->node_type = el;
      }
    } else if (node->symbol->non_terminal == LvalueARRStmt) {
      if (TYPE_CHECKING == false) {
        // AST_Node *ASSIGN = create_AST_Node("ASSIGN", NULL);
        resolve(node->head->sibling); // Element_index_with_expr
        resolve(node->head->sibling->sibling->sibling->sibling); // Expression
        append_AST_lists_tail(node->list, node->head->sibling->list);
        // insert_AST_tail(node->list, ASSIGN);
        append_AST_lists_tail(
            node->list, node->head->sibling->sibling->sibling->sibling->list);
      } else {
        resolve(node->head->sibling); // Element_index_with_expr
        resolve(node->head->sibling->sibling->sibling->sibling); // Expression
        node->node_type =
            node->head->sibling->sibling->sibling->sibling->node_type;
      }
    } else if (node->symbol->non_terminal == ModuleReuseStmt) {
      if (TYPE_CHECKING == false) {
        AST_Node *OPTIONAL = create_AST_Node("FUNCTION_CALL", NULL);
        AST_Node *FUNCTION_CALL_END = create_AST_Node("FUNCTION_CALL_END", NULL);
        resolve(node->head); // Optional
        AST_Node *MODULE = create_AST_Node("MODULE", NULL);
        AST_Node *PARAMETERS = create_AST_Node("PARAMETERS", NULL);
        resolve(node->head->sibling->sibling->sibling); // id
        resolve(node->head->sibling->sibling->sibling->sibling->sibling
                    ->sibling); // Actual_para_list

        insert_AST_tail(node->list, OPTIONAL);
        append_AST_lists_tail(node->list, node->head->list); // optional
        insert_AST_tail(node->list, MODULE);
        insert_AST_tail(
            node->list,
            node->head->sibling->sibling->sibling->list->head); // id
        insert_AST_tail(node->list, PARAMETERS);                // parameters
        // append_AST_lists_tail(node->list,node->head->sibling->sibling->sibling->sibling->sibling->list);
        append_AST_lists_tail(node->list,
                              node->head->sibling->sibling->sibling->sibling
                                  ->sibling->sibling->list); // Actual_para_list
        insert_AST_tail(node->list, FUNCTION_CALL_END);
      } else {
        Scope *called_module_scope = find_module_scope(
            GLOBAL_SCOPE, node->head->sibling->sibling->sibling->list->head
                              ->token.id); // finding scope for called module
        AST_Node *actual_list_ast = node->head->sibling->sibling->sibling
                                        ->sibling->sibling->sibling->list->head;
        printf("\n\nCALLED MODULE SCOPE ------------------\n");
        print_scope(called_module_scope);
        int OFFSET = 0;
        while (actual_list_ast != NULL &&
               OFFSET != called_module_scope->iplist_offset) {
          SYMBOL_TABLE_ELEMENT *fp =
              search_element_by_offset(called_module_scope->table, OFFSET);
          OFFSET = fp->next_offset;
          SYMBOL_TABLE_ELEMENT *ap = find_symtable_el_by_id(
              find_scope(GLOBAL_SCOPE, actual_list_ast->token.line),
              actual_list_ast->token.id);
          actual_list_ast = actual_list_ast->next;
          printf("\nCHECKING TYPE EQUIVALENCE: %d\n", type_equal(fp, ap));
          print_symbol_table_element(fp);
          print_symbol_table_element(ap);
        }
        if (actual_list_ast != NULL) {
          printf("\nERROR: EXTRA ACTUAL PARAMETERS!\n");
        } else if (OFFSET != called_module_scope->iplist_offset) {
          printf("\nERROR: MISSING ACTUAL PARAMETERS!\n");
        }
        // checking return parameters
        AST_Node *return_list_ast = node->head->list->head;
        return_list_ast = return_list_ast->next; // skipping label
        while (return_list_ast != NULL &&
               OFFSET != called_module_scope->oplist_offset) {
          SYMBOL_TABLE_ELEMENT *fp =
              search_element_by_offset(called_module_scope->table, OFFSET);
          OFFSET = fp->next_offset;
          SYMBOL_TABLE_ELEMENT *ap = find_symtable_el_by_id(
              find_scope(GLOBAL_SCOPE, return_list_ast->token.line),
              return_list_ast->token.id);
          return_list_ast = return_list_ast->next;
          printf("\nCHECKING TYPE EQUIVALENCE: %d\n", type_equal(fp, ap));
          print_symbol_table_element(fp);
          print_symbol_table_element(ap);
        }
        if (return_list_ast != NULL) {
          printf("\nERROR: EXTRA RETURN PARAMETERS!\n");
        } else if (OFFSET != called_module_scope->oplist_offset) {
          printf("\nERROR: MISSING ACTUAL PARAMETERS!\n");
        }
      }
    } else if (node->symbol->non_terminal == Optional) {
      if (TYPE_CHECKING == false) {
        AST_Node *OPTIONAL_LIST = create_AST_Node("OPTIONAL_PARAMETERS", NULL);
        insert_AST_tail(node->list, OPTIONAL_LIST);
        if (node->head->sibling == NULL) {
        } else {
          resolve(node->head->sibling); // IDlist
          append_AST_lists_tail(node->list, node->head->sibling->list);
        }
      } else {
      }
    } else if (node->symbol->non_terminal == Actual_para_list) {
      if (TYPE_CHECKING == false) {
        resolve(node->head);          // Sign_for_loop
        resolve(node->head->sibling); // Actual_para_id
        resolve(node->tail);          // Actual_para_list1
        append_AST_lists_tail(node->list, node->head->list);
        append_AST_lists_tail(node->list, node->head->sibling->list);
        append_AST_lists_tail(node->list, node->tail->list);
      } else {
      }
    } else if (node->symbol->non_terminal == Actual_para_iD) {
      if (TYPE_CHECKING == false) {
        if (node->head->sibling == NULL) {
          resolve(node->head); // num/rnum/boolconst
          append_AST_lists_tail(node->list, node->head->list);
        } else {
          resolve(node->head); // id
          resolve(node->tail); // N11
          append_AST_lists_tail(node->list, node->head->list);
          append_AST_lists_tail(node->list, node->tail->list);
        }
      } else {
      }
    } else if (node->symbol->non_terminal == Actual_para_list1) {
      if (TYPE_CHECKING == false) {
        if (node->head->sibling == NULL) {
        } else {
          resolve(node->head->sibling);          // Sign_for_loop
          resolve(node->head->sibling->sibling); // Actual_para_id
          resolve(node->tail);                   // Actual_para_list1
          append_AST_lists_tail(node->list, node->head->sibling->list);
          append_AST_lists_tail(node->list, node->head->sibling->sibling->list);
          append_AST_lists_tail(node->list, node->tail->list);
        }
      } else {
      }
    }
  }
}

void run_ast(char *prog_file, char *output_file) {
  run_parser(prog_file, output_file);
  resolve(Parse_Tree_Root->head); // initial run
  TYPE_CHECKING = true;
  resolve(
      Parse_Tree_Root->head); // 2nd run for type checking of module reuse stmts
  // TODO: TYPE_CHECKING
  print_astnodes(Parse_Tree_Root->head);
  printf("\n\nPRINTING SCOPES:\n");
  char prefix[200] = "";
  print_scopes(GLOBAL_SCOPE, prefix);
  printf("\n\nFINDING MODULE SCOPE: DRIVER\n");
  print_scope(find_module_scope(GLOBAL_SCOPE, "DRIVER_MODULE"));
}
