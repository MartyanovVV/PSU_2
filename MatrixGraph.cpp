#include "MatrixGraph.h"

CMatrixGraph::CMatrixGraph(IGraph* other) {
	adjacency_matrix.clear();
	adjacency_matrix.resize((*other).VerticesCount());
	for (int i = 0; i < (*other).VerticesCount(); ++i) {
		std::vector<int> neighbours;
		(*other).FindAllAdjacentOut(i, neighbours);
		adjacency_matrix[i] = neighbours;
	}
}

void CMatrixGraph::AddEdge(int from, int to) {
	assert(from != to);
	adjacency_matrix[from][to] = 1;
}

int CMatrixGraph::VerticesCount() const {
	return static_cast<int>(adjacency_matrix.size());
}

void CMatrixGraph::FindAllAdjacentIn(int vertex, std::vector<int>& vertices) const {
	vertices.clear();
	vertices.reserve(VerticesCount());
	for (int i = 0; i < VerticesCount(); ++i) {
		if (adjacency_matrix[i][vertex] == 1) {
			vertices.push_back(adjacency_matrix[i][vertex]);
		}
	}
}

void CMatrixGraph::FindAllAdjacentOut(int vertex, std::vector<int>& vertices) const {
	vertices.clear();
	vertices.reserve(VerticesCount());
	for (int i = 0; i < VerticesCount(); ++i) {
		if (adjacency_matrix[vertex][i] == 1) {
			vertices.push_back(adjacency_matrix[vertex][i]);
		}
	}
}

