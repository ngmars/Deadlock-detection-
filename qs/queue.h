// queue.h
// Areeba Kamal & Helena Kleinschmidt
// Taken from CPUscheduler/pqq/queue.h (Bach, Kleinschmidt, Zhumabekova)

#ifndef Q_H
#define Q_H
#include <stdio.h>
#include <stdlib.h>
#include "process.h"

typedef struct Node {
	struct Process *process;
	struct Node *next;
} Node;

typedef struct Queue_STRUCT {
	struct Node* HEAD;
	struct Node* TAIL;
	int SIZE;
} Queue_STRUCT;

Queue_STRUCT* initQ();
void enqueueQ(Queue_STRUCT* q, Process* process);
Node* dequeueQ(Queue_STRUCT* q);
Node* peekQ(Queue_STRUCT* q);
int getSizeQ(Queue_STRUCT* q);
void printQ(Queue_STRUCT* q);

#endif
