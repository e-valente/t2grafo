/*
 * dfs.h
 *
 *  Created on: Apr 3, 2013
 *      Author: emanuel
 */

#ifndef DFS_H_
#define DFS_H_

#define WHITE 0
#define GRAY 1
#define BLACK 2

#include "grafo.h"

//fila (vetor) que armazenará o resultado (caminho)
//poderia ser uma pilha
typedef struct _dfs_result_t
{
	int total;
	int count;
	int *index;
} dfs_result_t;


//vetor de predecessores
typedef struct _dfs_predec_t
{
	int total;
	int **index;
} dfs_predec_t;

typedef struct _order_access_black_t
{
	int total;
	int *value;
}order_access_black_t;


int insert_at_result_queue(int);
//retorna a arvore resultante (=predecessores)
void dfs_init(GRAFO*, int, int, int);
void dfs_close();
void dfs(GRAFO*, int, int);
//retorna 2 se src vem antes e nao sao vizinhos
//retorna 1 se src ven antes de sao vizinhos
//retorna 0 se dst vem antes e nao sao vizinhos
//retorna -1 se dst vem antes e sao vizinhos
int vertex_comes_before_or_after_on_dfs(int vertex_src, int vertex_dst);


#endif /* DFS_H_ */
