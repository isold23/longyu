/* llist.h - Header file for llist.c
Eugene Kim, <eekim@eekim.com>
$Id: cgi-llist.h,v 1.1.1.1 2004/02/13 07:21:11 hunter Exp $

Copyright (C) 1995 Eugene Eric Kim
All Rights Reserved
*/

#ifndef __CGI_LLIST_H__
#define __CGI_LLIST_H__

typedef struct
{
    char *name;
    char *value;
} entrytype;

typedef struct _node
{
    entrytype entry;
    struct _node *next;
} node;

typedef struct
{
    node* head;
} llist;

void list_create(llist *l);
node* list_next(node* w);
short on_list(llist *l, node *w);
short on_list_debug(llist *l, node *w);
void list_traverse(llist *l, void (*visit)(entrytype item));
node* list_insafter(llist *l, node *w, entrytype item);
void list_clear(llist *l);

#endif
