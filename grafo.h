/*
 * grafo.h
 *
 *  Created on: Mar 19, 2013
 *      Author: emanuel
 */

#ifndef GRAFO_H_
#define GRAFO_H_

#include "list.h"

typedef struct grafo {
	int vertex;
	int color;
	int count;
	int total;
	int edges;
    int is_compacted;
	LIST *list;
}GRAFO;

GRAFO* createGraph(int);
void insertVertexAtGraph(GRAFO*, int);
int insertEdgeAtGraph(GRAFO*, int , int, int);
void printVertexes(GRAFO*);
void printAll(GRAFO*);
int next_adjacent_vertex(GRAFO *, int, int);//grafo, index_vertex, index_adjacent
//retorna o indice no vetor de vertices
int index_next_adjacent_vertex(GRAFO*, int, int);
//retorna o i-esimo indice no vetor de vertice
//consultando suas arestas adjacente
int index_next_minor_adjacent_by_order(GRAFO*, int, int); //grafo, index, order (next minor)
//retorna o i-esimo menor vertice que faz arestas com o vertice de origem
int index_next_minor_adjacent_by_order(GRAFO*, int, int); //grafo, index, order (next minor)
//seta todos os arestas deste vertice de origem
//como como aresta da arvore
int set_tree_edge(GRAFO*, int);
int set_return_edge(GRAFO*, int, int);
int set_forward_edge(GRAFO*, int, int);
int set_cross_edge(GRAFO*, int, int);
//retorna (o primeiro) indice no grafo de um determinado vertice
int index_from_vertex(GRAFO*, int);
//retorna proximo vertice que faz parte de uma aresta
//de ligacao com o vertice de origem
int next_vertex_from_tree_edge(GRAFO*, int); //(grafo, vertice de origem)
//retorna proximo vertice que faz parte de uma aresta
//de travessia com o vertice de origem
int next_vertex_from_cross_edge(GRAFO*, int); //(grafo, vertice de origem)
//retorna proximo vertice que faz parte de uma aresta
//de avanco com o vertice de origem
int next_vertex_from_forward_edge(GRAFO*, int); //(grafo, vertice de origem)
//retorna proximo vertice que faz parte de uma aresta
//de retorno com o vertice de origem
int next_vertex_from_return_edge(GRAFO*, int); //(grafo, vertice de origem)
//verifica se tem aresta de retorno de dst -> src
int has_return_edge(GRAFO*, int, int); //(grafo, src, dst)
//verifica se existe uma aresta que liga o vertice src ao vertice dst
int has_edge_from_vertexes(GRAFO*, int, int);


void destroyGraph(GRAFO*);




#endif /* GRAFO_H_ */
