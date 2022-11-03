#ifndef SLL_NODE_H__
#define SLL_NODE_H__
typedef struct NODE {
  struct NODE *link;
  int value;
} Node;

int sll_insert1(Node *current, int new_value);
int sll_insert2(Node **rootp, int new_value);
int sll_insert3(register Node **linkp, int new_value);

Node *search_list(Node *node, void const *value, int (*compare)(void const *, void const *));

#endif
