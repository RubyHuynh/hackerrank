



#include<stdlib.h>
#include<stdio.h>
#include<stdbool.h>
#include<string.h>
#include<sys/time.h>
#include<time.h>
#include<math.h>

void dumpArr(int* arr, int sz) {
 	int i = 0;
	for (; i < sz; ++i) {
		printf("%d \t", arr[i]);
	}
	printf("\n");
}

/* LINKED LIST */
typedef struct _Node {
        int                     val;
        void*			p;
	int*                    sz;
        struct _Node*           next;
} Node;

void addP(Node** list, void* val) {
        Node* tmp = *list;
        Node* item = (Node*) calloc(1, sizeof(Node));
        if (tmp) {
                item->sz = tmp->sz;
                item->next = tmp;
        }
        else {
                item->sz = (int*) calloc(1, sizeof(int));
        }
        item->p = val;
        (*(item->sz))++;
        *list = item;
}

void add(Node** list, int val) {
        Node* tmp = *list;
        Node* item = (Node*) calloc(1, sizeof(Node));
        if (tmp) {
                item->sz = tmp->sz;
                item->next = tmp;
        }
        else {
                item->sz = (int*) calloc(1, sizeof(int));
        }
        item->val = val;
        (*(item->sz))++;
        *list = item;
}

void del(Node* node) {
        (*(node->sz))--;
        free(node);
}

void dump(Node* node) {
	while (node) {
		printf("%d\t", node->val);
		node = node->next;
	}
	printf("\n");
}

/*    STACK   */
typedef struct _Stack {
	Node*			top;
} Stack;

void queue(Stack* stack, void* val) {
	Node* tmp = stack->top;
	Node* item = (Node*) malloc(sizeof(Node));
	item->p = val;
	item->next = NULL;
	while (tmp) {
		if (!tmp->next) {
			tmp->next = item;
			return;
		}
		tmp = tmp->next;
	}
	stack->top = item;
}

void push(Stack* stack, int val) {
	Node* item = (Node*) malloc(sizeof(Node));
	item->val = val;
	item->next = stack->top;
	stack->top = item;
}

Node* pop(Stack* stack) {
	Node* item = stack->top;
	if (item) {
		stack->top = item->next;
		item->next = NULL;
	}
	return item;
}

void dumpStack(Stack* stack) {
	dump(stack->top);
}


/*    TREE   */
typedef struct Tree {
	int 			val;
	struct Tree*		left;
	struct Tree*		right;
} Tree;

void insert(Tree** tree, int val) {
	Tree* item = (Tree*) calloc(1, sizeof(Tree));
	Tree* tmp = *tree;
	item->val = val;
	printf("%s val(%d)\n", __func__, val);
	if (tmp) {
		while (tmp) {
			if (tmp->val > val) {
			       	if (tmp->left) {
				       tmp = tmp->left;
			       	}
		 		else {
					tmp->left = item;
					break;
				}
			}
			else if (tmp->val < val) {
			       	if (tmp->right) {
				       tmp = tmp->right;
			       	}
		 		else {
					tmp->right = item;
					break;
				}
			}
			else {
				printf("duplicated, irnore\n");
				break;
			}
		}
	}
	else {
		*tree = item;
	}
}

void dumpLCR(Tree* tree, bool log) {
	if (log) {
		printf("%s In-Order\n", __func__);
	}
	if (!tree) return;
	dumpLCR(tree->left, false);
	printf("%d ", tree->val);
	dumpLCR(tree->right, false);
}

		
void dumpCLR(Tree* tree, bool log) {
	if (log) {
		printf("%s Pre-Order\n", __func__);
	}
	if (!tree) return;
	printf("%d ", tree->val);
	dumpLCR(tree->left, false);
	dumpLCR(tree->right, false);
}


void dumpLRC(Tree* tree, bool log) {
	if (log) {
		printf("%s Post-Order\n", __func__);
	}
	if (!tree) return;
	dumpLCR(tree->left, false);
	dumpLCR(tree->right, false);
	printf("%d ", tree->val);
}

Tree* dfs(Tree* tree, int val) {
	Tree* ret = NULL;
	
	if (!tree) return NULL;

	printf("%d vs %d, ", tree->val, val);

	if (tree->val == val) {
		printf("\nfound \n");
		return tree;
	}

	if(!(ret = dfs(tree->left, val))) {
		ret = dfs(tree->right, val);
	}
	return ret;
}

Tree* bfs(Tree* tree, int val) {
	Tree* ret = NULL, *left, *right;
	Stack q;
	if (!tree) return NULL;

	memset(&q, 0, sizeof(Stack));
	queue(&q, tree);
	while (q.top) {
		ret = (Tree*) q.top->p;
		pop(&q);
		printf("%d vs %d, ", ret->val, val);
		left = ret->left;
		right = ret->right;
		if (ret->val == val) {
			printf("\nfound \n");
			return ret;
		}
		if (left) queue(&q, left);
		if (right) queue(&q, right);
	}
	return ret;
}

int max(int x, int y) {
	return x > y ? x :y;
}

int min(int x, int y) {
	return x < y ? x : y;
}

int mxDepth(Tree* tree) {
	if (!tree) return 0;
	return 1 + max(mxDepth(tree->left), mxDepth(tree->right));
}

int mnDepth(Tree* tree) {
	if (!tree) return 0;
	return 1 + min(mnDepth(tree->left), mnDepth(tree->right));
}

bool isBalance(Tree* tree) {
	int mx = mxDepth(tree);
	int mn = mnDepth(tree);
	printf("\t%s mx(%d) mn(%d)\n", __func__, mx, mn);
       	return mx - mn <= 1 ? true : false;
}

void buildTree(int* arr, int start, int stop, Tree* tree) {
	int sz = stop + start;
	int mid = sz/ 2;
	if (start > stop) return;
	insert(&tree, arr[mid]);
	buildTree(arr, start, mid - 1, tree);
	buildTree(arr, mid + 1, stop, tree);
}

void buildList(Tree* tree, Node** ret) {
	int lvl = 0;
	
	if (!tree) return;
	printf("\nBuilding list[%d]\n\t%d\n", lvl, tree->val);
	addP(&ret[lvl], tree);
	while (1) {
		int i = 0, j = 0;
		bool next = false;
		Node* maybe;
		for (; i < (ret[lvl] ? *ret[lvl]->sz : 0); i++) {		
			Node* cu = ret[lvl];
			printf("\nBuilding list[%d]\n", lvl+1);
			j = 0;
			while (cu) {
				if (i == j++){
					printf("\t i=%d:", i);
					break;
				}
				cu = cu->next;
			}
			if (cu) {
				Tree* cur = (Tree*) cu->p;
				if (cur->left) {
					addP(&ret[lvl+1], cur->left);
					printf("\t%d \t", cur->left->val);
				}
				if (cur->right) {
					addP(&ret[lvl+1], cur->right);
					printf("\t %d \t", cur->right->val);
				} 
				next = true;

			}
		}
		if (!next) {
			printf("finished\n");
			break;
		}
		lvl++;
	}

}
/*         GRAPH       */
void dumpGr(int *ar, int sz) {
	int (*arr)[sz] = (int (*)[7])ar;
	int i = 0, j;
	while (i < sz) {
		j = 0;
		while (j < sz) {
			printf("%d\t", arr[i][j]);
			++j;
		}
		++i;
		printf("\n");
	}
}

typedef struct Point {
	int 		x;
	int 		y;
} Point;

int routeGr(int* ar, int sz, int s, int d) {
	Stack paths = {};
	int (*arr)[sz] = (int (*)[7])ar;
	Node* item = NULL;
	Point p = {d, d};
	int weight = 0;
	int j = 0;

	queue(&paths, &p);
	while ((item = pop(&paths))) {
		Point* val = (Point*) item->p;
		if (val->x == s && val->y == s) {
			printf("found route with weight %d\n", weight);
			return weight;
		}
		for (j = 0; j < val->x; ++j) {
			if (arr[j][val->x] > 0) {
				Point* tmp = (Point*) malloc (sizeof(Point));
				tmp->x = tmp->y = j;
				queue(&paths, tmp);
				printf("\t can reach (%d) through (%d)\n", val->x, j);
			}
		}
		printf("\n");
	}
	return 0;
}

/* compile debug log */
#ifdef TEMO
	#define DEBUG(X) X
#else
	#define DEBUG(X)
#endif

/* time measure */
#define TM_INIT\
	struct timeval time_start, time_end; double time_taken;

#define TM_START(_log)\
	gettimeofday(&time_start, NULL); \
	printf("%s ...\n", _log);

#define TM_END(_log)\
	gettimeofday(&time_end, NULL); \
	time_taken = (time_end.tv_sec - time_start.tv_sec) * 1e6; \
	time_taken = (time_taken + (time_end.tv_usec - time_start.tv_usec)) * 1e-6; \
	printf("%s took(%f)\n", _log, time_taken);
