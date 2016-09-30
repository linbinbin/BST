/*
 * tree.c : 二分探索木
 *
 *          Copyright (C) 2015 Makoto Hiroi
 */
#include <stdio.h>
#include <stdlib.h>
#include "tree.h"

// 節の生成
static Node_t *make_node(void * x)
{
	Node_t *node = malloc(sizeof(Node_t));
	if (node != NULL) {
		node->item = x;
		node->left = NULL;
		node->right = NULL;
	}
	return node;
}

// 節の廃棄
static void destroy_node(Node_t *node)
{
	if (node != NULL) {
		destroy_node(node->left);
		destroy_node(node->right);
		free(node);
	}
}

// データの探索
static bool search_node(void* x, Node_t *node)
{
	while (node != NULL) {
		if (*(int *)node->item == *(int *)x)
			return true;
		else if (*(int *)x < *(int *)node->item)
			node = node->left;
		else
			node = node->right;
	}
	return false;
}

// データの探索
static bool replace_node(void* x, Node_t *node)
{
	while (node != NULL) {
		if (*(int *)node->item == *(int *)x) {
			printf("replace %d\n", *(int *)x);
			node->item = x;
			return true;
		}
		else if (*(int *)x < *(int *)node->item)
			node = node->left;
		else
			node = node->right;
	}
	return false;
}

// データのGet
Node_t* get_node(void* x, Node_t *node)
{
	while (node != NULL) {
		if (*(int *)node->item == *(int *)x)
			return node;
		else if (*(int *)x < *(int *)node->item)
			node = node->left;
		else
			node = node->right;
	}
	return NULL;
}

// データの挿入
static Node_t *insert_node(void *x, Node_t *node, void **pre, void **nxt)
{
	if (node == NULL)
		return make_node(x);
	else if (*(int *)x < *(int *)node->item) {
		node->left = insert_node(x, node->left, pre, nxt);
		if (*nxt == NULL)
			*nxt = node->item;
	}
	else if (*(int *)x > *(int *)node->item) {
		node->right = insert_node(x, node->right, pre, nxt);
		if (*pre == NULL)
			*pre = node->item;
	}
	return node;
}

// 最小値の探索
static void * search_min(Node_t *node)
{
	while (node->left != NULL) node = node->left;
	return node->item;
}

// 最大値の探索
static void * search_max(Node_t *node)
{
	while (node->right != NULL) node = node->right;
	return node->item;
}

// 最小値の削除
static Node_t *delete_min(Node_t *node)
{
	if (node->left == NULL) {
		Node_t *temp = node->right;
		free(node);
		return temp;
	}
	node->left = delete_min(node->left);
	return node;
}

// 最大値の削除
static Node_t *delete_max(Node_t *node)
{
	if (node->right == NULL) {
		Node_t *temp = node->left;
		free(node);
		return temp;
	}
	node->right = delete_max(node->right);
	return node;
}

// データの削除
static Node_t *delete_node(void *x, Node_t *node)
{
	if (node == NULL) return NULL;
	if (*(int *)x == *(int *)node->item) {
		if (node->left == NULL) {
			Node_t *temp = node->right;
			free(node);
			return temp;
		}
		if (node->right == NULL) {
			Node_t *temp = node->left;
			free(node);
			return temp;
		}
		node->item = search_min(node->right);
		node->right = delete_min(node->right);
	} else if (*(int *)x < *(int *)node->item)
		node->left = delete_node(x, node->left);
	else
		node->right = delete_node(x, node->right);
	return node;
}

// 巡回
static void foreach_node(void (*func)(void *), Node_t *node)
{
	if (node != NULL) {
		foreach_node(func, node->left);
		func(node->item);
		foreach_node(func, node->right);
	}
}

//
// 公開する関数
//

// 木の生成
Tree *make_tree(void)
{
	Tree *tree = malloc(sizeof(Tree));
	if (tree != NULL) {
		tree->root = NULL;
	}
	return tree;
}

// 木の廃棄
void destroy_tree(Tree *tree)
{
	destroy_node(tree->root);
	free(tree);
}

// 空の木か
bool is_empty_tree(Tree *tree)
{
	return tree->root == NULL;
}

// データの探索
bool search_tree(void * x, Tree *tree)
{
	return search_node(x, tree->root);
}

// 最小値を求める
void * search_min_tree(Tree *tree, bool *err)
{
	if (is_empty_tree(tree)) {
		*err = false;
		return 0;
	}
	*err = true;
	return search_min(tree->root);
}

// 最大値を求める
void * search_max_tree(Tree *tree, bool *err)
{
	if (is_empty_tree(tree)) {
		*err = false;
		return 0;
	}
	*err = true;
	return search_max(tree->root);
}

// データの挿入
void insert_tree(void *x, Tree *tree, void **pre, void **nxt)
{
	if (!replace_node(x, tree->root))
		tree->root = insert_node(x, tree->root, pre, nxt);
}

// データの削除
void delete_tree(void *x, Tree *tree)
{
	tree->root = delete_node(x, tree->root);
}

// 最小値を削除
void delete_min_tree(Tree *tree)
{
	if (!is_empty_tree(tree))
		tree->root = delete_min(tree->root);
}

// 最大値を削除
void delete_max_tree(Tree *tree)
{
	if (!is_empty_tree(tree))
		tree->root = delete_max(tree->root);
}

// 巡回
void foreach_tree(void (*func)(void *), Tree *tree)
{
	foreach_node(func, tree->root);
}
