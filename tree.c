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

int validateTree(tree_t *my_tree)
{
	int i, total_elem;
	int count;

	total_elem = my_tree->total_elem;
	count = 0;

	for(i = 0; i< total_elem; i++)
	{
		if(my_tree->values[i][1] == -1)count++;

	}

	if(count < total_elem -1){

		my_tree->is_ok = 1;
		return 1; //arvore valida
	}


	my_tree->is_ok = 0;
	return 0;  //arvore invalida
}



void validateVectorTree(tree_vector_t *my_vector_tree)
{
	int i, total_elem;

	my_vector_tree->total_validated_trees = 0;
	total_elem = my_vector_tree->total_trees;

	for(i = 0; i< total_elem; i++)
	{
		if(validateTree(&my_vector_tree->tree[i]) == 1)
			my_vector_tree->total_validated_trees++;



	}
}

int executeCompression(GRAFO *grafo, tree_vector_t *tree_result)
{
	int i, j, k, total_vertexes, total_trees, total_elem;
	int count_vertexes_not_compacted;

	total_vertexes = grafo->total;
	total_trees = tree_result->total_trees;


	//para cada arvore
	for(i = 0; i < total_trees; i++)
	{
		total_elem = tree_result->tree[i].total_elem;

		//se a arvore for valida
		if(tree_result->tree[i].is_ok == 1){

			//para cada elemento da arvore
			for(j = 0; j < total_elem; j++)
			{
				//para cada vertice do grafo original
				for(k = 0; k < total_vertexes; k++)
				{
					//printf("comaprando: %d com %d\n", grafo[k].vertex,tree_result->tree[i].values[j][0] );
					if(grafo[k].vertex == tree_result->tree[i].values[j][0] &&
							tree_result->tree[i].values[j][1] != -1)grafo[k].is_compacted = 1;


				}



			}

		}



	}


	//conta os vertices nao compactados e retorna
	count_vertexes_not_compacted = 0;

	for(k = 0; k < total_vertexes; k++)
	{
		if(grafo[k].is_compacted == 0) count_vertexes_not_compacted++;


	}


	return count_vertexes_not_compacted;





}
