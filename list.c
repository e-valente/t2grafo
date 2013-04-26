/*
 * list.c
 *
 *  Created on: Mar 10, 2013
 *      Author: emanuel
 */

#include <stdlib.h>
#include <stdio.h>
#include "list.h"

void create(LIST **list)
{
	*list = (LIST*)malloc(sizeof(LIST));
	(*list)->head = NULL;
	(*list)->tail = NULL;
	(*list)->total = 0;
	//printf("list em criar = %p\n",list);
	//printf("*list em criar = %p\n",*list);
}

int insert(LIST *list, ITEM *item)
{
	//cria novo nó
	NODE *mynode = (NODE*)malloc(sizeof(NODE));

	if(mynode != NULL) {
		mynode->item = *item; //apenas o conteudo será copiado (operacao valida para structs tb
		mynode->next = NULL;


		//se a lista esta vazia inserimos no inicio
		if(list->head == NULL) {
			list->head = mynode;
		}else {
			//o ultimo elemento sera o penultimo
			list->tail->next = mynode;
		}

		//o elemento inserido sera o ultimo
		list->tail = mynode;
		list->total++;

		return 0;

	}else return 1; //impossivel alocar espaco pro novo nó

}

void print(LIST *list)
{
	NODE *mynode = list->head;

	if(mynode == NULL){
		printf("Lista vazia!\n");
	} else {
		while(mynode != NULL){
			printf(" %d => weight: %d type: %d; ", mynode->item.vertex, mynode->item.weight, mynode->item.type_edge);
			mynode = mynode->next;
		}

		printf("\n");
	}

}

int search(LIST *list, int key)
{
	NODE *mynode = list->head;

	if(mynode != NULL) {
		while(mynode != NULL)
		{
			if(mynode->item.key == key) return 1;
			mynode = mynode->next;
		}
	}

	return 0;
}

int search_minor(LIST *list, int order)
{
	NODE *mynode;
	int *vector;
	int i, j, count;
	int tmp;

	 mynode = list->head;

	count = 0;

	vector = (int*)malloc(sizeof(int)*100);
	//printf("list total vale: %d\n", list->total);

	if(mynode != NULL) {
		while(mynode != NULL)
		{
			vector[count++] = mynode->item.vertex;
			mynode = mynode->next;
		}
	}


	if(order >= count) {
		if(vector != NULL)free(vector);
		return -1;
	}
	else{
		//inline insertion sort
		for(i = 0; i < count -1; i++)
		{
			j = i;
			//a cada iteracao deixa o menor elemento
			//à esquerda
			while(vector[j+1] < vector[j] && j >= 0){
				//swap
				tmp = vector[j+1];
				vector[j+1] = vector[j];
				vector[j] = tmp;
				j--;
			}
		}

	}

	tmp = vector[order];
	if(vector!=NULL)free(vector);

	return tmp;


}

int removelast(LIST *list)
{
	NODE *mynode = list->head;

	//verifica se a lista esta vazia
	if(mynode != NULL) {

		//procura pelo penultimo nó (bkpearemos), pois senao o perderemos
		while(mynode->next != NULL && mynode->next != list->tail) {

			mynode = mynode->next;
		}

		//verifica se  a lista tem um só nó
		//nao precisamos usar o penultimo nó
		if(list->head == list->tail){
			free(mynode->next); //pois mynode é penultimo
			list->tail->next = NULL;
		} else {
			//temos que usar o penultimo (backup)
			//nó, pois temos mais que um nó na lista
			free(list->tail);
			list->tail = mynode;
			list->tail->next = NULL;

		}

		return 1;

	}else return 0; //lista vazia


}

int destroylist(LIST *list)
{
	NODE *mynode = list->head;
	int count = 0;

	//lista vazia
	if(mynode == NULL){
		free(list);
		//printf("Lista vazia! Nao foi removido nada!\n");
		return 0;

	}

	do{
		//mynode sempre tera um elemento
		//a frente do head, pois destruiremos
		//do comeco p/ o final
		mynode = mynode->next;
		free(list->head);
		count++;
		list->head = mynode;
		//enquanto o primeiro elemento da listanao seja nulo
		//se for nulo chegaremos no "next" do nó tail.
	}while(list->head != NULL);

	free(list);

	//printf("total de remocoes: %d\n",count);
	return count;

}
