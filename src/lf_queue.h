#ifndef LF_QUEUE_H_
#define LF_QUEUE_H_

#include "lf_node.h"
#include "hprecord.h"

struct lf_queue {
    struct lf_node *head;
    struct lf_node *tail;
};

struct lf_node *new_node(void *);
struct lf_queue *lf_queue_init();
void destroy_lf_queue(struct lf_queue *);
void lf_enqueue(struct lf_queue *, void *, struct hprectype*);
struct lf_node *lf_dequeue(struct lf_queue *, struct hprectype *);

#endif //LF_QUEUE_H_
