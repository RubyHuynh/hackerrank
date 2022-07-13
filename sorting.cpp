#include<iostream>
#include<ostream>
#include<stack>
#include<list>
#include<vector>
#include<queue>
#include<algorithm>
#include<string.h>


class Graph {
	int 		v; /* number of vertices */
	std::list<int>  *adj;

	void topologicalAdjacent(int v, bool *visited, std::stack<int> &rs) {
		// 1. mark the current node as visited
		visited[v] = true;

		// 2. recur for all he vertices adjacent to this vertex
		//sdt::list<int>::iterator i;
		for (auto i = this->adj[v].begin(); i != this->adj[v].end(); ++i) {
			if (!visited[*i]) {
				topologicalAdjacent(*i, visited, rs);
			}
		}

		// 3. push value to rs
		rs.push(v);
	}
public:
	Graph(int V) {
		this->v = V;
		this->adj = new std::list<int>[V];
	}


	void addEdge(int v, int w) {
		this->adj[v].push_back(w);
	}

		
	void topologicalSort() {
		std::stack<int> rs;

		// 1. mark all the vertices as not visited
		bool *visited = new bool[this->v];
		for (int i = 0; i < this->v; i++) {
			visited[i] = false;
		}

		// 2. call the recursive helper function to 
		// store the topilogical values
		for (int i = 0; i < this->v; i++) {
			if (!visited[i]) {
				topologicalAdjacent(i, visited, rs);
			}
		}

		// 3. print rs
		while (!rs.empty()) {
			std::cout << rs.top() << " ";
			rs.pop();
		}
				
	}

	std::vector<int> bfs(int idx) {
		std::vector<int> rs;
		std::vector<bool> visited(this->v, false);

		std::queue<int> q;
		visited[idx] = true;
		q.push(idx);
		std::cout << "\n" << __func__;
		while (!q.empty()) {
			idx = q.front();
			rs.push_back(idx);
			q.pop();
			for (auto it : this->adj[idx]) {
				if (!visited[it]) {
					visited[it] = true;
					q.push(it);
				}
			}
		}
		return rs;
	}
	// 13. Clone a Directed Graph
	Graph* clone() {
		Graph* rs = new Graph(this->v);

		std::vector<int> visited(this->v, false);
		std::queue<int> q;
		visited[0] = true;
		q.push(0);
		while (!q.empty()) {
			int idx = q.front();
			//rs->addEdge(idx, this->adj[idx]);
			q.pop();
			for (auto it : this->adj[idx]) {
				if (!visited[it]) {
					visited[it] = true;
					q.push(it);
				}
			}
		}
		return rs;
	}
};
template<typename T>
void swap(T *a, T *b) {
	std::cout << "\n\t\t\t swapping " << *a << "<->" << *b;
	T c = *a;
	*a = *b;
	*b = c;
}
template<typename T>
void dump(T &arr) {
	std::cout << "\n" << __PRETTY_FUNCTION__ << "\n";
	for (auto it = arr.begin(); it != arr.end(); it++) {
		std::cout << *it << ", ";
	}
}

template<typename T>
void dump(T *arr) {
	std::cout << "\n" << __PRETTY_FUNCTION__ << "\n";
	for (auto it = arr->begin(); it != arr->end(); it++) {
		std::cout << *it << ", ";
	}
}

// max heap
void buildMaxHeap(std::vector<int> &arr) {
	std::cout << "\n\t" << __func__;
	for (int i = 1; i < arr.size(); i++) {
		if (arr[i] > arr[(i-1)/2]) {
			int j = i;
			while (arr[j] > arr[(j-1)/2]) {
				swap(&arr[i], &arr[(j-1)/2]);
				j = (j-1)/2;
			}
		}
	}
}

void heapSort(std::vector<int> &arr) {
	std::cout << "\n\t" << __func__;
	buildMaxHeap(arr);
	dump(arr);
	for (int i = arr.size() - 1; i > 0; i--) {
		swap(&arr[0], &arr[i]);
		int j = 0, idx;
		do {
			idx = 2*j + 1;
			if (arr[idx] < arr[idx +1] && idx < (i -1)) {
				idx++;
			}

			if (arr[j] < arr[idx] && idx < i) {
				swap(&arr[j], &arr[idx]);
			}
			j = idx;
		}
		while (idx < i);
	}
}

// quick sort
int partition(std::vector<int> &arr, int low, int high) {
	int pivot = arr[high];
	int i = low - 1;

	for (int j = low; j <= high; j++) {
		if (arr[i] < pivot) {
			i++;
			swap(&arr[i], &arr[j]);
		}
	}
	swap(&arr[i + 1], &arr[high]);
	return i + 1;
}

void quick(std::vector<int> arr, int low, int high) {
	if (low < high) {
		int pivot = partition(arr, low, high);
		quick(arr, low, pivot - 1);
		quick(arr, pivot + 1, high);
	}
}


//
#define RANGE 255
template<typename T>
void counting(std::vector<T> &arr) {
	T rs[arr.size()];
	
	T count[RANGE];
	memset(count, 0, sizeof(count));

	for (int i = 0; i < arr.size(); i++) {
		++count[arr[i]];
	}

	for (int i = 1; i <= RANGE; i++) {
		count[i] += count[i-1];
	}

	for (int i = 0; i < arr.size(); i++) {
		rs[count[arr[i]]-1] = arr[i];
		--count[arr[i]];
	}
	for (int i = 0; i < arr.size(); i++) {
		arr[i] = rs[i];
	}
}

//
void bucket(std::vector<float> &arr) {
	std::vector<float> bucket[arr.size()];
	for (int i = 0; i < arr.size(); i++) {
		int index = arr.size() * arr[i];
		std::cout <<"\t\t index of " << arr[i] << " is " << index << "\n";
		bucket[index].emplace_back(arr[i]);
	}

	for (int i = 0; i < arr.size(); i++) {
		sort(bucket[i].begin(), bucket[i].end());
	}

	int index = 0;
	for (int i = 0; i < arr.size(); i++) {
		for (int j = 0; j < bucket[i].size(); j++) {
			arr[index++] = bucket[i][j];
		}
	}
}

void mergeArr(std::vector<int> &arr, int l, int m, int r) {
	int i, j, k;
	int n1 = m - l +1; // first part
	int n2 = r -m; // second part
	
	int L[n1], R[n2];

	// temp arrays
	for (int i  = 0; i < n1; i++) {
		L[i] = arr[l+i];
	}
	for (int i = 0; i < n2; i++) {
		R[i] = arr[m + 1 + i];
	}
	

	i = 0; j = 0; k = l;
	while (i < n1 && j < n2) {
		if (L[i] <= R[j]) {
			arr[k++] = L[i++];
		}
		else {
			arr[k++] = R[j++];
		}
	}
	
	while (i < n1) {
		arr[k++] = L[i++];
	}

	while (j < n2) {
		arr[k++] = R[j++];
	}
}

// O(nlogn)
void merge(std::vector<int> &arr, int l, int r) {
	if (l < r) {
		int m = l + (r-l)/2;
		merge(arr, l, m);
		merge(arr, m + 1, r);
		
		mergeArr(arr, l, m, r);
	}
}

// O(n^2), O(1)
void bubble(std::vector<int> &arr) {
	std::cout << __func__ << "\n";
	for (int i = 0; i < arr.size(); i++) {
		for (int j = i; j < arr.size() - i - 1; j++) {
			if (arr[j] > arr[j+1]) {
				std::swap(arr[j], arr[j+1]);
			}
		}
	}
}
int main() {
	Graph g(6);
	g.addEdge(5, 2);
	g.addEdge(5, 0);
	g.addEdge(4, 0);
	g.addEdge(4, 1);
	g.addEdge(2, 3);
	g.addEdge(3, 1);
	std::cout << "Topological sorting of the given Graph: \n\t";
	g.topologicalSort();
	auto bbb = g.bfs(5);
	dump(bbb);
	auto ccc = g.clone();

	std::cout << "\nbubble sort\n";
	std::vector<int> arr{100,2,4,21,4,12,31, 5};
	dump(arr);
	bubble(arr);
	dump(arr);

	
	std::cout << "\nmerge sort\n";
	std::vector<int> arr2{100,2,4,21,4,12,31, 5};
	dump(arr2);
	merge(arr2, 0, arr2.size() -1);
	dump(arr2);

	std::cout << "\nbucket sort\n";
	std::vector<float> arr3{0.897, 0.565, 0.656, 0.1234, 0.665, 0.3434};
	dump(arr3);
	bucket(arr3);
	dump(arr3);


	std::cout << "counting sort\n";
	std::vector<char> arr4{'a','e','d','g', 'z', 's'};
	dump(arr4);
	counting(arr4);
	dump(arr4);
	std::cout << "\n";

	
	std::cout << "\nquick sort\n";
	std::vector<int> arr5{100,2,4,21,4,12,31, 5};
	dump(arr5);
	quick(arr5, 0, arr5.size()-1);
	dump(arr5);


	std::cout << "\nmax heap sort\n";
	std::vector<int> arr6{100,2,4,21,4,12,31, 5};
	dump(arr6);
	heapSort(arr6);
	dump(arr6);
	return 0;
}
