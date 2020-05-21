// pqueue.c
// Areeba Kamal & Helena Kleinschmidt
// Taken from CPUscheduler/pqq/pqueue.c (Bach, Kleinschmidt, Zhumabekova)

#include <stdio.h>
#include "pqueue.h"

PQueue_STRUCT* initPQ(){
  PQueue_STRUCT* pq = (PQueue_STRUCT*)malloc(sizeof(PQueue_STRUCT));
  pq->HEAD = NULL;
  pq->TAIL = NULL;
  pq->SIZE = 0;
  return pq;
}
/* @param event is the reference to the event to be enqueued to the pq
 * @param priority is the priority of the priority queue node
 * Adds a priority queue node with a priority and an event to the PQ in increasing
  order of priority
 */
void enqueuePQ(PQueue_STRUCT* pq, Event *event){
  NodePQ* newNode = (NodePQ*)malloc(sizeof(NodePQ));
  newNode->event = event;
  newNode->priority = event->timestamp;
  newNode->next = NULL;

  // If priority queue is empty, point HEAD and TAIL to NewNode
  if (pq->SIZE == 0){
    pq->HEAD = newNode;
    pq->TAIL = newNode;
  }

  /* If priority queue is not empty, traverse the LL to find
    a node whose priority is greater than newNode's and set newNode's
    next to this node
  */
  else{
    NodePQ* currentNode = pq->HEAD;

    /* If the priority of the new node < the head's:
    *   - point the head to the new node
    *   - point new node's next to old head
    */
    if (newNode->priority < pq->HEAD->priority){
      pq->HEAD = newNode;
      newNode->next = currentNode;
    }

    /* If the priority of new node => the head's:
    *   - iterate through the queue until currentNode next node's priority
    is less than newNode's
    *   - set newNode's next to the currentNode's next
    *   - set currentNode's next to newNode
    */
    else{

      while (currentNode->next != NULL && currentNode->next->priority < newNode->priority){
        currentNode = currentNode->next;
      }

      /* If newNode's priority is the largest in PQ:
          - set currentNode's next to
          - set TAIL to newNode
      */
      if (currentNode->next == NULL){
        currentNode->next = newNode;
        pq->TAIL = newNode;
      }

      /* If newNode's priorty is somewhere in the middle of PQ:
          - set newNode's next to currentNode's next
          - set currentNode's next to newNode
      */
      else{
        newNode->next = currentNode->next;
        currentNode->next = newNode;
      }

    }
  }

  pq->SIZE++;
}

/*
* @param pq is the priority queue whose min will be returned but not extracted
* Returns a reference to the node with the smallest priority without removing it
*/
NodePQ* getMin(PQueue_STRUCT* pq){
  NodePQ* dequeued = NULL;

  // If the pq is not empty
  if (pq->SIZE != 0){
    dequeued = pq->HEAD;
    // printf("Min's event's timestamp: %d\n", dequeued->event->timestamp);
  }
  return dequeued;
}

/*
*  @param pq is the priority queue whose node with min priority you want to extract
*  Removes the node with the lowest priority
*  Returns a reference to the removed node
*/
NodePQ* dequeuePQ(PQueue_STRUCT* pq){
  NodePQ* dequeued = NULL;

  // If PQ is empty, print error
  if (pq->SIZE == 0){
    // printf("Nothing to extract\n");
    return dequeued;
  }
  else{
    dequeued = pq->HEAD;

    // If PQ only has 1 element, set HEAD and TAIL to NULL
    if (pq->SIZE == 1){
      pq->HEAD = NULL;
      pq->TAIL = NULL;
    }

    // If PQ has more than 1 element, set HEAD to HEAD's next
    else{
      pq->HEAD = pq->HEAD->next;
    }
    pq->SIZE--;
    // printf("Extracted min whose event timestamp: %d\n", dequeued->event->timestamp);
    return dequeued;
  }
}

// Returns the number of priority queue nodes in the priority queue
int getSizePQ(PQueue_STRUCT* pq){
  // printf("SIZE = %d\n", pq->SIZE);
  return pq->SIZE;
}

// Prints out the priority queue nodes
void printPQ(PQueue_STRUCT* pq){
  NodePQ* node = pq->HEAD;

  while (node != NULL){
    if (node->next != NULL)
      printf("             [P: %d][t: %d](%d)->\n", node->event->proc->id, node->event->timestamp, node->event->type);
    else
      printf("             [P: %d][t: %d](%d)", node->event->proc->id, node->event->timestamp, node->event->type);
    node = node->next;
  }
  printf("\n");
}
