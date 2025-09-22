#ifndef __GLTHREAD__
#define __GLTHREAD__

#include <stdint.h>

typedef struct glthread_node_ {
    struct glthread_node_ *left;
    struct glthread_node_ *right;
} glthread_node_t; 

typedef struct glthread_ {
    glthread_node_t *head;
    glthread_node_t *tail;
    unsigned int offset;
    int size;
} glthread_t;

void glthread_add(glthread_t *lst, glthread_node_t *glnode);
glthread_node_t *glthread_remove(glthread_t *lst, glthread_node_t *glnode);

/*Iterative macro to Iterate Over GLTHhreads*/
#define ITERATE_GL_THREADS_BEGIN(lstptr, struct_type, ptr)      \
{                                                               \
    glthread_node_t *_glnode = NULL, *_next = NULL;             \
    for(_glnode = lstptr->head->right; _glnode != lstptr->tail; _glnode = _next){      \
        _next = _glnode->right;                                 \
        ptr = (struct_type *)((char *)_glnode - lstptr->offset);

#define ITERATE_GL_THREADS_ENDS }}

#define glthread_node_init(glnode)  \
    glnode->left = NULL;            \
    glnode->right = NULL;

void glthread_init(glthread_t *glthread, unsigned int offset);
void glthread_destroy(glthread_t *glthread);

#define offsetof(struct_name, field_name)   \
    ((unsigned int)(uintptr_t)&((struct_name *)0)->field_name)

#define tostruct(struct_name, lstptr, node) \
    ((struct_name *) ((char *) node - lstptr->offset))

#endif
