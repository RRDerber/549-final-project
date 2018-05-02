#ifndef HAZLIST_H_
#define HAZLIST_H_

#include "lf_node.h"

struct hazlist{
    struct lf_node *head;
    int size;
};

struct hazlist *init_hazlist();
void destroy_hazlist(struct hazlist *);
int hazlist_push(struct hazlist *, struct lf_node *);
struct lf_node *hazlist_pop(struct hazlist *);

#endif //HAZLIST_H_
