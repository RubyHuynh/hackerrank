#include<stdlib.h>
#include<stdio.h>
#include<string.h>
#include<stdbool.h>
#include"../hash.c"

#define LOG(_X) printf("%d\n", _X);
#define MAX_MAX (5000000 * sizeof(int))

int* _arr;
char** _arrStr;

/*
char** bestContruct(const char* target, char** arr, int n) {
	for (i = 0 ; i < n; i++) {
		if (
	}
}
*/

bool canCompose(const char* target, char** arr, int n) {
	int i = 0, j, k;
	int idx = hash(target);
	printf("\n");
	for (i = 0; i < n; i++) {
		printf("%s-->%d\n", arr[i], jenkins(arr[i], strlen(arr[i])));
	}

	if (1) {
		int tabuN = strlen(target) + 1;
		bool tabu[tabuN];
		char tmp[tabuN];
		memset(tabu, 0, sizeof(tabu));
		tabu[0] = true;
		for (i = 0; i < tabuN - 1; i++) {
			printf("\t working on %s\n", &target[i]);
			if (tabu[i]) {
				for (j = 0; j < n; j++) {
					memset(tmp, 0, sizeof(tmp));
					strncpy(tmp, target + i, strlen(arr[j]));
					printf("\t\t comparing to %s(%p), rs=%s(%p)\n", arr[j], arr[j], tmp, tmp);
					if (!strcasecmp(tmp, arr[j])) {
						tabu[i+strlen(arr[j])] = true;
						printf("\t\tOK %d", i + strlen(arr[j]));
						
					}
				}
			}
		}
		printf("\t finished\n");
		for (i = 0; i < tabuN; i++) {
			printf("%d\t", tabu[i]);
		}
		return tabu[tabuN-1];
	}
	
	return false;
}


int tabGridTraveler(int n, int m) {
	int table[n+1][m+1];
	int i, j;
	memset(table, 0, sizeof(table));

	table[1][1] = 1;
	for (i = 0 ; i <= n; i++) {
		for (j = 0; j <= m; j++) {
			int cur = table[i][j];
			if (j + 1 <= m) table[i][j+1] += cur;
			if (i + 1 <= n) table[i+1][j] += cur;
		}
	}
	return table[n][m];
}
typedef struct Info {
	int* arr;
	int n;
} Info;

void append(Info* info1, Info* item) {
	int i;
	for (i = 0; i < item->n; i++, info1->n++) {
		info1->arr[info1->n] = item->arr[i];
//		printf("%s [%d]=%d", __func__, info1->n, info1->arr[info1->n]);
	}
	
}

void append1(Info* info1, int item) {
	info1->arr[info1->n++] = item;
}

void clone(Info* info1, Info* item) {
	int i;
	
	//memset(info1->arr, 0, sizeof(int)*info1->n);
	info1->n=0;
	
	for (i = 0; i < item->n; i++, info1->n++) {
		info1->arr[info1->n] = item->arr[i];
	}
}
void bestSum(int target, int* arr, int n) {
	Info* tabu[target+1];
	Info tmp;
	int i, j,k;
	
	memset(tabu, 0, sizeof(tabu));
	tabu[0] = calloc(1, sizeof(Info));
	
	for(i = 0; i < target; i++) {
		for (j = 0; j < n; j++) {
			if (tabu[i] != NULL && (i+arr[j]) <= target) {
				memset(&tmp, 0, sizeof(tmp));
				tmp.arr = calloc(1, sizeof(int)*target);
				append(&tmp, tabu[i]);
				append1(&tmp, arr[j]);
				if (!tabu[i+arr[j]]) {
					tabu[i+arr[j]] = calloc(1, sizeof(Info));
					tabu[i+arr[j]]->arr = calloc(1, sizeof(int)*target);
					clone(tabu[i+arr[j]], &tmp);
					printf("\t fresh clone\n");
				}
				else {
					if (tabu[i+arr[j]]->n < tmp.n) {
						printf("\tshorter, do nothing\n");
					}
					else {
						clone(tabu[i+arr[j]], &tmp);
						printf("\t wipe clone\n");
					}
				}
			}	
		}
	}
	printf("\tResult is\n\t");
	for (i =0; i < tabu[target]->n; i++) {
		printf("%d ", tabu[target]->arr[i]);
	}
	return tabu[target];
}


bool tabCanSum(int target, int *arr, int n) {
	int i, j;
	int table[target+1];

	memset(table, 0, sizeof(table));
	table[0] = true;
	for (i = 0; i <= target; i++) {
		if (table[i]) {
			for (j = 0; j< n; j++) {
				if (i + arr[j] <= target) {
					table[i+arr[j]] = true;
				}
			}
		}
	}
	return table[target];
}

bool canSum(int target, int* arr, int n, int* memo) {
	int i;
	if (target == 0) return true;
	if (target < 0) return false;
	if (memo[target]) return memo[target];
	for (i = 0; i < n; i++) {
		int remainder = target - arr[i];
		if (canSum(remainder, arr, n, memo)) {
			printf("\t %d\n", arr[i]);
			memo[arr[i]] = true;
			return true;
		}
	}
 	memo[target] = false;
	return false;
}


/*top-down*/
int fibo(int n, int* memo) {
	if (n <= 2) return 1;
	if (memo[n]) return memo[n];
	memo[n] = fibo(n-1, memo) + fibo(n-2, memo);
	return memo[n];
}

/* bottom-up */
int fibo0(int n, int* memo) {
	int i;

	memo[0] = 0;
	memo[1] = 1;

	for (i = 2; i <=n; i++) {
		memo[i] = memo[i-1] + memo[i-2];
	}
	return memo[n];
}
 
/*optimized bottom-up */
int fibo1(int n) {
	int a = 0, b = 1, rs, i;
	if (n == 0) return 0;
	
	for (i = 2; i <= n; i++) {
		rs = a + b;
		a = b;
		b = rs;
	}
	return rs;
}

/*Math*/
/*
#include<math.h>
int fib(int n) {
  double phi = (1 + sqrt(5)) / 2;
  return round(pow(phi, n) / sqrt(5));
}
*/
int main() {	
 	_arr = calloc(1, MAX_MAX);
	LOG(fibo(5, _arr));
	memset(_arr, 0, MAX_MAX);
	LOG(fibo(7, _arr));
	memset(_arr, 0, MAX_MAX);
	LOG(fibo(30, _arr));
	memset(_arr, 0, MAX_MAX);
	LOG(fibo0(30, _arr));
	LOG(fibo1(30));

	printf("===\n");
	{
		int arr[] = {3, 4,5, 25, 1};
		memset(_arr, 0, MAX_MAX);
		LOG(canSum(100, arr, 5, _arr))
		bestSum(100, arr, 5);
	}
	printf("=======\n");
	LOG(tabGridTraveler(5,3))

	printf("======\n");
	{
		int arr[] = {3, 4,5, 25, 1};
		memset(_arr, 0, MAX_MAX);
		LOG(tabCanSum(100, arr, 5))
	}

	printf("======\n");
	{
		char* arr[] = {"ab", "abc", "cd", "def", "abcf"};
		canCompose("abcdef", arr, 5);
	}
	{
		char* arr[] = {"bo", "rd", "ate", "t", "ska", "sk", "boar"};
		canCompose("skateboard", arr, sizeof(arr)/sizeof(arr[0]));
	}
	return 0;
}
