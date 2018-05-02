#include <stdlib.h>
#include <stdatomic.h>
#include "lf_node.h"

int lf_cas(struct lf_node **obj, struct lf_node *expected, struct lf_node *desired){
    return __sync_bool_compare_and_swap(obj, expected, desired); 
}

void *lf_malloc(int size){
    return malloc(size);
}

void lf_free(void *p){
    free(p);
}
