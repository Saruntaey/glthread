#include "glthread.h"
#include <assert.h>
#include <stdlib.h>

void glthread_init(glthread_t *glthread, unsigned int offset) {
  glthread_node_t *dummy_h;
  glthread_node_t *dummy_t;

  dummy_h = calloc(1, sizeof(glthread_node_t));
  dummy_t = calloc(1, sizeof(glthread_node_t));
  dummy_h->left = NULL;
  dummy_h->right = dummy_t;
  dummy_t->left = dummy_h;
  dummy_t->right = NULL;
  glthread->head = dummy_h;
  glthread->tail = dummy_t;
  glthread->offset = offset;
  glthread->size = 0;
}

void glthread_destroy(glthread_t *glthread) {
  assert(glthread->size == 0);
  free(glthread->head);
  free(glthread->tail);
  glthread->head = NULL;
  glthread->tail = NULL;
}

void glthread_add(glthread_t *lst, glthread_node_t *glnode) {
  glthread_node_t *dummy;

  dummy = lst->tail;
  glnode->left = dummy->left;
  glnode->right = dummy;
  glnode->right->left = glnode;
  glnode->left->right = glnode;
  lst->size++;
}

glthread_node_t *glthread_remove(glthread_t *lst, glthread_node_t *glnode) {
  assert(lst->size > 0);
  if (!glnode) {
    assert(lst->head->right != lst->tail);
    glnode = lst->head->right;
  }
  glnode->right->left = glnode->left;
  glnode->left->right = glnode->right;
  glnode->left = NULL;
  glnode->right = NULL;
  lst->size--;
  return glnode;
}
