// pqueue.h
// Areeba Kamal & Helena Kleinschmidt
// Taken from CPUscheduler/pqq/pqueue.h (Bach, Kleinschmidt, Zhumabekova)

#ifndef PQ_H
#define PQ_H
#include <stdio.h>
#include "event.h"

typedef struct NodePQ {
	Event *event;
	int priority;
	struct NodePQ *next;
} NodePQ;

typedef struct PQueue_STRUCT {
	struct NodePQ* HEAD;
	struct NodePQ* TAIL;
	int SIZE;
} PQueue_STRUCT;

PQueue_STRUCT* initPQ();
void enqueuePQ(PQueue_STRUCT* pq,  Event* event);
NodePQ* dequeuePQ( PQueue_STRUCT* pq);
NodePQ* getMin( PQueue_STRUCT* pq);
int getSizePQ( PQueue_STRUCT* pq);
void printPQ( PQueue_STRUCT* pq);

#endif
