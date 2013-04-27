/*
 * tree.c
 *
 *  Created on: Apr 14, 2013
 *      Author: emanuel
 */

#include <stdlib.h>
#include <stdio.h>
#include "grafo.h"
#include "tree.h"


void insertTreeAtVector(tree_vector_t **my_vector, tree_t *my_tree)
{
	int index, i;
	//int i, total_elem;

	index = (*my_vector)->total_trees++;



	//*my_vector = (tree_vector_t*)realloc(*my_vector, sizeof(tree_vector_t) * (index +1));

	//aloca mais um arvore no vetor de arvores
	(*my_vector)->tree = (tree_t*)realloc((*my_vector)->tree, sizeof(tree_t) * (index + 1));

	//aloca espaco para arvore atual
	(*my_vector)->tree[index].values = (int**)malloc(sizeof(int*) * my_tree->total_elem);



	//printf("IMprime nova arvore: \n\n");

	(*my_vector)->tree[index].total_elem = my_tree->total_elem;

	for(i = 0; i < my_tree->total_elem; i++)
	{
		(*my_vector)->tree[index].values[i] = (int*)malloc(sizeof(int) * 2);

		(*my_vector)->tree[index].values[i][0] = my_tree->values[i][0];
		(*my_vector)->tree[index].values[i][1] = my_tree->values[i][1];

	}


}
tree_t* createTree(int nelem)
{
	tree_t *my_tree;
	int i;

	my_tree = (tree_t*)malloc(sizeof(tree_t));
	my_tree->total_elem = nelem;

	my_tree->values = NULL;

	//numero de elementos na arvore
	my_tree->values = (int**)realloc(my_tree->values, sizeof(int*) * nelem);

	//aloca pai e filho
	for(i = 0; i < nelem; i++)
	{
		my_tree->values[i] = (int*)malloc(sizeof(int) * 2);

	}

	return my_tree;
}

tree_vector_t* createTreeVector()
{
	tree_vector_t *my_vector_tree;

	my_vector_tree = (tree_vector_t*)malloc(sizeof(tree_vector_t));
	my_vector_tree->total_trees = 0;


	return my_vector_tree;
}

void destroyTree(tree_t *my_tree)
{
	int i, total;

	total = my_tree->total_elem;


	for(i = 0; i < total; i++)
	{
		free(my_tree->values[i]);

	}

	free(my_tree->values);
	free(my_tree);

}

void destroyVector(tree_vector_t *my_tree_vector)
{
	int i, j, total_tree;
	int total_element;

	total_element = 1;

	total_tree = my_tree_vector->total_trees;

	for(i = 0; i < total_tree; i++)
	{
		total_element = my_tree_vector->tree[i].total_elem;

		//free em cada elemento da arvore atual
		for(j = 0; j < total_element; j++)
		{
			free(my_tree_vector->tree[i].values[j]);

		}


		//free no ponteiro da arvore atual
		free(my_tree_vector->tree[i].values);


	}

	free(my_tree_vector->tree);
	free(my_tree_vector);

}
