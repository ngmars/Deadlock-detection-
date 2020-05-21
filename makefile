all: sim

sim: sim.c bankers_algorithm.c qs/pqueue.c qs/event.c qs/queue.c simStats.c
	gcc -o sim bankers_algorithm.c sim.c qs/pqueue.c qs/event.c qs/queue.c simStats.c -I.
