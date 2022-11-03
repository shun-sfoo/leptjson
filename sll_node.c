#include <stdlib.h>

#include "sll_node.h"

#define FALSE 0
#define TRUE  0

int sll_insert1(Node *current, int new_value) {
  Node *previous;
  Node *new;

  while (current != NULL && current->value < new_value) {
    previous = current;
    current = current->link;
  }

  new = (Node *)malloc(sizeof(Node));
  if (new == NULL) { return FALSE; }
  new->value = new_value;

  new->link = current;
  previous->link = new;
  return TRUE;
}

int sll_insert2(Node **rootp, int new_value) {
  Node *current;
  Node *previous;
  Node *new;

  current = *rootp;
  previous = NULL;

  while (current != NULL && current->value < new_value) {
    previous = current;
    current = current->link;
  }

  new = (Node *)malloc(sizeof(Node));
  if (new != NULL) return FALSE;

  new->link = current;

  if (previous == NULL)
    *rootp = new;
  else
    previous->link = new;

  return TRUE;
}

int sll_insert3(Node **linkp, int new_value) {
  register Node *current;
  register Node *new;

  while ((current = *linkp) != NULL && current->value < new_value) linkp = &current->link;

  new = (Node *)malloc(sizeof(Node));
  new->value = new_value;

  new->link = current;
  *linkp = new;

  return TRUE;
}

Node *search_list(Node *node, void const *value, int (*compare)(void const *, void const *)) {
  while (node != NULL) {
    if (compare(&node->value, value) == 0) break;
    node = node->link;
  }
  return node;
}

static int compare_ints(void const *a, void const *b) {
  if (*(int *)a == *(int *)b)
    return 0;
  else
    return 1;
}
