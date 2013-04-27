/*
 * dfs.c
 *
 *  Created on: Apr 3, 2013
 *      Author: emanuel
 */

#include <stdlib.h>
#include <stdio.h>

#include "grafo.h"
#include "dfs.h"
//#include "topological_sort.h"


extern dfs_result_t *dfs_result = NULL;
extern dfs_predec_t *dfs_predec = NULL;
extern order_access_black_t *order_black;

void dfs_init(GRAFO *grafo, int first_vertex, int time, int go_count)
{

	int nelem;
	int i;

	nelem = grafo->count;

	if(time == 0) {
		dfs_result = (dfs_result_t*)malloc(sizeof(dfs_result_t));
		dfs_predec = (dfs_predec_t*)malloc(sizeof(dfs_predec_t));

		dfs_result->index = (int*)malloc(sizeof(int) * nelem);
		dfs_predec->index = (int**)malloc(sizeof(int*) * nelem);
		for(i = 0; i < nelem; i++)
		{
			dfs_predec->index[i] = (int*)malloc(sizeof(int) * 2);

		}

		dfs_predec->total = nelem;

		dfs_result->count = 0;
		dfs_result->total = nelem;

		for(i = 0 ; i < nelem; i++)
		{
			dfs_predec->index[i][0] = grafo[i].vertex;
			dfs_predec->index[i][1] = -1;
			//grafo[i].color = WHITE;

			if(grafo[i].vertex == first_vertex)
				dfs_predec->index[i][1] = -2;

			//como todos vertices estao brancos
			//setamos todas areas como arestas da arvore
			set_tree_edge(grafo, i);

		}



	}


	//seta o vetor de predecessores
	//pinta os vertices de branco
	for(i = 0 ; i < nelem; i++)
	{
		dfs_predec->index[i][0] = grafo[i].vertex;
		dfs_predec->index[i][1] = -1;
		//grafo[i].color = WHITE;

		if(grafo[i].vertex == first_vertex)
			dfs_predec->index[i][1] = -2;

		//como todos vertices estao brancos
		//setamos todas areas como arestas da arvore
		set_tree_edge(grafo, i);

	}


	dfs(grafo, first_vertex, go_count);


	//imprime resultado



	/*
	printf("resultado DFS:\n");
	for(i = 0; i < nelem; i++)
	{
		printf(" %d ", dfs_result->index[i]);

	}


	 */


	printf("\n\nresultado predecessores:\n");
	for(i = 0; i < nelem; i++)
	{
		printf(" predecessor de %d é %d\n", dfs_predec->index[i][0], dfs_predec->index[i][1]);

	}


}

void dfs(GRAFO *grafo, int index, int go_count)
{
	int i, index_new_vertex;
	int index_test_color;

	grafo[index].color = GRAY;
	insert_at_result_queue(grafo[index].vertex);
	i = 0;

	do{
		index_new_vertex = index_next_minor_adjacent_by_order(grafo, index, i);

		//testar se já esta pintado
		index_test_color = index_from_vertex(grafo, index_new_vertex);
		if(index_test_color >=0)
			if(grafo[index_test_color].color != WHITE) {index_new_vertex = -2;
			//printf("NAO EH WHITE -> vertice %d\n", grafo[index_test_color].vertex);
			}
		//if(index_new_vertex <= grafo[index].vertex && index_new_vertex != -1) index_new_vertex = -2;

		if(index_new_vertex >= 0 )
		{
			if(grafo[index_new_vertex].color == WHITE) {
				grafo[index_new_vertex].color = GRAY;

				dfs_predec->index[index_new_vertex][1] = grafo[index].vertex;
				dfs(grafo, index_new_vertex, go_count);
			} else {
				if(grafo[index_new_vertex].color == GRAY) {
					//se vertice é cinza setamos se existir uma aresta que
					//volta para aquele vertice como de retorno
					if(has_edge_from_vertexes(grafo, grafo[index].vertex, grafo[index_new_vertex].vertex)){
						set_return_edge(grafo,grafo[index].vertex, grafo[index_new_vertex].vertex);
					}
					//fim da classificao da aresta de retorno

				}
			}

			//nao faz parte do dfs
			//apenas classificaremos se aresta é de
			//travessia ou avanco
			if(grafo[index_new_vertex].color == BLACK) {
				if(vertex_comes_before_or_after_on_dfs(grafo[index].vertex,
						grafo[index_new_vertex].vertex) == 2) {
					//aresta de avanco
					set_forward_edge(grafo, index, grafo[index_new_vertex].vertex);
				} else {  //senao a aresta é de travessia
					if(vertex_comes_before_or_after_on_dfs(grafo[index].vertex,
							grafo[index_new_vertex].vertex) == 0) {
						set_cross_edge(grafo, index, grafo[index_new_vertex].vertex);
					}


				}
			}


		}



		i++;


	}while(index_new_vertex != -1);

	grafo[index].color = BLACK;
	//seta a ordem de acesso dos pretos (usado em outros algoritmos
	if(go_count == 1)order_black->value[order_black->total++] = index;

	/*******ordenacao topologica*****/
	//printf("insrindo: %d\n",grafo[index].vertex );
	//insert_topological_sort(grafo[index].vertex);
	//printf("ordenacao topológica: %d\n", grafo[index].vertex);
	/***fim da ordenacao topologica******/




}

int insert_at_result_queue(int vertex)
{
	if(dfs_result->total == dfs_result->count)return -1;
	else {
		dfs_result->index[dfs_result->count++] = vertex;
		return 0;
	}
}


void dfs_close()
{
	int i, nelem;

	nelem = dfs_predec->total;

	if(dfs_result->index != NULL){
		free(dfs_result->index);
		free(dfs_result);
	}


	if(dfs_predec->index != NULL){
		for(i = 0; i < nelem; i++)free(dfs_predec->index[i]);
		free(dfs_predec->index);
		free(dfs_predec);
	}

}
//retorna 2 se src vem antes e nao sao vizinhos
//retorna 1 se src ven antes de sao vizinhos
//retorna 0 se dst vem antes e nao sao vizinhos
//retorna -1 se dst vem antes e sao vizinhos
int vertex_comes_before_or_after_on_dfs(int vertex_src, int vertex_dst)
{
	int i;
	int src_idx, dst_idx;

	src_idx = -1;
	dst_idx = -1;


	for(i = 0; i < dfs_result->total; i++)
	{
		if(dfs_result->index[i] == vertex_src)src_idx = i;
		if(dfs_result->index[i] == vertex_dst)dst_idx = i;

	}

	//src vem antes
	if((dst_idx - src_idx) > 1)return 2;
	if((dst_idx - src_idx) == 1)return 1;
	if((src_idx - dst_idx) > 1)return 0;
	if((src_idx - dst_idx) == 1)return -1;

	return -2;

}


