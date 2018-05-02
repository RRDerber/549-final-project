#include <stdlib.h>
#include "hprecord.h"
#include "lf_node.h"
#include "hazlist.h"
#include "lf_utils.h"

#define THRESH_MULT 5

struct hprectype *init_hprectype(int num_hp, int num_threads, struct hprectype **records_array){
    struct hprectype *record;
    record = lf_malloc(sizeof(struct hprectype));
    record->HP = lf_malloc(sizeof(struct lf_node *) * num_hp);
    record->rlist = init_hazlist();
    record->threshold = num_threads * 5;
    record->num_threads = num_threads;
    record->all_records = records_array;
}

void retire_node(struct lf_node *node, struct hprectype *record){
    int rlist_size;
    rlist_size = hazlist_push(record->rlist, node);
    if(rlist_size == record->threshold){
        scan(record);
    }
}

void scan(struct hprectype *record){
    int i, j, k, free;
    struct lf_node **temp;
    struct lf_node *node;
    struct lf_node **hazards;
    temp = lf_malloc(sizeof(struct lf_node *) * record->rlist->size);

    for(i = 0; i < record->rlist->size; ++i){
        temp[i] = hazlist_pop(record->rlist);
    }
    
    for(k = 0; k < record->rlist->size; ++k){
        free = 1;
        node = temp[k];
        for(i = 0; i < record->num_threads; ++i){
            for(j = 0; j < record->num_hp; ++j){
                if(record->all_records[i]->HP[j] == node)
                    free = 0;
            }
        }
        if(free)
            lf_free(node);
        else
            hazlist_push(record->rlist, node);
    }
}
