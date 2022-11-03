#ifndef DLL_NODE_H__
#define DLL_NODE_H__
typedef struct NODE {
  struct NODE *fwd;
  struct NODE *bwd;
  int value;
} Node;

int dll_insert(Node *rootp, int value);
int dll_insert2(Node *rootp, int value);

#endif
