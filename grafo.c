/*
 * grafo.c
 *
 *  Created on: Mar 19, 2013
 *      Author: emanuel
 */
#include <stdlib.h>
#include <stdio.h>
#include "grafo.h"
#include "dfs.h"

GRAFO* createGraph(int total_vertex)
{
	GRAFO *grafo;
	int i;
	//aloca numero de vertices no vetor
	grafo = (GRAFO*)malloc(sizeof(GRAFO) * total_vertex);

	grafo->count = 0;
	grafo->edges = 0;
	grafo->total = total_vertex;

	//inicia as listas de cada vertice
	for(i =0; i< total_vertex; i++){
		create(&grafo[i].list);
	}
	return grafo;
}

void insertVertexAtGraph(GRAFO *grafo, int vertex)
{
	int index;

	index = grafo->count;

	grafo[index].vertex = vertex;
	grafo->count++;


}

int insertEdgeAtGraph(GRAFO *grafo, int src_vertex , int dst_vertex, int weight)
{
	//fazer verificacao se existem eses vertices
	ITEM item;
	int i;

	int flag_exists_vertex_src = 0;
	int flag_exists_vertex_dst = 0;

	int index;

	for(i = 0; i < grafo->count; i++)
	{
		if(src_vertex == grafo[i].vertex)
		{
			flag_exists_vertex_src = 1;
			index = i; //vertice que receberá a lista
		}

		if(dst_vertex == grafo[i].vertex)
		{
			flag_exists_vertex_dst = 1;
		}

	}

	if(flag_exists_vertex_src == 0){
		printf("O vertice %d não existe!\n", src_vertex);
		return -1;
	}

	if(flag_exists_vertex_dst == 0){
		printf("O vertice %d não existe!\n", dst_vertex);
		return -1;
	}

	//insere realmente no grafo

	item.vertex = dst_vertex;
	item.weight = weight;
	item.type_edge = ORDINARY_EDGE;

	insert(grafo[index].list, &item);
	grafo->edges++;

	return 0;

}
void printVertexes(GRAFO *grafo)
{
	int i;
	int total = grafo->count;

	printf("\nVertexes: \n");

	for(i = 0; i < total; i++)
	{
		printf("Vertex: %d Color: %d\n", grafo[i].vertex, grafo[i].color);

	}
}

void destroyGraph(GRAFO *grafo)
{
	int total_vertexes = grafo->total;
	int i;

	//destrói (free()) as listas
	for(i = 0; i < total_vertexes; i++){
		destroylist(grafo[i].list);
	}

	free(grafo);


}

void printAll(GRAFO *grafo)
{//imprime grafo

	int i;
	int nelem = grafo->count;

	printf("\n\n*******Impressao do Grafo*************\n\n");
	for(i = 0; i < nelem; i++){
		printf("Vertex: %d. Edges: ", grafo[i].vertex);
		print(grafo[i].list);
	}

	printf("\n\n*******Fim da Impressao do Grafo*************\n");


}

int next_adjacent_vertex(GRAFO *grafo, int index, int i)
{

	NODE *mynode;
	int j = 0;

	mynode = grafo[index].list->head;

	if(mynode == NULL){
		free(mynode);
		return -1;
	} else {
		while(mynode != NULL){
			if(j == i)return mynode->item.vertex;
			mynode = mynode->next;
			j++;
		}
	}

	return -1;

}

int index_next_adjacent_vertex(GRAFO *grafo, int index, int i)
{
	NODE *mynode;// = (NODE*)malloc(sizeof(NODE));
	int j = 0;
	int vertex = -1;

	mynode = grafo[index].list->head;

	if(mynode == NULL){
		//free(mynode);
		return -1;
	} else {
		while(mynode != NULL && vertex == -1){
			if(j == i)vertex = mynode->item.vertex;
			mynode = mynode->next;
			j++;

		}
	}

	//free(mynode);

	if(vertex != -1) {
		//retorna index do vertice
		for(j = 0; j < grafo->total; j++)
		{
			if(vertex == grafo[j].vertex)return j;

		}
	}

	return -1;

}

int index_next_minor_adjacent_by_order(GRAFO *grafo, int index, int order)
{
	int vertex, j;

	vertex = search_minor(grafo[index].list, order);

	if(vertex != -1) {
		//retorna index do vertice
		for(j = 0; j < grafo->count; j++)
		{
			if(vertex == grafo[j].vertex)return j;
		}
	}else return -1;

	return -1;


}

int vertex_next_minor_adjacent_by_order(GRAFO *grafo, int index, int order)
{
	int vertex, j;

	vertex = search_minor(grafo[index].list, order);

	if(vertex != -1) {
		//retorna index do vertice
		for(j = 0; j < grafo->total; j++)
		{
			if(vertex == grafo[j].vertex)return vertex;
		}
	}else return -1;

	return -1;


}

//seta todos os arestas deste vertice de origem como como aresta
//da arvore
int set_tree_edge(GRAFO *grafo, int index)
{
	NODE *mynode = grafo[index].list->head;

	if(mynode != NULL) {
		while(mynode != NULL)
		{
			mynode->item.type_edge = TREE_EDGE;
			mynode = mynode->next;
		}
	}

	//printf("vertex vale %d\n", vertex);
	return 1;

}

int set_return_edge(GRAFO *grafo, int index, int vertex)
{
	NODE *mynode = grafo[index].list->head;

	if(mynode != NULL) {
		while(mynode != NULL)
		{
			//printf("comparando %d com %d\n",mynode->item.vertex, vertex);
			if(mynode->item.vertex == vertex) {
				mynode->item.type_edge = RETURN_EDGE;
				return 0;
			}

			mynode = mynode->next;
		}
	}

	//printf("vertex vale %d\n", vertex);
	return -1;

}

int set_cross_edge(GRAFO *grafo, int index, int vertex)
{
	NODE *mynode = grafo[index].list->head;

	if(mynode != NULL) {
		while(mynode != NULL)
		{
			//printf("comparando %d com %d\n",mynode->item.vertex, vertex);
			if(mynode->item.vertex == vertex &&
					mynode->item.type_edge != FORWARD_EDGE &&
					mynode->item.type_edge != RETURN_EDGE) {
				mynode->item.type_edge = CROSS_EDGE;
				return 0;
			}

			mynode = mynode->next;
		}
	}

	//printf("vertex vale %d\n", vertex);
	return -1;

}


int set_forward_edge(GRAFO *grafo, int index, int vertex)
{
	NODE *mynode = grafo[index].list->head;

	if(mynode != NULL) {
		while(mynode != NULL)
		{
			//printf("comparando %d com %d\n",mynode->item.vertex, vertex);
			//if(mynode->item.vertex == vertex && mynode->item.type_edge != TREE_EDGE) {
			if(mynode->item.vertex == vertex) {
				mynode->item.type_edge = FORWARD_EDGE;
				return 0;
			}

			mynode = mynode->next;
		}
	}

	//printf("vertex vale %d\n", vertex);
	return -1;

}


int index_from_vertex(GRAFO *grafo, int vertex)
{
	int i;

	for(i = 0; i < grafo->total; i++)
	{
		if(grafo[i].vertex == vertex) return i;
	}

	return -1;

}


int next_vertex_from_tree_edge(GRAFO *grafo, int src_vertex)
{

	NODE *mynode;
	int index_graph, minor_vertex, flag;

	minor_vertex = -1;
	flag = 0;

	index_graph = index_from_vertex(grafo, src_vertex);

	if(index_graph == -1) return -1;

	mynode = grafo[index_graph].list->head;

	if(mynode != NULL) {
		while(mynode != NULL)
		{
			if(mynode->item.type_edge == TREE_EDGE){

				if(flag == 0){
					minor_vertex = mynode->item.vertex;
					flag = 1;
				} else if(mynode->item.vertex < minor_vertex) minor_vertex =  mynode->item.vertex;
			}
			mynode = mynode->next;
		}
	}

	return minor_vertex;

}


int next_vertex_from_forward_edge(GRAFO *grafo, int src_vertex)
{

	NODE *mynode;
	int index_graph, minor_vertex, flag;

	minor_vertex = -1;
	flag = 0;

	index_graph = index_from_vertex(grafo, src_vertex);

	if(index_graph == -1) return -1;

	mynode = grafo[index_graph].list->head;

	if(mynode != NULL) {
		while(mynode != NULL)
		{
			if(mynode->item.type_edge == FORWARD_EDGE){

				if(flag == 0){
					minor_vertex = mynode->item.vertex;
					flag = 1;
				} else if(mynode->item.vertex < minor_vertex) minor_vertex =  mynode->item.vertex;
			}
			mynode = mynode->next;
		}
	}

	return minor_vertex;

}

int next_vertex_from_return_edge(GRAFO *grafo, int src_vertex)
{

	NODE *mynode;
	int index_graph, minor_vertex, flag;

	minor_vertex = -1;
	flag = 0;

	index_graph = index_from_vertex(grafo, src_vertex);

	if(index_graph == -1) return -1;

	mynode = grafo[index_graph].list->head;

	if(mynode != NULL) {
		while(mynode != NULL)
		{
			if(mynode->item.type_edge == RETURN_EDGE){

				if(flag == 0){
					minor_vertex = mynode->item.vertex;
					flag = 1;
				} else if(mynode->item.vertex < minor_vertex) minor_vertex =  mynode->item.vertex;
			}
			mynode = mynode->next;
		}
	}

	return minor_vertex;

}

int next_vertex_from_cross_edge(GRAFO *grafo, int src_vertex)
{

	NODE *mynode;
	int index_graph, minor_vertex, flag;

	minor_vertex = -1;
	flag = 0;

	index_graph = index_from_vertex(grafo, src_vertex);

	if(index_graph == -1) return -1;

	mynode = grafo[index_graph].list->head;

	if(mynode != NULL) {
		while(mynode != NULL)
		{
			if(mynode->item.type_edge == CROSS_EDGE){

				if(flag == 0){
					minor_vertex = mynode->item.vertex;
					flag = 1;
				} else if(mynode->item.vertex < minor_vertex) minor_vertex =  mynode->item.vertex;
			}
			mynode = mynode->next;
		}
	}

	return minor_vertex;

}

int has_edge_from_vertexes(GRAFO *grafo, int vertex_src, int vertex_dst)
{
	NODE *mynode;
	int index_graph;

	index_graph = index_from_vertex(grafo, vertex_src);

	if(index_graph == -1) return -1;

	mynode = grafo[index_graph].list->head;

	if(mynode != NULL) {
		while(mynode != NULL)
		{
			if(mynode->item.vertex == vertex_dst) return 1;
			mynode = mynode->next;
		}
	}

	return -1;

}


int has_return_edge(GRAFO *grafo, int src_vertex, int dst_vertex)
{
	NODE *mynode;
	int index_vertex_src, index_vertex_dst;

	index_vertex_src = index_from_vertex(grafo, src_vertex);
	index_vertex_dst = index_from_vertex(grafo, dst_vertex);

	if(index_vertex_src == -1 || index_vertex_dst == -1) return -1;

	mynode = grafo[index_vertex_dst].list->head;

	if(mynode != NULL) {
		while(mynode != NULL)
		{
			if(mynode->item.vertex == src_vertex) return 1;
			mynode = mynode->next;
		}
	}

	return -1;

}
