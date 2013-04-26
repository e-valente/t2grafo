/*
 * topological_sort.h
 *
 *  Created on: Apr 14, 2013
 *      Author: emanuel
 */

#ifndef TOPOLOGICAL_SORT_H_
#define TOPOLOGICAL_SORT_H_

typedef struct _topological_sort_t
{
	int total;
	int *value;

}topological_sort_t;

extern topological_sort_t *my_topological_sort;

void insert_topological_sort(int);
void print_topological_sort();

#endif /* TOPOLOGICAL_SORT_H_ */
