#include <stdlib.h>
#include <stdio.h>
#include <pthread.h>
#include "lf_queue.h"

struct lf_queue *q;
struct hprectype *records[2];

void *list_test(void *p){
    struct hprectype *record;
    int thread, i;
    thread = *(int *)p;
    record = records[thread];

    for(i = 0; i < 5; ++i){
        lf_enqueue(q, &i, record);
    }
    for(i = 0; i < 5; ++i){
        lf_dequeue(q, record);
    }

    return NULL;
}

void main(int argc, char **argv){
    int i, j;
    pthread_t thread0;
    pthread_t thread1;
    
    q = lf_queue_init();
    
    i = 0;
    j = 1;

    records[0] = init_hprectype(2, 2, records);
    records[1] = init_hprectype(2, 2, records);

    if(pthread_create(&thread0, NULL, list_test, &i)){
        printf("error creating thread");
        return;
    }

    if(pthread_create(&thread1, NULL, list_test, &j)){
        printf("error creating thread");
        return;
    }

    if(pthread_join(thread0, NULL)){
        printf("error joining thread");
        return;
    }
    if(pthread_join(thread1, NULL)){
        printf("error joining thread");
        return;
    }

    return;
}
