#include <iostream>
#include <vector>
#include <queue>

//https://contest.yandex.ru/contest/36361/run-report/67905162/

struct Vertex {
    int vert_u;
    int edge_length;
};

struct VertexGreater {
    bool operator()(Vertex &a, Vertex &b) {
        return a.edge_length > b.edge_length;
    }
};

int Prim(const std::vector<std::vector<Vertex>> &graph,const int &n) {
    std::priority_queue<Vertex, std::vector<Vertex>, VertexGreater> que;
    std::vector<bool> visited(n);
    visited[0] = true;
    for (auto elem: graph[0]) {
        if(!visited[elem.vert_u]) {
            que.push(elem);
        }
    }
    int res = 0;
    while (!que.empty()) {
        Vertex top = que.top();
        que.pop();
        if (!visited[top.vert_u]) {
            res += top.edge_length;
            visited[top.vert_u] = true;
            for (auto elem: graph[top.vert_u]) {
                if (!visited[elem.vert_u]) {
                    que.push(elem);
                }
            }
        }
    }
    return res;
}

int main() {
    int n = 0, m = 0;
    std::cin >> n >> m;
    std::vector<std::vector<Vertex>> graph(n);
    for (int i = 0; i < m; ++i) {
        int j = 0, k = 0, l = 0;
        Vertex v;
        std::cin >> j >> k >> l;
        --j;--k;
        v.vert_u=k;
        v.edge_length=l;
        graph[j].push_back(v);
        v.vert_u=j;
        graph[k].push_back(v);
    }
    std::cout << Prim(graph, n);
    return 0;
}
