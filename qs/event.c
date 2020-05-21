// event.c
// Helena Kleinschmidt
// Areeba Kamal

#include "event.h"

Event* createEvent(Process* proc, int timestamp, int type) {
	Event* ev = malloc(sizeof(Event));
	ev->proc = proc;
	ev->timestamp = timestamp;
	ev->type = type;
	return ev;
}
