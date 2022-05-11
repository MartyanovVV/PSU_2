#include <iostream>
#include <vector>
#include <set>
#include <limits>

//https://contest.yandex.ru/contest/36361/run-report/68332151/

struct Edge {
    int Vertex = 0;
    int Weight = 0;
};

int Dijkstra(const std::vector<std::vector<Edge>>& graph, int s, int f) {
                               
  std::vector<int> distance(graph.size(), std::numeric_limits<int>::max());
  std::set<std::pair<int, int>> q;

  q.insert({0, s});
  distance[s] = 0;
  while (!q.empty()) {
    auto it = q.begin();
    int u = it->second;
    q.erase(it);
 
    for (auto e : graph[u]) {
      int v = e.Vertex;
      if (distance[u] + e.Weight < distance[v]) {
        auto it_v = q.find({distance[v], v});
      if (it_v != q.end()) {
      	q.erase(it_v);
      }
 
        distance[v] = distance[u] + e.Weight;
        q.insert({distance[v], v});
      }
    }
  }
  return distance[f];
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
    std::cout << Dijkstra(graph,s,f);
    return 0;
}
