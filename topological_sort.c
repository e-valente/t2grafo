/*
 * topological_sort.c
 *
 *  Created on: Apr 14, 2013
 *      Author: emanuel
 */

#include <stdlib.h>
#include <stdio.h>
#include "grafo.h"
#include "dfs.h"
#include "topological_sort.h"

topological_sort_t *my_topological_sort;

void insert_topological_sort(int value)
{
	int index;


	index = my_topological_sort->total++;

	my_topological_sort->value = (int*)
			realloc(my_topological_sort->value, sizeof(int) * (index+1));
	my_topological_sort->value[index] = value;

}

void print_topological_sort()
{
	int i;

	printf("Ordenacao Toológica: \n");
	for(i = my_topological_sort->total -1; i >= 0; i--)
	{
		printf("%d ", my_topological_sort->value[i]);
	}

	printf("\n\n");
}


