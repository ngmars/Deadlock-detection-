// distribution.c
// Helena Kleinschmidt
// Areeba Kamal
// Adapted from Ashley DeFlumere

#include <stdio.h>
#include <time.h>
#include <stdlib.h> /* Needed for both */
#include <math.h> /* Needed for exponential */

int uniform_rand(int min, int max) {
	double r = rand()/(1.0 + RAND_MAX);
	int range = max - min + 1;
	return (r * range) + min;
}

int exponential_rand(int mean, int lower_bound){
	double r = rand()/(1.0 + RAND_MAX);
	return -mean*log(r) + 1 >= lower_bound ? -mean*log(r) + 1 : exponential_rand(mean, lower_bound);
}