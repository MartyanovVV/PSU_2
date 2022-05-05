#include <iostream>
#include <vector>
#include <queue>

//https://contest.yandex.ru/contest/36361/run-report/68003766/

unsigned int BFS(const std::vector<std::vector<unsigned int>> &graph, unsigned int &n, unsigned int &s, unsigned int &f) {
    std::vector<int> distance(n, -1);
    distance[s] = 0;
    std::vector<unsigned int> count_ways_mindistance(n);
    count_ways_mindistance[s] = 1;
    std::queue<unsigned int> que;
    que.push(s);
    while (!que.empty()) {
        unsigned int v = que.front();
        que.pop();
        for (int u: graph[v]) {
            if (distance[u] < 0) {
                que.push(u);
                distance[u] = distance[v] + 1;
            }
            if (distance[u] > distance[v]) {
                count_ways_mindistance[u] += count_ways_mindistance[v];
            }
        }
    }
    return count_ways_mindistance[f];
}

int main() {
    unsigned int n = 0, m = 0;
    std::cin >> n >> m;
    std::vector<std::vector<unsigned int>> graph(n);
    for (int i = 0; i < m; ++i) {
        int v, u;
        std::cin >> v >> u;
        graph[v].push_back(u);
        graph[u].push_back(v);
    }
    unsigned int s = 0, f = 0;
    std::cin >> s >> f;
    std::cout << BFS(graph, n, s, f);
    return 0;
}
