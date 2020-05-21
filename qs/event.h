// event.h
// Areeba Kamal
// Helena Kleinschmidt

#ifndef EVENT_H
#define EVENT_H
#include "process.h"
#include "resource.h"

typedef struct Event {
	Process* proc;
	int timestamp;
	int type; // can be 0 (indicates event to create process)
		  // 	 or 1 (indicates event that terminate process)
		  // 	 or 2 (indicates event that kills process prematurely)
		  //	 or 3 (indicates event that will let process request resource)
		  // 	 or 4 (indicates event that will let process release resource)
} Event;

Event* createEvent(Process* proc, int timestamp, int type);

#endif
