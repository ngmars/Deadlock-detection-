// bankers_algorithm.c
// Helena Kleinschmidt
// Areeba Kamal

#include <stdio.h>
#include <stdlib.h>
#include "bankers_algorithm.h"
#define defaultPrc 3
#define defaultRes 3

int ** maxClaims; 		// index[i][j] holds max number of instances of resource j that process i can lay claim to  
int ** currUse;			// index[i][j] holds number of instances of resource j that process i currently holds 
int * available; 		// index i holds number of instances of resource i available and currently not in use
int * unexecuted; 		// index i says whether process i has been executed yet or not
int * safeState;  		// holds safe sequence

int numPrc = defaultPrc; // number of processes available
int numRes = defaultRes; // number of resources available

/**
* Runs test files
*
int main() {

	test(); 
	test2();
	return 0;
}*/

/**
* Sets numPrc and numRes, mallocs memory for arrays, calls method to initialize them
*/ 
int setNumPrcRes(int setPrc, int setRes) {
	
	numPrc = setPrc; 
	numRes = setRes;
	int i, j, k, l;

	maxClaims = (int**) malloc ( numPrc * sizeof(int *)); 
	for(i = 0; i < numPrc; i++)
		maxClaims[i] = (int*)malloc(numRes * sizeof(int));

	currUse = (int**) malloc ( numPrc * sizeof(int *)); 
	for(j = 0; j < numPrc; j++)
		currUse[j] = (int*)malloc(numRes * sizeof(int));

	available = (int*) malloc(numRes * sizeof(int));
	unexecuted = (int*) malloc(numPrc * sizeof(int));
	safeState = (int*) malloc(numPrc * sizeof(int));

	initArrays();
	return 0;
}

/**
* Initializes arrays
*/
void initArrays() {

	int i, j, k, l, m; // initialize maxclaims and curr use to zero
	for(i = 0; i < numPrc; i++) {
		for(j = 0; j < numRes; j++) {
			maxClaims[i][j] = 0; 
			currUse[i][j] = 0; 
		}
	}
	for(k = 0; k < numRes; k++) {
		available[k] = 0; 
	}

	for(l = 0; l < numPrc; l++) {
		unexecuted[l] = 1; 
	}

	for(m = 0; m < numPrc; m++) {
		safeState[m] = -1; 
	}
}

/**
* Find safe seq - test 1
*/
void test() {

	// START BY CALLING THIS METHOD ALWAYS
	setNumPrcRes(defaultPrc, defaultRes);
	printf("\n\n Starting test 1:\n");
	int mc1[] = {10, 7, 5};
	int mc2[] = {0, 6, 5}; 
	int mc3[] = {0, 6, 5}; 

	setMaxClaims(0, mc1);
	setMaxClaims(1, mc2);
	setMaxClaims(2, mc3);

	int cu1[] = {1, 0, 0};
	int cu2[] = {0, 6, 3}; 
	int cu3[] = {0, 0, 1}; 

	setCurrUse(0, cu1);
	setCurrUse(1, cu2); 
	setCurrUse(2, cu3);

	int avb[] = {1, 5, 2};

	setAvailable(avb);

	//readMaxClaims(); 
	//readCurrUse(); 
	//readAvailable(); 
	runprocesses();
	return;
}

/**
* Find safe seq - test 2
*/
void test2() {

	setNumPrcRes(defaultPrc, defaultRes);
	printf("\n\n Starting test 2:\n");

	int mc1[] = {5, 6, 7};
	int mc2[] = {3, 4, 5}; 
	int mc3[] = {0, 6, 5}; 

	setMaxClaims(0, mc1);
	setMaxClaims(1, mc2);
	setMaxClaims(2, mc3);

	int cu1[] = {1, 0, 0};
	int cu2[] = {0, 0, 0}; 
	int cu3[] = {4, 5, 6}; 

	setCurrUse(0, cu1);
	setCurrUse(1, cu2); 
	setCurrUse(2, cu3);

	int avb[] = {1, 1, 1};

	setAvailable(avb);

	//readMaxClaims(); 
	//readCurrUse(); 
	//readAvailable(); 
	runprocesses();
	return;
}

/**
* Setter method for max claims for a given process with ID pID
*/
void setMaxClaims(int pID, int maxR[]) {

	int i;
	for(i = 0; i < numRes; i++)
		maxClaims[pID][i] = maxR[i];
	return; 
}

/**
* Setter method for currUse for a given process with ID pID
*/
void setCurrUse(int pID, int maxU[]) {

	int i;
	for(i = 0; i < numRes; i++)
		currUse[pID][i] = maxU[i];
	return; 
}


/**
* Setter method for number of available units of each resource
*/
void setAvailable(int avb[]) {

	int i;
	for(i = 0; i < numRes; i++)
		available[i] = avb[i];
	return; 
}

/**
* Print max claims array
*/ 
void readMaxClaims() {

	int i;
	int j;
	for(i = 0; i < numPrc; i++)
		for(j = 0; j < numRes; j++)
			printf("For process %d, maxClaims to resource %d are %d\n", i, j, maxClaims[i][j]);
}

/**
* Print current use array
*/ 
void readCurrUse() {

	int i; 
	int j; 
	for(i = 0; i < numPrc; i++)
		for(j = 0; j < numRes; j++)
			printf("For process %d, current use of resource %d are %d\n", i, j, currUse[i][j]);
}

/**
* Print available array
*/ 
void readAvailable() {

	int j;
	for(j = 0; j < numRes; j++)
		printf("For resource %d, number of available units are %d\n", j, available[j]);
}

/**
* Execute bankers algorithm and find a safe sequence
*/ 
int runprocesses() {

	int runningAProcess = 1; 
	int safe = 0;
	int processesLeft = numPrc;
	while(processesLeft != 0) { // while all processes have not had their turn
		safe = 0; // anticipate unsafe state, walk through executed processes, looking for a process to run next
		int p, r;
		for(p = 0; p < numPrc; p++) {// this loop will run as long as we don't execute all our processes
			// printf("Processes being executed is %d\n", p);

			if(unexecuted[p]) { 			// if this process has not been run yet
				runningAProcess = 1; 
				for(r = 0; r < numRes; r++) { // check if it is safe to run
					if(maxClaims[p][r] - currUse[p][r] > available[r]) {
						printf("Insufficient instances of resource %d for process %d\n", r, p);
						runningAProcess = 0; 
						break; // process not safe to run, break and move to next process
					} 
				}
				if(runningAProcess) {
					unexecuted[p] = 0; // if it is safe to run, execute it
					safe = 1; // safe process search in process
					// printf("Executing process with pID %d\n", p);
					safeState[numPrc - processesLeft] = p; 
					processesLeft--; 
					int i; 
					for(i = 0; i < numRes; i++) {// increment available resources
						available[i] = available[i] + currUse[p][i];
						currUse[p][i] = 0; 
					}
					break; // process safely run, break and move to next process
				} 
			}
		}

		if(safe) {
			printf("Safe state found\n");
			//printSafeSeq(); 
		} else {
			printf("Safe state not found\n");
			break;
		}
	}

	return safe;
}

/**
* Print safe sequence if one is found
*/
void printSafeSeq() {
	printf("Safe sequence found!\nSafe sequence is:\n");
		int i;
		for(i = 0; i < numPrc; i++)
			printf("%d\n", safeState[i]);
		return;
}
