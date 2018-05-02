#ifndef LF_UTILS_H_
#define LF_UTILS_H_

#include "lf_node.h"

int lf_cas(struct lf_node **, struct lf_node *, struct lf_node *);
void *lf_malloc(int);
void lf_free(void *);

#endif //LF_UTILS_H_
