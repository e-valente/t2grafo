/*
 * trip.c
 *
 *  Created on: Apr 4, 2013
 *      Author: emanuel
 */

#include <stdlib.h>
#include <stdio.h>
#include "dfs.h"
#include "trip.h"

trip_t* init_trip(void)
{
	trip_t *my_trip;

	my_trip = (trip_t*)malloc(sizeof(trip_t));


	my_trip->visited_cities = NULL;
	my_trip->total = 0;

	return my_trip;

}

void insert_city_on_trip(trip_t *my_trip, int city)
{
	int count;

	count = my_trip->total++;

	my_trip->visited_cities = (int*)realloc(my_trip->visited_cities,
			sizeof(int) * (count +1));

	my_trip->visited_cities[count] = city;

}

void print_trip(trip_t *my_trip)
{
	int i;

	//printf("\n");

	for(i = 0; i < my_trip->total -1; i++)
	{
		printf("%d ", my_trip->visited_cities[i]);

	}

	printf("%d\n", my_trip->visited_cities[i]);

}

int next_city(GRAFO *grafo, int current_city, int last_city, int *counter_time, int *last_action)
{
	int city;


	if(*counter_time == 6) *counter_time = 1;

	printf("cidade atual %d cidade anterior: %d counter: %d ultima_acao %d\n\n ",
			current_city, last_city, *counter_time, *last_action);

	/*para finalizar, verificar se cidade atual nao tem aresta
	 * da arvore, entao bata dar valor -1 para city
	 */

	/*********** TEMPO = 1, 4 ou 5**********************************************/
	if(*counter_time == 1 || *counter_time == 4 || *counter_time == 5 ){

		//sempre terá uma aresta da arvore
		city = next_vertex_from_tree_edge(grafo, current_city);
		(*counter_time)++;
		return city;

	}


	/*********** TEMPO = 2**********************************************/

	//brigam e tentam cruzamento



	if(*counter_time == 2  && *last_action != CROSS){
		//prioridade é cruzamento
		city = next_vertex_from_cross_edge(grafo, current_city);
		if(city >= 0) {
			*last_action = CROSS;
			(*counter_time) = 1;
			return city;
		}
	}



	//brigam e tentam o retorno
	if(*counter_time == 2 && *last_action != BACK){
		//*last_action = BACK;
		//tentam voltar pela aresta de retorno
		city = next_vertex_from_return_edge(grafo, current_city);
		//tentam retorno pela aresta de cruzamento
		//if(city < 0)city = next_vertex_from_cross_edge(grafo, current_city);
		if(city >= 0) {
			*last_action = BACK;
			(*counter_time) = 1;
			return city;
		}else{ //fazem as pazes em ultimo caso
			city = next_vertex_from_tree_edge(grafo, current_city);
			(*counter_time) += 1;
			return city;

		}
	}


	/***************TEMPO = 3********************************/

	//brigam e tentam cruzamento



	if(*counter_time == 3  && *last_action != CROSS){
		//prioridade é cruzamento
		city = next_vertex_from_cross_edge(grafo, current_city);
		if(city >= 0) {
			*last_action = CROSS;
			(*counter_time) = 1;
			return city;
		}
	}



	//brigam e tentam atalho
	if(*counter_time == 3 && *last_action != SHORTCUT ){
		//*last_action = SHORTCUT;
		city = next_vertex_from_forward_edge(grafo, current_city);
		if(city >= 0) {
			*last_action = SHORTCUT;
			(*counter_time) = 1;
			return city;



		} else{ //fazem as pazes e seguem
			city = next_vertex_from_tree_edge(grafo, current_city);
			//nesse caso o contador é "zerado"
			(*counter_time) = 1;
			return city;

		}
	}


	/**********************CASO NAO SEJA TOMADA DECISAO EM T=2 ou T=3*********/

	if(*counter_time == 2 || *counter_time == 3)
	{
		//sempre terá uma aresta da arvore
		city = next_vertex_from_tree_edge(grafo, current_city);
		(*counter_time) ++;
		return city;
	}

	return city;
}


void end_trip(trip_t *my_trip)
{
	free(my_trip->visited_cities);

}
