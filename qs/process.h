// process.h
// Areeba Kamal
// Helena Kleinschmidt

#ifndef PROCESS_H
#define PROCESS_H
#include <stdlib.h>
#include <stdio.h>

typedef struct Process {
	/* characteristics */
	int id;
	int interarrivalTime; // average interarrival time 
	int avg_execTime; 	 // average execution time
	int actual_execTime; // actual execution time
	/* resource status */
	int* max_claims;
	int* curr_use;
	/* status */
	int executing; // says if a process is executing or not, init to 0
	/* statistics */
	int timeRunSoFar; // portion of  turnaround time when  process is running not idle
	int terminationEnqueued; 
	int creationTime;
	int start_firstPhase;
	int end_firstPhase; 
	int start_finalPhase; 
	int end_finalPhase;

} Process;

#endif
