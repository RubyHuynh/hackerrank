#include<iostream>
#include<ostream>
#include<stdio.h>
#include<vector>
#include<list>


bool bt(std::list<int> maze[], int start, int end, std::vector<bool> &visited, std::list<int> &rs) {
	if (start == end) {
		rs.push_back(start);
		return true;
	}

	visited[start] = true;
	auto it = maze[start].begin();
	while (it != maze[start].end()) {
		if (!visited[*it]) {
			if (bt(maze, *it, end, visited, rs)) {
				rs.push_front(start);
				return true;
			}			
		}
		it++;
	}
	//visited[start] = false;
	return false;	
}


std::list<int> solveMaze(std::list<int> maze[], int start, int end) {
	std::vector<bool> visited(100, false);
	std::list<int> rs;
	bt(maze, start, end, visited, rs);
 	for (auto it : rs) {
		printf ("%d -> ", it);
	}
	return rs;
}


int main() {
	std::list<int> maze[9];
	maze[0].push_back(1);
	maze[0].push_back(3);
	maze[1].push_back(0);
	maze[1].push_back(2);
	maze[2].push_back(1);
	maze[3].push_back(0);
	maze[3].push_back(4);
	maze[3].push_back(6);
	maze[4].push_back(3);
	maze[4].push_back(5);
	maze[4].push_back(7);
	maze[5].push_back(4);
	maze[6].push_back(3);
	maze[7].push_back(4);
	maze[7].push_back(8);

	solveMaze(maze, 0, 8);
	return 0;
}
