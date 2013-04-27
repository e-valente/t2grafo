/*
 * main.c
 *
 *  Created on: Mar 19, 2013
 *      Author: emanuel
 */

#include <stdlib.h>
#include <stdio.h>
#include "grafo.h"
#include "dfs.h"
#include "tree.h"
//#include "topological_sort.h"
#include "strong_connected.h"


tree_vector_t *tree_result;

int main()
{
	//graph vars
	GRAFO *grafo;
	int total_vertexes, total_edges;
	int vertex_src, vertex_dst, i;
	int vertexes_not_compacteded;


	grafo = NULL;



	//reads total vertexes
	scanf("%d", &total_vertexes);
	//reads total edges
	scanf("%d", &total_edges);

	grafo = createGraph(total_vertexes);



	//creates vertexes
	for(i = 0; i < total_vertexes; i++)
	{
		insertVertexAtGraph(grafo, i);

	}


	//creates edges
	for(i = 0; i < total_edges; i++)
	{
		scanf("%d %d", &vertex_src, &vertex_dst);
		insertEdgeAtGraph(grafo, vertex_src, vertex_dst, 1);


	}


	/********inicia o vetor de arvores resultantes**************/
	tree_result = NULL;
	tree_result = (tree_vector_t*)malloc(sizeof(tree_vector_t));
	tree_result->tree = NULL;
	tree_result->total_trees = 0;

	//obtem as arvores que contem
	//os componentes fortemente conectdos
	calculateStrongConnected(grafo);

	vertexes_not_compacteded = executeCompression(grafo, tree_result);

	//imprime vertices nao compactados + arvores validas (vertices compactados)
	printf("%d\n",vertexes_not_compacteded + tree_result->total_validated_trees);




	destroyGraph(grafo);
	destroyVector(tree_result);


	return 0;
}

