/*
 * tree.h
 *
 *  Created on: Apr 14, 2013
 *      Author: emanuel
 */

#ifndef TREE_H_
#define TREE_H_


typedef struct _tree_t_
{
	int total_elem;
	int **values;

}tree_t;


typedef struct _tree_vector_t {
	int total_trees;
	tree_t *tree;
}tree_vector_t;

tree_t* createTree(int nelem);
tree_vector_t* createTreeVector();
void destroyTree(tree_t*);
void destroyVector(tree_vector_t*);
void insertTreeAtVector(tree_vector_t**, tree_t*);

#endif /* TREE_H_ */
