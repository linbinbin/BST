/*
 * tree.h : 二分探索木
 *
 *          Copyright (C) 2015 Makoto Hiroi
 */
#ifndef _TREE_H_
#define _TREE_H_

#include <stdlib.h>
#include <stdbool.h>

// 節の定義
typedef struct node {
	void* item;
	struct node *left;
	struct node *right;
} Node_t;

// 木の定義
typedef struct {
	Node_t *root;
} Tree;

typedef struct {
	char *dummy;
	int left;
	int pre;
	int next;
	int idx;
} user_t;


// 関数宣言
Node_t* get_node(void* x, Node_t *node);
Tree *make_tree(void);
void destroy_tree(Tree *tree);
bool is_empty_tree(Tree *tree);
bool search_tree(void * x, Tree *tree);
void *search_min_tree(Tree *tree, bool *err);
void *search_max_tree(Tree *tree, bool *err);
void insert_tree(void *x, Tree *tree, void **pre, void **nxt);
void delete_tree(void *x, Tree *tree);
void delete_min_tree(Tree *tree);
void delete_max_tree(Tree *tree);
void foreach_tree(void (*func)(void *), Tree *tree);
#endif
