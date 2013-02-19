#ifndef __HJ_RBTREE_H__
#define __HJ_RBTREE_H__

#include <stdio.h>

typedef enum
{
    RB_RED = 0,
    RB_BLACK = 1
} ENUM_RB_COLOR;

struct HJ_RB_node
{
    unsigned long  ulParentColor;
    struct HJ_RB_node *pRight;
    struct HJ_RB_node *pLeft;
} __attribute__((aligned(sizeof(long))));
/* The alignment might seem pointless, but allegedly CRIS needs it */

struct HJ_RB_root
{
    struct HJ_RB_node *pRBNode;
};

#define HJ_RB_parent(r)     ((struct HJ_RB_node *)((r)->ulParentColor & ~3))
#define HJ_RB_color(r)      ((r)->ulParentColor & 1)
#define HJ_RB_is_red(r)     (!HJ_RB_color(r))
#define HJ_RB_is_black(r)   HJ_RB_color(r)
#define HJ_RB_set_red(r)    do { (r)->ulParentColor &= ~1; } while (0)
#define HJ_RB_set_black(r)  do { (r)->ulParentColor |= 1; } while (0)

static inline void HJ_RB_set_parent(struct HJ_RB_node *rb, struct HJ_RB_node *p)
{
    rb->ulParentColor = (rb->ulParentColor & 3) | (unsigned long)p;
}
static inline void HJ_RB_set_color(struct HJ_RB_node *rb, int color)
{
    rb->ulParentColor = (rb->ulParentColor & ~1) | color;
}

#define HJ_RB_ROOT (struct HJ_RB_root) { NULL, }
#define HJ_RB_Entery(ptr, type, member) _HJ_container_of(ptr, type, member)

#define _HJ_container_of(ptr, type, member) ({\
    const typeof( ((type *)0)->member ) *__mptr = (ptr);\
    (type *)( (char *)__mptr - _HJ_offsetof(type,member) );})

#define _HJ_offsetof(type, member) ((size_t) &((type *)0)->member)

#define HJ_RB_EMPTY_ROOT(root) ((root)->pRBNode == NULL)
#define HJ_RB_EMPTY_NODE(node) (HJ_RB_parent(node) == node)
#define HJ_RB_CLEAR_NODE(node) (HJ_RB_set_parent(node, node))

void HJ_RB_insert_color(struct HJ_RB_node *, struct HJ_RB_root *);
void HJ_RB_erase(struct HJ_RB_node *, struct HJ_RB_root *);

/* Find logical next and previous nodes in a tree */
struct HJ_RB_node *HJ_RB_next(struct HJ_RB_node *);
struct HJ_RB_node *HJ_RB_prev(struct HJ_RB_node *);
struct HJ_RB_node *HJ_RB_first(struct HJ_RB_root *);
struct HJ_RB_node *HJ_RB_last(struct HJ_RB_root *);

/* Fast replacement of a single node without remove/rebalance/add/rebalance */
void HJ_RB_replace_node(struct HJ_RB_node *victim, struct HJ_RB_node *newnode
    , struct HJ_RB_root *root);

static inline void HJ_RB_link_node(struct HJ_RB_node *node, struct HJ_RB_node *parent
    , struct HJ_RB_node **HJ_RB_link)
{
    node->ulParentColor = (unsigned long )parent;
    node->pLeft = node->pRight = NULL;

    *HJ_RB_link = node;
}

#endif
