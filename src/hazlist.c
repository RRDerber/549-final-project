#include <stdlib.h>
#include "hazlist.h"
#include "lf_node.h"
#include "lf_utils.h"

struct hazlist *init_hazlist(){
    struct hazlist *list = lf_malloc(sizeof(struct hazlist));
    list->head = NULL;
    list->size = 0;
    return list;
}

void destroy_hazlist(struct hazlist *list){
    lf_free(list);
}

int hazlist_push(struct hazlist *list, struct lf_node *node){
    node->next = list->head;
    list->head = node;
    list->size++;
    return list->size;
}

struct lf_node *hazlist_pop(struct hazlist *list){
    struct lf_node *node;
    if(list->size < 1)
        return NULL;
    node = list->head;
    list->head = node->next;
    list->size--;
    return node;
}
