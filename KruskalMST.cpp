#include "stdafx.h"
#include <algorithm>
#include <iostream>
#include <unordered_map>
#include <unordered_set>
#include <map>
#include <vector>
#include <queue>
#include <forward_list>
#include <climits>
using namespace std;
namespace myGraph {
	template <typename T, typename Hash = std::hash<T>>
	class UnionFind {
	public:
		void addNode(T elem, T parent) {
			disjointSetMap_[elem] = std::make_pair(parent, 0);
		}
		std::pair<T, size_t> Find(T elem) {
			auto it = disjointSetMap_.find(elem);
			T parent;
			T rank;
			if (it != disjointSetMap_.end()) {
				parent = it->second.first;
				rank = it->second.second;
				while (parent != elem) {
					elem = parent;
					parent = disjointSetMap_.find(elem)->second.first;
					rank = disjointSetMap_.find(elem)->second.second;
				}
			}
			return std::make_pair(parent, rank);;
		}
		void Union(const T& elem1, const T& elem2) {
			std::pair<T, size_t> p1 = Find(elem1);
			std::pair<T, size_t> p2 = Find(elem2);
			if (p1.second >= p2.second) {
				auto it = disjointSetMap_.find(p2.first);
				it->second.first = p1.first;//update the parent for second
				if (p1.second == p2.second)
					++disjointSetMap_.find(p1.first)->second.second;//update first's rank
			}
			else {
				auto it = disjointSetMap_.find(p1.first);
				it->second.first = p2.first;//update the parent
			}
		}
	public:
		//Node,(parentNode,Rank)
		std::unordered_map<T, std::pair<T, size_t>, Hash> disjointSetMap_;
	};

	//Graph related stuff
	enum class vertexStates { UNDISCOVERED, DISCOVERED, PROCESSED };
	struct edge {
		int toNode_;
		int fromNode_;
		int weight_;
		edge(int f, int t, int w) :fromNode_{ f },toNode_ { t }, weight_{ w } {}
		edge(const edge& rhs) {
			fromNode_ = rhs.fromNode_;
			toNode_ = rhs.toNode_;
			weight_ = rhs.weight_;
		}
		int operator<(const edge&rhs) const {
			if (weight_ == rhs.weight_) {
				return (fromNode_ + weight_ + toNode_) < (rhs.fromNode_ + rhs.weight_ + rhs.toNode_);
			}
			else {
				return weight_ < rhs.weight_;
			}
		}
	};
	class Graph {
	public:
		unordered_map<int, int> vertices_;
		std::vector<edge> edgeList_;
		Graph(bool isDir = false) :isDirected{ isDir } {}
		void insert_vertex(int x) {
			if (vertices_.find(x) == vertices_.end()) {
				vertices_[x] = x;
			}
		}
		void insert_edge(int from, int to, int weight) {
			edgeList_.push_back(edge(from, to, weight));
		}

	private:
		bool isDirected;
	};

	int KruskalMST(Graph& g, int source) {
		int MSTWeight = 0;
		std::sort(g.edgeList_.begin(), g.edgeList_.end());
		UnionFind<int> uf;
		for (auto& v : g.vertices_) {
			uf.addNode(v.first,v.first);
		}
		for (int i = 0; i < g.edgeList_.size(); ++i) {
			myGraph::edge e = g.edgeList_[i];
			if (uf.Find(e.fromNode_).first != uf.Find(e.toNode_).first) {//no cycles
				uf.Union(e.fromNode_, e.toNode_);
				MSTWeight += e.weight_;
			}
		}

		return MSTWeight;
	}
	
}
/*
4 4 --Nodes Edges
1 2 24 --Edge from,to,weight
1 4 20
3 1 3
4 3 12
1 --Source Node
*/
int main()
{
	std::ios::sync_with_stdio(false);
	int T = 0; //number of test cases
	T = 1;
	vector<map<int, int>> op;
	while (T-- > 0)
	{
		myGraph::Graph g(false);
		int N = 0; int M = 0;
		cin >> N >> M;

		while (M-- > 0) {
			int f = 0;
			int t = 0;
			int w = 0;
			cin >> f >> t >> w;
			g.insert_vertex(f);
			g.insert_vertex(t);
			g.insert_edge(f, t, w);
		}
		int S = 0;
		cin >> S;
		
		int MSTW = myGraph::KruskalMST(g, S);
		cout << MSTW;
	}


	return 0;
}