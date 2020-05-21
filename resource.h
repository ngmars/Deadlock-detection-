// resource.h
// Areeba Kamal
// Helena Kleinschmidt

#ifndef RESOURCE_H
#define RESOURCE_H
#include "qs/queue.h"

typedef struct Resource {
	int type;	
	int total_inst;
	int available;
	Queue_STRUCT* request_q; // processes waiting to acquire the resource
} Resource;

#endif
 