#include<iostream>
#include<ostream>
#include<stack>
#include<list>
#include<vector>


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
};
template<typename T>
void dump(T &arr) {
	std::cout << "\n" << __PRETTY_FUNCTION__ << "\n";
	for (auto it = arr.begin(); it != arr.end(); it++) {
		std::cout << *it << ", ";
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

	std::cout << "\nbubble sort\n";
	std::vector<int> arr{100,2,4,21,4,12,31, 5};
	dump(arr);
	bubble(arr);
	dump(arr);
	return 0;
}
