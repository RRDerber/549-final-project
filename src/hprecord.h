#ifndef HPRECORD_H_
#define HPRECORD_H_
#include "lf_node.h"
#include "hazlist.h"

struct hprectype{
    struct lf_node **HP;
    struct hazlist *rlist;
    int threshold;
    int num_threads;
    struct hprectype **all_records;
    int num_hp;
};

struct hprectype *init_hprectype(int, int, struct hprectype **);
void retire_node(struct lf_node *, struct hprectype *);
void scan(struct hprectype *);

#endif
