#include <iostream>
#include <vector>
#include <queue>

//https://contest.yandex.ru/contest/36361/run-report/67605228/

struct Edge {
    int Vertex = 0;
    int Weight = 0;
};

std::vector<int> Dijkstra(const std::vector<std::vector<Edge>>& graph, int start) {
    std::vector<int> distance(graph.size(), INT32_MAX);
    std::vector<bool> visited(graph.size(), false);
    std::priority_queue<std::pair<int, int>,std::vector<std::pair<int,int>>,std::greater<>> que;
    que.push({0, start});
    distance[start]=0;
    while (!que.empty()) {
        int vert = que.top().second;
        que.pop();
        if (visited[vert]) continue;
        visited[vert] = true;
        for (auto elem: graph[vert]) {
            if (distance[vert] + elem.Weight < distance[elem.Vertex]) {
                distance[elem.Vertex] = distance[vert] + elem.Weight;
                que.push({distance[elem.Vertex], elem.Vertex});
            }
        }
    }
    return distance;
}

int main() {
    int v = 0, e = 0;
    std::cin >> v >> e;
    std::vector<std::vector<Edge>> graph(v);
    for (int i = 0; i < e; ++i) {
        int v1 = 0, v2 = 0,weight=0;
        std::cin>>v1>>v2>>weight;
        graph[v1].push_back({v2,weight});
        graph[v2].push_back({v1,weight});
    }
    int s = 0, f = 0;
    std::cin >> s >> f;
    std::cout<<Dijkstra(graph,s)[f];
    return 0;
}
