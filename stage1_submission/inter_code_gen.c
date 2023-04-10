#include "inter_code_gen.h"
#include "ast.c"
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
  char *tempVar;
  AST_Node *ret;
} Res;

Quadruple *quadruple;
int genPref = 0;
int labelPref = 0;

Res *arith_or_bool_tac(AST_Node *ast_node);
Res *math_op_tac(AST_Node *ast_node);
Res *arr_tac(AST_Node *ast_node, char *resVar);
Res *condn_stmt_tac(AST_Node *ast_node);
Res *statements_tac(AST_Node *ast_node);
Res *unary_op_tac(AST_Node *ast_node);
Res *get_value_tac(AST_Node *ast_node);
Res *fun_call_tac(AST_Node *ast_node);
Res *print_func_tac(AST_Node *ast_node);

void print_quadnode(QuadNode *temp) {
  printf("OP: %s arg1: %s arg2: %s result: %s\n", LABEL_TO_STR[temp->op],
         temp->arg1, temp->arg2, temp->result);
}

bool compare(char *s1, char *s2) { return (strcmp(s1, s1) == 0); }

void print_quadlist(Quadruple *ll, FILE *debug_fp) {
  if (ll == NULL || ll->head == NULL) {
    fprintf(debug_fp, "List is empty\n");
    return;
  }
  QuadNode *temp = ll->head;

  while (temp != NULL) {
    print_quadnode(temp);
    temp = temp->next;
  }
}

QuadNode *create_new_quad_node() {
  QuadNode *temp = (QuadNode *)malloc(sizeof(QuadNode));
  temp->next = NULL;
  return temp;
}

Quadruple *create_quadlist() {
  Quadruple *ll = (Quadruple *)malloc(sizeof(Quadruple));
  ll->head = NULL;
  ll->tail = NULL;
  ll->size = 0;
  return ll;
}

void insert_quadnode_at_tail(QuadNode *temp, Quadruple *ll) {

  if (ll->head == NULL) {
    ll->head = temp;
    ll->tail = temp;
  } else {
    // insert the node at the beginning of the list.
    ll->tail->next = temp;
    ll->tail = temp;
  }

  ll->size++;
}
void insert_quadnode_at_head(QuadNode *temp, Quadruple *ll) {

  if (ll->head == NULL) {
    ll->head = temp;
    ll->tail = temp;
  } else {
    // insert the node at the beginning of the list.
    temp->next = ll->head;
    ll->head = temp;
  }

  ll->size++;
}

void merge_at_tail(Quadruple *l1, Quadruple *l2) {

  QuadNode *temp = l2->head;

  while (temp != NULL) {
    insert_quadnode_at_tail(temp, l1);
    temp = temp->next;
  }

  l1->size += l2->size;
}

int count_digits_in_int(int x) {
  int ans = 0;

  if (x == 0)
    return 1;

  while (x != 0) {
    x /= 10;
    ans++;
  }

  return ans;
}

bool is_label_empty(char *label) { return (strcmp(label, "") == 0); }

char *compilerGeneratedTemporary() {
  int digits = count_digits_in_int(genPref);
  char *num = (char *)malloc(digits * sizeof(char));
  sprintf(num, "%d", genPref);
  char *str = (char *)malloc((digits + 1) * sizeof(char));
  str[0] = 't';
  strncat(str, num, digits);
  genPref++;
  return str;
}

char *compilerGeneratedLabel() {
  int digits = count_digits_in_int(labelPref);
  char *num = (char *)malloc(digits * sizeof(char));
  sprintf(num, "%d", labelPref);
  char *str = (char *)malloc((digits + 1) * sizeof(char));
  str[0] = 'l';
  strncat(str, num, digits);
  labelPref++;
  return str;
}

char *get_token_value(TOKEN token) {
  if (token.name == nUM) {
    int digits = count_digits_in_int(token.num);
    char *num = (char *)malloc(digits * sizeof(char));
    sprintf(num, "%d", token.num);
    return num;
  } else if (token.name == rNUM) {
    char *num = (char *)malloc(32 * sizeof(char));
    sprintf(num, "%f", token.rnum);
    return num;
  } else {
    char *x = (char *)malloc(32 * sizeof(char));
    for (int i = 0; i < 20; i++)
      x[i] = token.id[i];
    return x;
  }
}

// it returns the compiler generated temporary variable of the last assigned
// value.

Res *make_res(char *result, AST_Node *ast_node) {
  Res *res = (Res *)malloc(sizeof(Res));
  res->tempVar = result;
  res->ret = ast_node;
  return res;
}

Res *arr_index_tac(AST_Node *ast_node, char *arr_name) {
  if (strcmp(ast_node->next->label, "ARR_INDEX") == 0) {
    ast_node = ast_node->next->next;

    bool negative = false;
    QuadNode *arr_index_sign = create_new_quad_node();

    // printf("before if :%s %s\n", ast_node->label,
    // get_token_value(ast_node->token));

    if (strcmp(get_token_value(ast_node->token), "-") == 0) {
      // printf("isnide if\n");

      arr_index_sign->op = SUB;
      arr_index_sign->arg1 = "0";
      arr_index_sign->arg2 = get_token_value(ast_node->next->token);
      arr_index_sign->result = compilerGeneratedTemporary();
      insert_quadnode_at_tail(arr_index_sign, quadruple);
      // - -> num -> arr_index_end -> next_label.
      ast_node = ast_node->next->next->next;
      negative = true;
    }

    QuadNode *arr_index = create_new_quad_node();
    arr_index->op = MUL;
    if (negative)
      arr_index->arg1 = arr_index_sign->result;
    else {
      arr_index->arg1 = get_token_value(ast_node->next->token);
      ast_node = ast_node->next->next->next;
    }
    arr_index->arg2 = "4-size";
    arr_index->result = compilerGeneratedTemporary();

    insert_quadnode_at_tail(arr_index, quadruple);

    QuadNode *arr_assign = create_new_quad_node();

    arr_assign->op = ASSIGN;

    char *name_array = (char *)malloc(64 * sizeof(char));

    strcat(name_array, arr_name);
    // printf("after strcat1\n");

    strcat(name_array, "[");
    // printf("after strcat2\n");

    strcat(name_array, arr_index->result);
    // printf("after strcat3\n");

    strcat(name_array, "]");

    // printf("after strcat4\n");

    arr_assign->arg1 = name_array;
    arr_assign->result = compilerGeneratedTemporary();

    insert_quadnode_at_tail(arr_assign, quadruple);

    // printf("fuck here\n");
    return make_res(name_array, ast_node);
  }

  return make_res("NO_MATCH", ast_node);
}

Res *math_op_tac(AST_Node *ast_node) {
  QuadNode *new = create_new_quad_node();

  if (strcmp(ast_node->label, "ADD") == 0) {
    new->op = PLUS;
  } else if (strcmp(ast_node->label, "SUBTRACT") == 0) {
    new->op = SUB;
  } else if (strcmp(ast_node->label, "MUL") == 0) {
    new->op = MUL;
  } else if (strcmp(ast_node->label, "DIV") == 0) {
    new->op = DIV;
  } else if (strcmp(ast_node->label, "LE") == 0) {
    new->op = LE;
  } else if (strcmp(ast_node->label, "AND") == 0) {
    new->op = AND;
  } else if (strcmp(ast_node->label, "OR") == 0) {
    new->op = OR;
  } else if (strcmp(ast_node->label, "LE") == 0) {
    new->op = LE;
  } else if (strcmp(ast_node->label, "LT") == 0) {
    new->op = LT;
  } else if (strcmp(ast_node->label, "GE") == 0) {
    new->op = GE;
  } else if (strcmp(ast_node->label, "GT") == 0) {
    new->op = GT;
  } else if (strcmp(ast_node->label, "EQ") == 0) {
    new->op = EQ;
  } else if (strcmp(ast_node->label, "NE") == 0) {
    new->op = NE;
  } else if (is_label_empty(ast_node->label)) {
    if (strcmp(ast_node->next->label, "ARREXPR") == 0) {
      return arr_tac(ast_node, NULL);
    } else if (strcmp(ast_node->next->label, "ARR_INDEX") == 0) {
      return arr_index_tac(ast_node, get_token_value(ast_node->token));
    } else {
      new->op = ASSIGN;
      new->arg1 = get_token_value(ast_node->token);
      new->arg2 = NULL;
      new->result = compilerGeneratedTemporary();
      insert_quadnode_at_tail(new, quadruple);
      return make_res(new->result, ast_node);
    }
  } else
    return make_res("NO_MATCH", ast_node);

  ast_node = ast_node->next;

  char *reuse = NULL;

  if (is_label_empty(ast_node->label)) {
    new->arg1 = get_token_value(ast_node->token);

    // need to check whether this variable is array instantiation or not.
    //
    if (strcmp(ast_node->next->label, "ARREXPR") == 0) {
      Res *res = arr_tac(ast_node, NULL);
      ast_node = res->ret;
      new->arg1 = res->tempVar;
    } else if (strcmp(ast_node->next->label, "ARR_INDEX") == 0) {
      Res *res = arr_index_tac(ast_node, new->arg1);
      ast_node = res->ret;
      new->arg1 = res->tempVar;
    }

    // printf("NEW ARG1 : %s\n", new->arg1);
  } else {
    Res *res1 = arith_or_bool_tac(ast_node);
    Res *res2 = math_op_tac(ast_node);

    if (strcmp(res1->tempVar, "NO_MATCH") == 0) {
      // printf("CHOSE ARITH OR BOOL EXP METHOD\n");
      new->arg1 = res2->tempVar;
      ast_node = res2->ret;
    } else {
      // printf("CHOSE MATH OP METHOD\n");
      new->arg1 = res1->tempVar;
      ast_node = res1->ret;
    }

    reuse = new->arg1;
  }

  ast_node = ast_node->next;

  if (is_label_empty(ast_node->label)) {
    new->arg2 = get_token_value(ast_node->token);

    if (strcmp(ast_node->next->label, "ARREXPR") == 0) {
      Res *res = arr_tac(ast_node, NULL);
      ast_node = res->ret;
      new->arg2 = res->tempVar;
    } else if (strcmp(ast_node->next->label, "ARR_INDEX") == 0) {
      Res *res = arr_index_tac(ast_node, new->arg1);
      ast_node = res->ret;
      new->arg2 = res->tempVar;
    }

  } else {
    Res *res1 = arith_or_bool_tac(ast_node);
    Res *res2 = math_op_tac(ast_node);

    if (strcmp(res1->tempVar, "NO_MATCH") == 0) {
      // printf("CHOSE ARITH OR BOOL EXP METHOD\n");
      new->arg2 = res2->tempVar;
      ast_node = res2->ret;
    } else {
      // printf("CHOSE MATH OP METHOD\n");
      new->arg2 = res1->tempVar;
      ast_node = res1->ret;
    }

    reuse = new->arg2;
  }

  new->result = (reuse == NULL) ? compilerGeneratedTemporary() : reuse;

  // print_quadnode(new);
  insert_quadnode_at_tail(new, quadruple);

  return make_res(new->result, ast_node);
}

Res *arith_or_bool_tac(AST_Node *ast_node) {
  // printf("here label: %s\n", ast_node->label);
  if (strcmp(ast_node->label, "ARITHORBOOLEXP") == 0) {
    ast_node = ast_node->next;
    Res *result = math_op_tac(ast_node);
    ast_node = result->ret;

    // int counter = 1;
    while (strcmp(ast_node->label, "ARITHORBOOLEXP_END") != 0) {
      // printf("label: %s -> ", ast_node->label);
      ast_node = ast_node->next;
      // counter++;
    }

    return make_res(result->tempVar, ast_node);
  }

  return make_res("NO_MATCH", ast_node);
}

Res *arr_tac(AST_Node *ast_node, char *resVar) {
  char *var_name = get_token_value(ast_node->token);

  ast_node = ast_node->next->next;

  Res *res = math_op_tac(ast_node);

  ast_node = res->ret;

  QuadNode *new = create_new_quad_node();

  new->op = MUL;
  new->arg1 = res->tempVar;
  new->arg2 = "4-size";
  new->result = res->tempVar;

  insert_quadnode_at_tail(new, quadruple);

  QuadNode *new2 = create_new_quad_node();

  new2->op = ASSIGN;

  char *name_array = (char *)malloc(64 * sizeof(char));

  strcat(name_array, var_name);
  strcat(name_array, "[");
  strcat(name_array, new->result);
  strcat(name_array, "]");

  new2->arg1 = resVar;
  new2->arg2 = NULL;
  new2->result = name_array;

  if (resVar == NULL) {
    new2->arg1 = name_array;
    new2->result = new->result;
  }

  insert_quadnode_at_tail(new2, quadruple);

  while (strcmp(ast_node->label, "ARREXPR_END") != 0)
    ast_node = ast_node->next;

  return make_res(new2->result, ast_node);
}

Res *assignment_tac(AST_Node *ast_node) {
  // printf("insidie assignment statement");
  // Quadruple *quad = create_quadlist();
  if (strcmp(ast_node->label, "ASSIGNSTMT") == 0) {
    int curr = genPref;

    AST_Node *copy_node = copy_AST_Node(ast_node);

    while (strcmp(copy_node->label, "ARITHORBOOLEXP") != 0 &&
           strcmp(copy_node->label, "UNARY_OP") != 0) {
      copy_node = copy_node->next;
    }

    Res *res1;
    if (strcmp(copy_node->label, "UNARY_OP") == 0) {
      res1 = unary_op_tac(copy_node);
    } else if (strcmp(copy_node->label, "ARITHORBOOLEXP") == 0) {
      res1 = arith_or_bool_tac(copy_node);
    }

    ast_node = ast_node->next;
    if (strcmp(ast_node->next->label, "ARREXPR") == 0) {
      arr_tac(ast_node, res1->tempVar);
    } else {
      QuadNode *new = create_new_quad_node();
      new->op = ASSIGN;
      // printf("token for assign: %s\n", get_token_value(ast_node->token));
      new->arg1 = res1->tempVar;
      new->arg2 = NULL;
      new->result = get_token_value(ast_node->token);
      insert_quadnode_at_tail(new, quadruple);
      // print_quadnode(new);
    }

    int end = genPref;

    genPref -= (end - curr);

    while (strcmp(ast_node->label, "ASSIGNSTMT_END") != 0)
      ast_node = ast_node->next;

    return make_res("NULL", ast_node);
  }

  return make_res("NO_MATCH", ast_node);
}

Res *case_stmt_tac(char *var, AST_Node *ast_node, char *end_label) {
  if (strcmp(ast_node->label, "CASE") == 0) {
    ast_node = ast_node->next;
    QuadNode *val = create_new_quad_node();
    val->arg2 = get_token_value(ast_node->token);
    val->arg1 = var;
    val->op = IF_TRUE_GOTO;
    val->result = compilerGeneratedLabel();
    insert_quadnode_at_tail(val, quadruple);

    QuadNode *val2 = create_new_quad_node();
    val2->op = LABEL;
    val2->result = val->result;

    insert_quadnode_at_tail(val2, quadruple);
    // print_quadnode(val2);

    // Statement process
    ast_node = ast_node->next;
    Res *res = statements_tac(ast_node);
    ast_node = res->ret;
  }
  if (strcmp(ast_node->label, "DEFAULTCASE") == 0) {
    printf("inside default case\n");
    ast_node = ast_node->next;

    QuadNode *val2 = create_new_quad_node();
    val2->op = LABEL;
    val2->result = compilerGeneratedLabel();

    insert_quadnode_at_tail(val2, quadruple);
    // print_quadnode(val2);

    // Statements process
    Res *res = statements_tac(ast_node);
    ast_node = res->ret;
  }

  QuadNode *jump = create_new_quad_node();
  jump->op = GOTO_UNCOND;
  jump->result = end_label;
  insert_quadnode_at_tail(jump, quadruple);

  return make_res("NULL", ast_node);
}

Res *condn_stmt_tac(AST_Node *ast_node) {
  // printf("condn stmt, here label: %s\n", ast_node->label);
  if (strcmp(ast_node->label, "SWITCH") == 0) {
    ast_node = ast_node->next;
    char *var = get_token_value(ast_node->token);
    // printf("VAR NAME: %s\n", var);
    ast_node = ast_node->next;
    if (strcmp(ast_node->label, "CASES") == 0) {

      ast_node = ast_node->next;

      AST_Node *copy_node = copy_AST_Node(ast_node);

      int cases = 0;
      while (strcmp(copy_node->label, "SWITCH_END") != 0) {
        if (strcmp(copy_node->label, "CASE") == 0)
          cases++;
        copy_node = copy_node->next;
      }

      int digits = count_digits_in_int(labelPref + cases + 1);
      char *num = (char *)malloc(digits * sizeof(char));
      sprintf(num, "%d", labelPref + cases + 1);
      char *str = (char *)malloc((digits + 1) * sizeof(char));
      str[0] = 'l';
      strncat(str, num, digits);

      // final jump label.

      while (strcmp(ast_node->label, "SWITCH_END") != 0) {
        Res *res = case_stmt_tac(var, ast_node, str);
        ast_node = res->ret;
        ast_node = ast_node->next;
      }
    }

    QuadNode *val = create_new_quad_node();
    val->op = LABEL;
    val->result = compilerGeneratedLabel();

    return make_res("NULL", ast_node);
  }
  return make_res("NO_MATCH", ast_node);
}

Res *iterative_stmt_tac(AST_Node *ast_node) {
  // printf("itr stmt, here label: %s\n", ast_node->label);
  if (strcmp(ast_node->label, "FORLOOP") == 0) {
    ast_node = ast_node->next; // x
    char *temp =
        get_token_value(ast_node->token); // index value ( ->X  in  1..5)
    ast_node = ast_node->next;            // INDEX_FOR_LOOP
    ast_node = ast_node->next;            // start index

    // assign stmt;
    TOKEN start_index = ast_node->token;

    QuadNode *index = create_new_quad_node();
    index->arg1 = get_token_value(ast_node->token); // start value
    index->arg2 = NULL;
    index->op = ASSIGN;
    index->result = compilerGeneratedTemporary();

    insert_quadnode_at_tail(index, quadruple);

    QuadNode *index2 = create_new_quad_node();
    index2->arg1 = index->result;
    index2->arg2 = NULL;
    index2->op = ASSIGN;
    index2->result = temp;
    insert_quadnode_at_tail(index2, quadruple);

    // Label stmt
    QuadNode *label = create_new_quad_node();
    label->arg1 = NULL;
    label->arg2 = NULL;
    label->op = LABEL;
    label->result = compilerGeneratedLabel();
    insert_quadnode_at_tail(label, quadruple);

    ast_node = ast_node->next->next;
    TOKEN end_index = ast_node->token;

    // LE, GE stmt
    bool is_GE = false;
    QuadNode *cmp = create_new_quad_node();
    cmp->arg2 = temp;
    cmp->arg1 = get_token_value(end_index);
    if (start_index.num > end_index.num) {
      cmp->op = GE;
      is_GE = true;
    } else
      cmp->op = LE;
    // to go from start index to end index

    cmp->result = compilerGeneratedTemporary();
    // print_quadnode(cmp);
    insert_quadnode_at_tail(cmp, quadruple);

    QuadNode *iftruecomparisonresult = create_new_quad_node();
    iftruecomparisonresult->op = IF_TRUE_GOTO;
    iftruecomparisonresult->arg1 = cmp->result;
    iftruecomparisonresult->result = compilerGeneratedLabel();
    insert_quadnode_at_tail(iftruecomparisonresult, quadruple);

    QuadNode *iffalsecomparisonresult = create_new_quad_node();
    iffalsecomparisonresult->op = GOTO_UNCOND;
    iffalsecomparisonresult->result = compilerGeneratedLabel();
    insert_quadnode_at_tail(iffalsecomparisonresult, quadruple);

    QuadNode *label2 = create_new_quad_node();
    label2->op = LABEL;
    label2->result = iftruecomparisonresult->result;
    insert_quadnode_at_tail(label2, quadruple);

    // rest statements
    //---------------add switch statement----------------
    ast_node = ast_node->next; // statements
    // printf(" @@@@@@@@@ THE LABEL HERE IS: %s \n", ast_node->label);
    //
    Res *res = statements_tac(ast_node);
    ast_node = res->ret;

    // printf("yeh yaha pe aa chuke hai apne lund\n");

    // increment, decrement
    QuadNode *inc_dec = create_new_quad_node();
    inc_dec->arg1 = temp;
    char *num = (char *)malloc(sizeof(char));
    sprintf(num, "%d", 1);
    inc_dec->arg2 = num;
    if (is_GE)
      inc_dec->op = SUB;
    else
      inc_dec->op = PLUS;
    inc_dec->result = compilerGeneratedTemporary();
    insert_quadnode_at_tail(inc_dec, quadruple);

    QuadNode *assign = create_new_quad_node();
    assign->arg1 = inc_dec->result;
    assign->op = ASSIGN;
    assign->result = temp;
    insert_quadnode_at_tail(assign, quadruple);

    QuadNode *jump = create_new_quad_node();
    jump->op = GOTO_UNCOND;
    jump->result = label->result;
    insert_quadnode_at_tail(jump, quadruple);

    QuadNode *label3 = create_new_quad_node();
    label3->op = LABEL;
    label3->result = iffalsecomparisonresult->result;
    insert_quadnode_at_tail(label3, quadruple);

    return make_res("NULL", ast_node);
  }
  return make_res("NO_MATCH", ast_node);
}

Res *statements_tac(AST_Node *ast_node) {
  if (strcmp(ast_node->label, "STATEMENTS") == 0) {
    ast_node = ast_node->next;

    while (strcmp(ast_node->label, "STATEMENTS_END") != 0) {
      Res *res;

      res = assignment_tac(ast_node);

      if (strcmp(res->tempVar, "NO_MATCH") != 0) {
        ast_node = res->ret;
        ast_node = ast_node->next;

        continue;
      }

      res = arith_or_bool_tac(ast_node);

      if (strcmp(res->tempVar, "NO_MATCH") != 0) {
        ast_node = res->ret;
        ast_node = ast_node->next;
        continue;
      }

      res = condn_stmt_tac(ast_node);
      if (strcmp(res->tempVar, "NO_MATCH") != 0) {
        ast_node = res->ret;
        ast_node = ast_node->next;
        continue;
      }

      res = print_func_tac(ast_node);

      if (strcmp(res->tempVar, "NO_MATCH") != 0) {
        ast_node = res->ret;
        ast_node = ast_node->next;
        continue;
      }

      res = iterative_stmt_tac(ast_node);
      if (strcmp(res->tempVar, "NO_MATCH") != 0) {
        ast_node = res->ret;
        ast_node = ast_node->next;
        continue;
      }

      if (ast_node == NULL)
        break;
      ast_node = ast_node->next;
    }

    // printf("CUASE ITS A RKB\n");
    return make_res("NULL", ast_node);
  }
  return make_res("NO_MATCH", ast_node);
}

Res *unary_op_tac(AST_Node *ast_node) {

  if (strcmp(ast_node->label, "UNARY_OP") == 0) {

    ast_node = ast_node->next;
    QuadNode *new = create_new_quad_node();
    new->arg1 = get_token_value(ast_node->token);

    if (strcmp(new->arg1, "-") == 0)
      new->op = UMINUS;
    else
      new->op = UPLUS;

    Res *res = math_op_tac(ast_node->next);
    ast_node = res->ret;
    new->arg2 = res->tempVar;

    new->result = compilerGeneratedTemporary();
    // print_quadnode(new);
    insert_quadnode_at_tail(new, quadruple);

    return make_res(new->result, ast_node);
  }
  return make_res("NO_MATCH", ast_node);
}

Res *print_func_tac(AST_Node *ast_node) {
  if (strcmp(ast_node->label, "PRINT") == 0) {
    ast_node = ast_node->next;

    QuadNode *new = create_new_quad_node();

    if (strcmp(ast_node->label, "ARRAY_ACCESS") == 0) {

      ast_node = ast_node->next;

      QuadNode *array_acess = create_new_quad_node();
      array_acess->op = ARRAY_ACCESS;
      array_acess->arg1 = get_token_value(ast_node->token);

      ast_node = ast_node->next->next;

      if (strcmp(get_token_value(ast_node->token), "-") == 0) {
        ast_node = ast_node->next;

        char *index = (char *)malloc(32 * sizeof(char));

        strcat(index, "-");
        strcat(index, get_token_value(ast_node->token));

        array_acess->arg2 = index;
        array_acess->result = compilerGeneratedTemporary();

      } else {
        array_acess->arg2 = get_token_value(ast_node->token);
        array_acess->result = compilerGeneratedTemporary();
      }

      // print_quadnode(array_acess);
      insert_quadnode_at_tail(array_acess, quadruple);

      new->op = PRINT;
      new->arg1 = array_acess->result;
      new->arg2 = NULL;
      new->result = NULL;

      // print_quadnode(new);
      insert_quadnode_at_tail(new, quadruple);

    } else {
      new->op = PRINT;
      new->arg1 = get_token_value(ast_node->token);
      new->arg2 = NULL;
      new->result = NULL;

      // print_quadnode(new);
      insert_quadnode_at_tail(new, quadruple);
    }

    return make_res("NULL", ast_node);
  }

  return make_res("NO_MATCH", ast_node);
}

Res *get_value_tac(AST_Node *ast_node) {
  if (strcmp(ast_node->label, "GET_VALUE") == 0) {
    ast_node = ast_node->next;

    QuadNode *new = create_new_quad_node();
    new->op = GET_VALUE;
    new->arg1 = get_token_value(ast_node->token);
    new->arg2 = NULL;
    new->result = NULL;

    // print_quadnode(new);
    insert_quadnode_at_tail(new, quadruple);

    return make_res("NULL", ast_node);
  }
  return make_res("NO_MATCH", ast_node);
}

Res *fun_call_tac(AST_Node *ast_node) {
  if (strcmp(ast_node->label, "FUNCTION_CALL") == 0) {

    ast_node = ast_node->next;
    AST_Node *copy_node = copy_AST_Node(ast_node);

    while (strcmp(copy_node->label, "PARAMETERS") != 0)
      copy_node = copy_node->next;

    copy_node = copy_node->next;

    int count = 0;
    while (strcmp(copy_node->label, "FUNCTION_CALL_END") != 0) {
      char *parameter;
      if (strcmp(get_token_value(copy_node->token), "-") == 0) {
        copy_node = copy_node->next;
        parameter = (char *)malloc(32 * sizeof(char));

        strcat(parameter, "-");
        strcat(parameter, get_token_value(copy_node->token));

      } else {
        parameter = get_token_value(copy_node->token);
      }

      if (strcmp(copy_node->next->label, "ARREXPR") == 0) {
        copy_node = copy_node->next->next;
        Res *res = math_op_tac(copy_node);

        copy_node = res->ret;

        QuadNode *new = create_new_quad_node();

        new->op = MUL;
        new->arg1 = res->tempVar;
        new->arg2 = "4-size";
        new->result = compilerGeneratedTemporary();

        insert_quadnode_at_tail(new, quadruple);

        QuadNode *new2 = create_new_quad_node();
        new2->op = ASSIGN;

        strcat(parameter, "[");
        strcat(parameter, new->result);
        strcat(parameter, "]");

        new2->arg1 = parameter;
        new2->result = compilerGeneratedTemporary();

        insert_quadnode_at_tail(new2, quadruple);

        parameter = new2->result;

        while (strcmp(copy_node->label, "ARREXPR_END") != 0) {
          copy_node = copy_node->next;
        }
      }

      if (strcmp(copy_node->next->label, "ARR_INDEX") == 0) {
        copy_node = copy_node->next->next;

        char *index = (char *)malloc(33 * sizeof(char));
        strcat(index, get_token_value(copy_node->token));

        if (strcmp(copy_node->next->label, "ARREXPR") == 0) {
          copy_node = copy_node->next->next;

          Res *res = math_op_tac(copy_node);
          copy_node = res->ret;

          QuadNode *new = create_new_quad_node();
          new->op = MUL;
          new->arg1 = res->tempVar;
          new->arg2 = "4-size";
          new->result = res->tempVar;

          insert_quadnode_at_tail(new, quadruple);

          QuadNode *new3 = create_new_quad_node();
          if (strcmp(index, "-") == 0) {
            new3->op = SUB;
            new3->arg1 = "0";
            new3->arg2 = res->tempVar;
            new3->result = new->result;
            insert_quadnode_at_tail(new3, quadruple);
          }

          QuadNode *new2 = create_new_quad_node();
          new2->op = ASSIGN;

          if (new3->result == NULL)
            new3->result = new->result;

          strcat(parameter, "[");
          strcat(parameter, new3->result);
          strcat(parameter, "]");

          new2->arg1 = parameter;
          new2->result = new->result;

          insert_quadnode_at_tail(new2, quadruple);

          parameter = new2->result;

          while (strcmp(copy_node->label, "ARR_INDEX_END") != 0) {
            copy_node = copy_node->next;
          }

        } else {

          copy_node = copy_node->next;
          strcat(index, get_token_value(copy_node->token));
        }
      }

      QuadNode *new = create_new_quad_node();
      new->op = ACTUAL_PARAM;
      new->arg1 = parameter;
      new->arg2 = NULL;
      new->result = NULL;

      insert_quadnode_at_tail(new, quadruple);
      count++;

      copy_node = copy_node->next;
    }

    // printf("after while loop\n");
    //

    printf("AST NODE LABEL: %s\n", ast_node->label);

    Quadruple *quad = create_quadlist();
    if (strcmp(ast_node->label, "OPTIONAL_PARAMETERS") == 0) {
      ast_node = ast_node->next;

      while (strcmp(ast_node->label, "MODULE") != 0) {
        QuadNode *new = create_new_quad_node();
        new->op = RETURN_PARAM;
        new->arg1 = get_token_value(ast_node->token);
        new->arg2 = NULL;
        new->result = NULL;

        insert_quadnode_at_tail(new, quad);

        ast_node = ast_node->next;
      }
    }

    printf("AST NODE LABEL: %s\n", ast_node->label);

    ast_node = ast_node->next;
    QuadNode *new = create_new_quad_node();
    new->op = FUNC_CALL;
    new->arg1 = get_token_value(ast_node->token);
    char *co_par = (char *)malloc(count_digits_in_int(count) * sizeof(char));
    sprintf(co_par, "%d", count);
    printf("co par : %s\n", co_par);
    new->arg2 = co_par;
    new->result = NULL;

    insert_quadnode_at_tail(new, quadruple);
    merge_at_tail(quadruple, quad);

    printf("AST NODE LABEL: %s %s\n", ast_node->label,
           get_token_value(ast_node->token));

    while (strcmp(ast_node->label, "FUNCTION_CALL_END") != 0)
      ast_node = ast_node->next;

    return make_res("NULL", ast_node);
  }

  return make_res("NO_MATCH", ast_node);
}

// void convert_to_three_address_code(AST) {}
// THREE ADDRESS CODE FOR TESTCASE.txt FILE
// FUNC_DEF MOD1 NULL NULL
// ASSIGN   -10 NULL  index
// index = -10
// L1 : if index > 15 goto L2
// var = 0
// L3 : if var >= 0 goto L4
// var = var + 1
// goto L3
// L4 : index = index + 1
// goto L1
// L2 :
//
Res *function_def_tac(AST_Node *ast_node) {
  if (strcmp(ast_node->label, "MODULE") == 0) {
    ast_node = ast_node->next;

    // label to jump to
    QuadNode *val = create_new_quad_node();
    val->op = LABEL;
    val->result =
        get_token_value(ast_node->token); // label name as name of module
    insert_quadnode_at_tail(val, quadruple);

    //------input parameter list-----------
    ast_node = ast_node->next;

    if (strcmp(ast_node->label, "INPUT_PARAMETERS_LIST") == 0) {
      ast_node = ast_node->next;
      while (strcmp(ast_node->label, "INPUT_PARAMETERS_LIST_END") != 0) {
        char *name = get_token_value(ast_node->token);

        QuadNode *node = create_new_quad_node();
        node->arg1 = name;
        node->op = INP_PARAM;
        insert_quadnode_at_tail(node, quadruple);

        ast_node = ast_node->next;
        if (strcmp(ast_node->label, "ARRAY") == 0)
          ast_node = ast_node->next->next->next->next->next->next->next;

        else
          ast_node = ast_node->next;
      }
    }

    //------output parameter list------------
    ast_node = ast_node->next;

    if (strcmp(ast_node->label, "RETURN_PARAMETERS_LIST") == 0) {
      ast_node = ast_node->next;
      while (strcmp(ast_node->label, "RETURN_PARAMETERS_LIST_END") != 0) {
        char *name = get_token_value(ast_node->token);

        QuadNode *node = create_new_quad_node();
        node->arg1 = name;
        node->op = OUTP_PARAM;
        insert_quadnode_at_tail(node, quadruple);

        ast_node = ast_node->next;
        if (strcmp(ast_node->label, "ARRAY") == 0)
          ast_node = ast_node->next->next->next->next->next->next->next;

        else
          ast_node = ast_node->next;
      }
    }

    //-------statement process----------------

    if (strcmp(ast_node->label, "STATEMENTS") == 0) {
      Res *res = statements_tac(ast_node);
      ast_node = res->ret;
    }

    while (strcmp(ast_node->label, "MODULE_END")) {
      ast_node = ast_node->next;
    }

    return make_res("NULL", ast_node);
  }
  return make_res("NO_MATCH", ast_node);
}

Quadruple *run_inter_code_gen(char *prog_file, char *output_file) {
  create_scopes(prog_file, output_file);
  run_ast(prog_file, output_file);

  printf("\n\n------------- THREE ADDRESS CODE OUTPUT -------------\n\n");

  quadruple = create_quadlist();
  AST_Node *temp = Parse_Tree_Root->head->list->head;

  while (temp != NULL) {
    Res *res;

    res = function_def_tac(temp);

    if (strcmp(res->tempVar, "NO_MATCH") != 0) {
      temp = res->ret;
      temp = temp->next;
      continue;
    }

    res = assignment_tac(temp);

    if (strcmp(res->tempVar, "NO_MATCH") != 0) {
      temp = res->ret;
      temp = temp->next;
      continue;
    }

    res = arith_or_bool_tac(temp);

    if (strcmp(res->tempVar, "NO_MATCH") != 0) {
      temp = res->ret;
      temp = temp->next;
      continue;
    }

    res = condn_stmt_tac(temp);
    if (strcmp(res->tempVar, "NO_MATCH") != 0) {
      temp = res->ret;
      temp = temp->next;
      continue;
    }

    res = print_func_tac(temp);
    if (strcmp(res->tempVar, "NO_MATCH") != 0) {
      temp = res->ret;
      temp = temp->next;
      continue;
    }

    res = get_value_tac(temp);
    if (strcmp(res->tempVar, "NO_MATCH") != 0) {
      temp = res->ret;
      temp = temp->next;
      continue;
    }

    res = fun_call_tac(temp);
    if (strcmp(res->tempVar, "NO_MATCH") != 0) {
      temp = res->ret;
      temp = temp->next;
      continue;
    }

    res = iterative_stmt_tac(temp);
    if (strcmp(res->tempVar, "NO_MATCH") != 0) {
      temp = res->ret;
      temp = temp->next;
      continue;
    }

    // printf("while label: %s\n", temp->label);

    if (temp == NULL)
      break;
    temp = temp->next;
  }

  print_quadlist(quadruple, stdout);

  return quadruple;
}
