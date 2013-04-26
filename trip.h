/*
 * trip.h
 *
 *  Created on: Apr 4, 2013
 *      Author: emanuel
 */

#ifndef TRIP_H_
#define TRIP_H_

#include "grafo.h"

//actions constants
#define BACK 0
#define SHORTCUT 1
#define CROSS 2

typedef struct _trip_t
{
	int total;
	int *visited_cities;

}trip_t;

trip_t* init_trip(void);
void end_trip(trip_t*); //free() at vector of cities
void insert_city_on_trip(trip_t*, int);
void print_trip(trip_t*);
int next_city(GRAFO*, int, int, int*, int*);

#endif /* TRIP_H_ */
