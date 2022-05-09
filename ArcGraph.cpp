#include "ArcGraph.h"

CArcGraph::CArcGraph(IGraph* other) {
	verticesCount = (*other).VerticesCount();
	from_to_list.clear();
	for (int i = 0; i < (*other).VerticesCount(); ++i) {
		std::vector<int> neighbours;
		(*other).FindAllAdjacentOut(i, neighbours);
		for (int to : neighbours) {
			from_to_list.push_back({ i, to });
		}
	}
}

void CArcGraph::AddEdge(int from, int to) {
	from_to_list.push_back({ from, to });
}

int CArcGraph::VerticesCount() const {
	return verticesCount;
}

void CArcGraph::FindAllAdjacentIn(int vertex, std::vector<int>& vertices) const {
	vertices.clear();
	vertices.reserve(VerticesCount());
	for (const auto& edge : from_to_list) {
		if (edge.second == vertex) {
			vertices.push_back(edge.first);
		}
	}
}

void CArcGraph::FindAllAdjacentOut(int vertex, std::vector<int>& vertices) const {
	vertices.clear();
	vertices.reserve(VerticesCount());
	for (const auto& edge : from_to_list) {
		if (edge.first == vertex) {
			vertices.push_back(edge.second);
		}
	}
}
