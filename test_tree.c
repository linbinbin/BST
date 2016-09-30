#define _XOPEN_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <time.h>
#include "tree.h"

#define offsetof(st, m) ((size_t)(&((st *)0)->m))
// データの表示
void print_item(void *x)
{
	int offset = offsetof(user_t, left);
	printf("%d\n", *(int *)x);
	printf(" %p, add:%p idx:%d\n", x, x-offset, ((user_t *)(x-offset))->idx);
}

void print_tree(Tree *tree)
{
	foreach_tree(print_item, tree);
	printf("\n");
}

// 木の高さ
int height_node(Node_t *node)
{
	if (node == NULL) return 0;
	int a = height_node(node->left);
	int b = height_node(node->right);
	return 1 + (a > b ? a : b);
}

int height_tree(Tree *tree)
{
	return height_node(tree->root);
}

// シャッフル
void shuffle(double *buff, int size)
{
	for (int i = size - 1; i > 0; i--) {
		int j = rand() % (i + 1);
		double tmp = buff[i];
		buff[i] = buff[j];
		buff[j] = tmp;
	}
}

#define N 10
/*
void test1(void)
{
	int buff[N] = {5,6,4,7,3,8,2,9,1,0};
	Tree *tree = make_tree();
	for (int i = 0; i < N; i++) {
		insert_tree(&buff[i], tree);
		print_tree(tree);
	}
	for (int i = -1; i < N + 1; i++) 
		printf("%d\n", search_tree(&i, tree));
	for (int i = 0; i < N; i++) {
		delete_tree(&buff[i], tree);
		print_tree(tree);
	}
	destroy_tree(tree);
}

#define M 2000000

int buff[M];

void test2(void)
{
	for (int n = 250000; n <= M; n *= 2) {
		Tree *tree = make_tree();
		for (int i = 0; i < n; i++) buff[i] = rand();
		printf("----- %d -----\n", n);
		clock_t s = clock();
		for (int i = 0; i < n; i++) 
			insert_tree(&buff[i], tree);
		printf("挿入時間 %.3f\n", (double)(clock() - s) / CLOCKS_PER_SEC);
		printf("高さ %d\n", height_tree(tree));
		s = clock();
		for (int i = 0; i < n; i++)
			if (!search_tree(&buff[i], tree)) fprintf(stderr, "search error\n");
		printf("探索時間 %.3f\n", (double)(clock() - s) / CLOCKS_PER_SEC);
		s = clock();
		for (int i = 0; i < n; i++)
			delete_tree(&buff[i], tree);
		printf("削除時間 %.3f\n", (double)(clock() - s) / CLOCKS_PER_SEC);
		destroy_tree(tree);
	}
}
*/
void test3(int data_size) {
	int i;
	Tree *tree = make_tree();
	user_t *in_data;
	void **pre = malloc(sizeof(char *));
	void **nxt = malloc(sizeof(char *));
	*pre = NULL;
	*nxt = NULL;
	printf("--- generating data... \n");
	srand48(11);
	in_data = (user_t *)calloc(data_size, sizeof(user_t));
	for (i = 0; i < data_size; ++i) {
		in_data[i].left = (unsigned)(100 * drand48() / 4);
		in_data[i].idx = i;
		printf("idx:%d, left:%d, str_add:%p, left_add:%p\n", in_data[i].idx, in_data[i].left, &in_data[i], &in_data[i].left);
		insert_tree(&in_data[i].left, tree, pre, nxt);
		if (*pre) {
			printf("add *pre:%p, value pre:%d\n", *pre, *(int *)(*pre));
			*pre = NULL;
		}
		else
			printf("The first Data.\n");
		if (*nxt) {
			printf("add *nxt:%p, value *nxt:%d\n", *nxt, *(int *)(*nxt));
			*nxt = NULL;
		}
		else
			printf("The last Data.\n");
	}
	printf("done!\n");
	print_tree(tree);
}

int main(void)
{
	//test1();
	//test2();
	test3(10);
	return 0;
}
