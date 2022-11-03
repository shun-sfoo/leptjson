#include <stdlib.h>

#include "doubly_linked_list_node.h"

int dll_insert(Node *rootp, int value) {
  Node *this;
  Node *next;
  Node *newnode;

  /* 查看value是否已经存在于链表中，如果是就返回。
   * 否则，为新值创建一个新节点
   * this 将指向应该在新节点之前的那个节点
   * next 将指向应该在新节点之后的那个节点
   */
  for (this = rootp; (next = this->fwd) != NULL; this = next) {
    if (next->value == value) return 0;
    if (next->value > value) break;
  }

  newnode = (Node *)malloc(sizeof(Node));

  if (newnode == NULL) return -1;

  newnode->value = value;

  if (next != NULL) {     // 并非位于链表尾部
    if (this != rootp) {  // 情况1 并非位于链表起始位置
      newnode->fwd = next;
      this->fwd = newnode;
      newnode->bwd = this;
      next->bwd = newnode;
    } else {  // 情况2 位于链表起始位置
      newnode->fwd = next;
      rootp->fwd = newnode;
      newnode->bwd = NULL;
      next->bwd = newnode;
    }
  } else {                // 位于链表尾部
    if (this != rootp) {  // 并非位于链表的起始位置
      newnode->fwd = NULL;
      this->fwd = newnode;
      newnode->bwd = this;
      rootp->bwd = newnode;
    } else {  // 位于链表的起始位置
      newnode->fwd = NULL;
      rootp->fwd = newnode;
      newnode->bwd = NULL;
      rootp->bwd = newnode;
    }
  }
  return 1;
}

int dll_insert2(register Node *rootp, int value) {
  register Node *this;
  register Node *next;
  register Node *newnode;

  for (this = rootp; (next = this->fwd) != NULL; this = next) {
    if (next->value == value) return 0;
    if (next->value > value) break;
  }

  newnode = (Node *)malloc(sizeof(Node));
  if (newnode == NULL) return -1;
  newnode->value = value;

  newnode->fwd = next;
  this->fwd = newnode;

  if (this != rootp)
    newnode->bwd = this;
  else
    newnode->bwd = NULL;

  if (next != NULL)
    next->bwd = newnode;
  else
    rootp->bwd = newnode;

  // simpest
  /* newnode->fwd = next; */
  /* this->fwd = newnode; */
  /* newnode->bwd = this != rootp ? this : NULL; */
  /* (next != NULL ? next : rootp)->bwd = newnode; */

  return 1;
}
