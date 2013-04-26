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


//topological_sort_t *my_topological_sort;

int main()
{
	//graph vars
	GRAFO *grafo;
	int total_vertexes, total_edges;
	int vertex_src, vertex_dst, i;
	//resultado
	tree_vector_t *my_trees;




	grafo = NULL;
	my_trees = NULL;



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




	printAll(grafo);
	calculateStrongConnected(grafo);

	//dfs_init(grafo, grafo[0].vertex);

	//printVertexes(grafo);

	/*
	for(i = 1; i < total_vertexes; i++)
	{
		if(grafo[i].color == WHITE)
			dfs_init(grafo, grafo[i].vertex);

	}

*/




	if(my_trees != NULL)destroyVector(my_trees);
	destroyGraph(grafo);


	return 0;
}

