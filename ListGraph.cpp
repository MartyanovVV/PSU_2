#include "ListGraph.h"

CListGraph::CListGraph(IGraph* other) {
	adjacency_lists.clear();
	adjacency_lists.resize((*other).VerticesCount());
	for (int i = 0; i < (*other).VerticesCount(); ++i) {
		(*other).FindAllAdjacentOut(i, adjacency_lists[i]);
	}
}

void CListGraph::AddEdge(int from, int to) {
	adjacency_lists[from].push_back(to);
}

int CListGraph::VerticesCount() const {
	return static_cast<int>(adjacency_lists.size());
}

void CListGraph::FindAllAdjacentIn(int vertex, std::vector<int>& vertices) const {
	vertices.clear();
	vertices.reserve(VerticesCount());
	for (int from = 0; from < adjacency_lists.size(); ++from) {
		if (is_vertex_in_list(adjacency_lists[from], vertex)) {
			vertices.push_back(from);
		}
	}
}

void CListGraph::FindAllAdjacentOut(int vertex, std::vector<int>& vertices) const {
	vertices = adjacency_lists[vertex];
}

bool CListGraph::is_vertex_in_list(const std::vector<int>& l, int vertex) const {
	return std::find(l.begin(), l.end(), vertex) != l.end();
}