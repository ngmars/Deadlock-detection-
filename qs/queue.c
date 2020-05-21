// queue.c
// Areeba Kamal & Helena Kleinschmidt
// Taken from CPUscheduler/pqq/queue.c (Bach, Kleinschmidt, Zhumabekova)

#include "queue.h"

Queue_STRUCT* initQ(){
  Queue_STRUCT* q = (Queue_STRUCT*)malloc(sizeof(Queue_STRUCT));
  q->HEAD = NULL;
  q->TAIL = NULL;
  q->SIZE = 0;
  return q;
}

// @param process is a reference to a process to be enqueued into q
// Adds a process to the end of the Queue_STRUCT_STRUCT q
void enqueueQ(Queue_STRUCT* q, Process* process){
  Node* newNode = (Node*)malloc(sizeof(Node));
  newNode->process = process;
  newNode->next = NULL;
  // If Queue_STRUCT is empty, point HEAD and TAIL to NewNode
  if (q->SIZE == 0){
    q->HEAD = newNode;
    q->TAIL = newNode;
  }

  /* If Queue_STRUCT is not empty, add newNode to the end by setting
  * current TAIL's next to the newNode and point TAIL to newNode
  */
  else{
    q->TAIL->next = newNode;
    q->TAIL = newNode;
  }
  q->SIZE++;
}

// Removes an element from the HEAD of the Queue_STRUCT
// Returns the deQueue_STRUCTd integer
Node* dequeueQ(Queue_STRUCT* q){
  Node* dequeued = NULL;

  // If the queue is empty, print "Nothing to dequeue"
  if (q->SIZE == 0){
    // printf("Nothing to dequeue\n");
    return dequeued;
  }
  // If queue is not empty, point HEAD to current HEAD's next
  else{
    dequeued = q->HEAD;
    q->HEAD = q->HEAD->next;
    q->SIZE--;
    return dequeued;
  }

}

// Returns the element at the HEAD of the queue
Node* peekQ(Queue_STRUCT* q){
  return q->HEAD;
}

// Returns the SIZE of the queue
int getSizeQ(Queue_STRUCT* q){
  // printf("Size = %d\n", q->SIZE);
  return q->SIZE;
}

// Prints all processes
void printQ(Queue_STRUCT* q){
  Node* current = q->HEAD;
  while (current != NULL){
    if (current->next != NULL)
      printf("%d ->", current->process->id);
    else
      printf("%d", current->process->id);
    current = current->next;
  }
  printf("\n");
}
