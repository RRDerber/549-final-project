#include <stdlib.h>
#include "lf_queue.h"
#include "hprecord.h"
#include "lf_utils.h"

struct lf_node *new_node(void *data){
    struct lf_node *n = lf_malloc(sizeof(struct lf_node));
    n->next = NULL;
    n->data = data;
    return n;
}

struct lf_queue *lf_queue_init(){
    struct lf_queue *q = lf_malloc(sizeof(struct lf_queue));
    struct lf_node *n = new_node(NULL);
    q->head = n;
    q->tail = n;
    return q;
}

void destroy_lf_queue(struct lf_queue *q){
    lf_free(q);
}

void lf_enqueue(struct lf_queue *q, void *data, struct hprectype *hprec){
    struct lf_node *n, *next, *t;
    n = new_node(data);
    while(1){
        t = q->tail;
        hprec->HP[0] = t;
        if(q->tail != t) continue;
        next = t->next;
        if(q->tail != t) continue;
        if(next != NULL){
            lf_cas(&q->tail, t, next);
            continue;
        }
        if( lf_cas(&t->next, NULL, n))
            break;
    }
    lf_cas(&q->tail, t, n);
    hprec->HP[0] = NULL;
}

struct lf_node *lf_dequeue(struct lf_queue *q, struct hprectype *hprec){
    struct lf_node *h, *t, *next;
    void *data;
    while(1){
        h = q->head;
        hprec->HP[0] = h;
        if(q->head != h) continue;
        t = q->tail;
        next = h->next;
        hprec->HP[1] = next;
        if(q->head != h) continue;
        if(next == NULL) return NULL;
        if(h == t){
            lf_cas(&q->tail, t, next);
            continue;
        }
        data = next->data;
        if(lf_cas(&q->head, h, next)) break;
    }

    hprec->HP[0] = NULL;
    hprec->HP[1] = NULL;

    retire_node(h, hprec);

    return data;
}
