#include "hj_rbtree.h"

static void __HJ_RB_rotate_left(struct HJ_RB_node *node, struct HJ_RB_root *root)
{
    struct HJ_RB_node *right = node->pRight;
    struct HJ_RB_node *parent = HJ_RB_parent(node);

    if ((node->pRight = right->pLeft))
    {
        HJ_RB_set_parent(right->pLeft, node);
    }
    right->pLeft = node;

    HJ_RB_set_parent(right, parent);

    if (parent)
    {
        if (node == parent->pLeft)
        {
            parent->pLeft = right;
        }
        else
        {
            parent->pRight = right;
        }
    }
    else
    {
        root->pRBNode = right;
    }
    HJ_RB_set_parent(node, right);
}

static void __HJ_RB_rotate_right(struct HJ_RB_node *node, struct HJ_RB_root *root)
{
    struct HJ_RB_node *left = node->pLeft;
    struct HJ_RB_node *parent = HJ_RB_parent(node);

    if ((node->pLeft = left->pRight))
    {
        HJ_RB_set_parent(left->pRight, node);
    }
    left->pRight = node;

    HJ_RB_set_parent(left, parent);

    if (parent)
    {
        if (node == parent->pRight)
        {
            parent->pRight = left;
        }
        else
        {
            parent->pLeft = left;
        }
    }
    else
    {
        root->pRBNode = left;
    }
    HJ_RB_set_parent(node, left);
}

void HJ_RB_insert_color(struct HJ_RB_node *node, struct HJ_RB_root *root)
{
    struct HJ_RB_node *parent, *gparent;

    while ((parent = HJ_RB_parent(node)) && HJ_RB_is_red(parent))
    {
        gparent = HJ_RB_parent(parent);

        if (parent == gparent->pLeft)
        {
            {
                register struct HJ_RB_node *uncle = gparent->pRight;
                if (uncle && HJ_RB_is_red(uncle))
                {
                    HJ_RB_set_black(uncle);
                    HJ_RB_set_black(parent);
                    HJ_RB_set_red(gparent);
                    node = gparent;
                    continue;
                }
            }

            if (parent->pRight == node)
            {
                register struct HJ_RB_node *tmp;
                __HJ_RB_rotate_left(parent, root);
                tmp = parent;
                parent = node;
                node = tmp;
            }

            HJ_RB_set_black(parent);
            HJ_RB_set_red(gparent);
            __HJ_RB_rotate_right(gparent, root);
        }
        else
        {
            {
                register struct HJ_RB_node *uncle = gparent->pLeft;
                if (uncle && HJ_RB_is_red(uncle))
                {
                    HJ_RB_set_black(uncle);
                    HJ_RB_set_black(parent);
                    HJ_RB_set_red(gparent);
                    node = gparent;
                    continue;
                }
            }

            if (parent->pLeft == node)
            {
                register struct HJ_RB_node *tmp;
                __HJ_RB_rotate_right(parent, root);
                tmp = parent;
                parent = node;
                node = tmp;
            }

            HJ_RB_set_black(parent);
            HJ_RB_set_red(gparent);
            __HJ_RB_rotate_left(gparent, root);
        }
    }

    HJ_RB_set_black(root->pRBNode);
}

static void __HJ_RB_erase_color(struct HJ_RB_node *node, struct HJ_RB_node *parent
    , struct HJ_RB_root *root)
{
    struct HJ_RB_node *other;

    while ((!node || HJ_RB_is_black(node)) && node != root->pRBNode)
    {
        if (parent->pLeft == node)
        {
            other = parent->pRight;
            if (HJ_RB_is_red(other))
            {
                HJ_RB_set_black(other);
                HJ_RB_set_red(parent);
                __HJ_RB_rotate_left(parent, root);
                other = parent->pRight;
            }

            if ((!other->pLeft || HJ_RB_is_black(other->pLeft))
                && (!other->pRight || HJ_RB_is_black(other->pRight)))
            {
                HJ_RB_set_red(other);
                node = parent;
                parent = HJ_RB_parent(node);
            }
            else
            {
                if (!other->pRight || HJ_RB_is_black(other->pRight))
                {
                    struct HJ_RB_node *o_left;
                    if ((o_left = other->pLeft))
                    {
                        HJ_RB_set_black(o_left);
                    }
                    HJ_RB_set_red(other);
                    __HJ_RB_rotate_right(other, root);
                    other = parent->pRight;
                }
                HJ_RB_set_color(other, HJ_RB_color(parent));
                HJ_RB_set_black(parent);
                if (other->pRight)
                {
                    HJ_RB_set_black(other->pRight);
                }
                __HJ_RB_rotate_left(parent, root);
                node = root->pRBNode;
                break;
            }
        }
        else
        {
            other = parent->pLeft;
            if (HJ_RB_is_red(other))
            {
                HJ_RB_set_black(other);
                HJ_RB_set_red(parent);
                __HJ_RB_rotate_right(parent, root);
                other = parent->pLeft;
            }

            if ((!other->pLeft || HJ_RB_is_black(other->pLeft))
                && (!other->pRight || HJ_RB_is_black(other->pRight)))
            {
                HJ_RB_set_red(other);
                node = parent;
                parent = HJ_RB_parent(node);
            }
            else
            {
                if (!other->pLeft || HJ_RB_is_black(other->pLeft))
                {
                    register struct HJ_RB_node *o_right;
                    if ((o_right = other->pRight))
                    {
                        HJ_RB_set_black(o_right);
                    }
                    HJ_RB_set_red(other);
                    __HJ_RB_rotate_left(other, root);
                    other = parent->pLeft;
                }
                HJ_RB_set_color(other, HJ_RB_color(parent));
                HJ_RB_set_black(parent);
                if (other->pLeft)
                {
                    HJ_RB_set_black(other->pLeft);
                }
                __HJ_RB_rotate_right(parent, root);
                node = root->pRBNode;
                break;
            }
        }
    }

    if (node)
    {
        HJ_RB_set_black(node);
    }
}

void HJ_RB_erase(struct HJ_RB_node *node, struct HJ_RB_root *root)
{
    struct HJ_RB_node *child, *parent;
    int color;

    if (!node->pLeft)
    {
        child = node->pRight;
    }
    else if (!node->pRight)
    {
        child = node->pLeft;
    }
    else
    {
        struct HJ_RB_node *old = node, *left;

        node = node->pRight;
        while ((left = node->pLeft) != NULL)
        {
            node = left;
        }
        child = node->pRight;
        parent = HJ_RB_parent(node);
        color = HJ_RB_color(node);

        if (child)
        {
            HJ_RB_set_parent(child, parent);
        }

        if (parent == old)
        {
            parent->pRight = child;
            parent = node;
        }
        else
        {
            parent->pLeft = child;
        }

        node->ulParentColor = old->ulParentColor;
        node->pRight = old->pRight;
        node->pLeft = old->pLeft;

        if (HJ_RB_parent(old))
        {
            if (HJ_RB_parent(old)->pLeft == old)
            {
                HJ_RB_parent(old)->pLeft = node;
            }
            else
            {
                HJ_RB_parent(old)->pRight = node;
            }
        }
        else
        {
            root->pRBNode = node;
        }

        HJ_RB_set_parent(old->pLeft, node);
        if (old->pRight)
        {
            HJ_RB_set_parent(old->pRight, node);
        }
        goto color;
    }

    parent = HJ_RB_parent(node);
    color = HJ_RB_color(node);

    if (child)
    {
        HJ_RB_set_parent(child, parent);
    }

    if (parent)
    {
        if (parent->pLeft == node)
        {
            parent->pLeft = child;
        }
        else
        {
            parent->pRight = child;
        }
    }
    else
    {
        root->pRBNode = child;
    }

color:
    if (color == RB_BLACK)
    {
        __HJ_RB_erase_color(child, parent, root);
    }
}

/*
 * This function returns the first node (in sort order) of the tree.
 */
struct HJ_RB_node *HJ_RB_first(struct HJ_RB_root *root)
{
    struct HJ_RB_node	*n;

    n = root->pRBNode;
    if (!n)
    {
        return NULL;
    }

    while (n->pLeft)
    {
        n = n->pLeft;
    }

    return n;
}

struct HJ_RB_node *HJ_RB_last(struct HJ_RB_root *root)
{
    struct HJ_RB_node *n;

    n = root->pRBNode;
    if (!n)
    {
        return NULL;
    }

    while (n->pRight)
    {
        n = n->pRight;
    }

    return n;
}

struct HJ_RB_node *HJ_RB_next(struct HJ_RB_node *node)
{
    struct HJ_RB_node *parent;

    if (HJ_RB_parent(node) == node)
    {
        return NULL;
    }

    /* If we have a right-hand child, go down and then left as far
    as we can. */
    if (node->pRight)
    {
        node = node->pRight;
        while (node->pLeft)
        {
            node=node->pLeft;
        }

        return node;
    }

    /* No right-hand children.  Everything down and left is
    smaller than us, so any 'next' node must be in the general
    direction of our parent. Go up the tree; any time the
    ancestor is a right-hand child of its parent, keep going
    up. First time it's a left-hand child of its parent, said
    parent is our 'next' node. */
    while ((parent = HJ_RB_parent(node)) && node == parent->pRight)
    {
        node = parent;
    }

    return parent;
}

struct HJ_RB_node *HJ_RB_prev(struct HJ_RB_node *node)
{
    struct HJ_RB_node *parent;

    if (HJ_RB_parent(node) == node)
    {
        return NULL;
    }

    /* If we have a left-hand child, go down and then right as far
    as we can. */
    if (node->pLeft)
    {
        node = node->pLeft;
        while (node->pRight)
        {
            node=node->pRight;
        }

        return node;
    }

    /* No left-hand children. Go up till we find an ancestor which
    is a right-hand child of its parent */
    while ((parent = HJ_RB_parent(node)) && node == parent->pLeft)
    {
        node = parent;
    }

    return parent;
}

void HJ_RB_replace_node(struct HJ_RB_node *victim, struct HJ_RB_node *newnode
    , struct HJ_RB_root *root)
{
    struct HJ_RB_node *parent = HJ_RB_parent(victim);

    /* Set the surrounding nodes to point to the replacement */
    if (parent)
    {
        if (victim == parent->pLeft)
        {
            parent->pLeft = newnode;
        }
        else
        {
            parent->pRight = newnode;
        }
    }
    else
    {
        root->pRBNode = newnode;
    }

    if (victim->pLeft)
    {
        HJ_RB_set_parent(victim->pLeft, newnode);
    }

    if (victim->pRight)
    {
        HJ_RB_set_parent(victim->pRight, newnode);
    }

    /* Copy the pointers/colour from the victim to the replacement */
    *newnode = *victim;
}
