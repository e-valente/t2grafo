/*
 * strong_connected.c
 *
 *  Created on: Apr 14, 2013
 *      Author: emanuel
 */
#include <stdlib.h>
#include <stdio.h>
#include "grafo.h"
#include "dfs.h"
#include "tree.h"
#include "strong_connected.h"



extern tree_vector_t *tree_result;
order_access_black_t *order_black;
dfs_predec_t *dfs_predec;

tree_vector_t* calculateStrongConnected(GRAFO *grafo)
{
	GRAFO *mygraph;

	tree_t *my_tree;

	int i, j, nelem, flag;
	int total_trees;

	mygraph = calculateInverseGraph(grafo);


	nelem = grafo->count;


	/****configura vetor de acesso aos pretos***/
	order_black = (order_access_black_t*)malloc(sizeof(order_access_black_t));
	order_black->total = 0;
	order_black->value = (int*)malloc(sizeof(int) * nelem);
	/*********************************************/


	dfs_init(grafo, grafo[0].vertex, 0, 1);

	for(i = 0; i < grafo->total; i++)
	{

		if(grafo[i].color == WHITE)
		{
			//if(i > 0)dfs_close();
			dfs_init(grafo, grafo[i].vertex, 1, 1);

		}
	}


	//exit(1);
	/*imprime tempo*/

	/*
	printf("ordem do tempo: \n\n");
	for(i = 0; i < order_black->total; i++)
	{
		printf(" %d",order_black->value[i]);
	}
	printf("\n\n");
	*/



	dfs_close();





	flag = 0;
	total_trees = 0;

	for(i = order_black->total -1; i >= 0 ; i--)
	{
		//printf("executando para vertice: %d cor dele %d\n", mygraph[order_black->value[i]].vertex, mygraph[order_black->value[i]].color);

		if(mygraph[order_black->value[i]].color == WHITE)
		{
			total_trees++;

			if(flag == 0){//na primeira vez que faz dfs() aloca a memoria
				dfs_init(mygraph, mygraph[order_black->value[i]].vertex, 0, 0);
				flag = 1;
			}
			else dfs_init(mygraph, mygraph[order_black->value[i]].vertex, 1, 0);


			//adiciona cada arvore em um vetor separado
			//copia vetor de predecessores para uma estrtura chamada tree
			my_tree = createTree(dfs_predec->total);

			my_tree->total_elem = dfs_predec->total;
			for(j = 0; j < dfs_predec->total; j++)
			{
				my_tree->values[j][0] = dfs_predec->index[j][0];
				my_tree->values[j][1] = dfs_predec->index[j][1];


			}

			insertTreeAtVector(&tree_result, my_tree);


			destroyTree(my_tree);

		}


	}



	//valida as arvores
	//descartas as que tem só nó raiz
	validateVectorTree(tree_result);


	destroyGraph(mygraph);
	dfs_close();


	free(order_black->value);
	free(order_black);
	return NULL;
}


GRAFO* calculateInverseGraph(GRAFO *grafo)
{
	GRAFO *mygraph;
	int total_vertexes;
	int src_vertex;
	int i, j;

	mygraph = NULL;

	total_vertexes = grafo->count;

	mygraph = createGraph(total_vertexes);


	//creates vertexes
	for(i = 0; i < total_vertexes; i++)
	{
		insertVertexAtGraph(mygraph, grafo[i].vertex);
		grafo[i].color = WHITE;

	}

	//creates edges
	for(i = 0; i < total_vertexes; i++)
	{
		j = 0;

		while(next_adjacent_vertex(grafo, i, j) != -1){
			src_vertex = next_adjacent_vertex(grafo, i, j);

			if(src_vertex != -1)
				insertEdgeAtGraph(mygraph, src_vertex, mygraph[i].vertex, 1);

			j++;

		}



	}

	//printAll(mygraph);

	return mygraph;




}





