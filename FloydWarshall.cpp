#include "stdafx.h"
#include <iostream>
#include <algorithm>
#include <vector>
#include <climits>
using namespace std;

void floydWarshall(vector<vector<int>>& adjMatrix)
{
	int n = adjMatrix.size();
	vector<vector<int>> adjMatK_Min1;
	vector<vector<int>> adjMatK;
	adjMatK = adjMatrix;
	for (int k = 0; k < n; ++k) {
		adjMatK_Min1 = adjMatK;
		for (int i = 0; i < n; ++i) {
			for (int j = 0; j < n; ++j) {
				//this is required else adding a number to INT_MAX will get it to negative
				int temp = adjMatK_Min1[i][k] + adjMatK_Min1[k][j];
				if (adjMatK_Min1[i][k] == INT_MAX || adjMatK_Min1[k][j] == INT_MAX)
					temp = INT_MAX;

				adjMatK[i][j] = std::min(adjMatK_Min1[i][j], temp);
			}
		}
	}
	adjMatrix = adjMatK;
}
/*
5 9 --|V|,|E|
1 2 3 --F,T,W
1 3 8
1 5 -4
2 4 1
2 5 7
3 2 4
4 1 2
4 3 -5
5 4 6
3 --Num of Q
4 3 --Shortest path from ,to
5 3
5 2
*/
int main() {
	std::ios::sync_with_stdio(false);

	int N = 0;
	cin >> N;
	int M = 0;
	cin >> M;
	vector<vector<int>> adjMatrix;
	for (int i = 0; i < N; ++i) {
		vector<int> temp;
		for (int j = 0; j < N; ++j) {
			if (i == j) {
				temp.push_back(0);
			}
			else
				temp.push_back(INT_MAX);
		}
		adjMatrix.push_back(temp);
	}
	while (M-- > 0) {
		int f = 0;
		int t = 0;
		int w = 0;
		cin >> f >> t >> w;
		adjMatrix[--f][--t] = w;
	}
	floydWarshall(adjMatrix);
	int Q = 0;
	cin >> Q;
	vector<int> op;
	while (Q-- > 0) {
		int f = 0;
		int t = 0;
		cin >> f >> t;
		if (adjMatrix[f-1][t-1] == INT_MAX)
			op.push_back(-1);
		else
			op.push_back(adjMatrix[f-1][t-1]);
	}
	std::for_each(op.begin(), op.end(), [](int a) {cout << a << endl; });

	return 0;
}