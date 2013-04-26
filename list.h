/*
 * list.h
 *
 *  Created on: Mar 10, 2013
 *      Author: emanuel
 */

#ifndef LIST_H_
#define LIST_H_

#define ORDINARY_EDGE 0
#define TREE_EDGE 1
#define FORWARD_EDGE 2
#define RETURN_EDGE 3
//#define ORDINARY_RETURN_EDGE 4
//#define ORDINARY_RETURN_EDGE 5
#define CROSS_EDGE 4


typedef struct {
	int key;
	int type_edge;
    int weight;
    int vertex;

}ITEM;

typedef struct node {
    ITEM item;
    struct node *next;
}NODE;

typedef struct {
    int total;
    NODE *head, *tail;
}LIST;

//prototypes
void create(LIST**);
int insert(LIST*, ITEM*);
void print(LIST*);
int search(LIST*, int);
int removelast(LIST*);
int destroylist(LIST*);
int search_minor(LIST*, int);


#endif /* LIST_H_ */
