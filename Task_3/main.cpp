#include <iostream>
#include <vector>
#include <algorithm>

//https://contest.yandex.ru/contest/36361/run-report/68018912/

void TimeDFS(const std::vector<std::vector<int>> &graph, int &v, std::vector<int> &time, std::vector<bool> &visited) {
    //Dfs с заполнением времени выхода вершин из Dfs
    static int t = 0;
    visited[v] = true;
    for (int u: graph[v]) {
        if (!visited[u]) {
            TimeDFS(graph, u, time, visited);
        }
    }
    time[v] = ++t;
}

void DFS(const std::vector<std::vector<int>> &graph, int &v, std::vector<bool> &visited, int &component,
         std::vector<int> &components) {
    visited[v] = true;
    components[v] = component;
    for (int u: graph[v]) {
        if (!visited[u]) {
            DFS(graph, u, visited, component, components);
        }
    }
}

int MainDFS(const std::vector<std::vector<int>> &graph, std::vector<int> &time, int &n, std::vector<int> &components) {
    std::vector<std::pair<int, int>> time_vertex;
    //заполнение и сортировка пар {время выходы вершины из Dfs; номер вершины}
    for (int i = 0; i < n; ++i) {
        std::pair<int, int> p{time[i], i};
        time_vertex.push_back(p);
    }

    std::sort(time_vertex.begin(), time_vertex.end(), [&time_vertex](std::pair<int, int> &a1, std::pair<int, int> &a2) {
        return a1.first > a2.first;
    });

    //вызов Dfs для графа по убыванию времены выходы вершин в Dfs инвертированного графа
    std::vector<bool> visited(n);
    int component = 0;
    for (int i=0;i<n;++i) {
        if (!visited[time_vertex[i].second]) {
            DFS(graph, time_vertex[i].second, visited, component, components);
            ++component;
        }
    }
    return component;
}

void Kasaray(const std::vector<std::vector<int>> &graph, const std::vector<std::vector<int>> &invert_graph, int &n, std::vector<int> &components, int &component) {
    std::vector<bool> visited(n);
    std::vector<int> time(n);
    for (int i = 0; i < n; ++i) {
        if (!visited[i]) {
            TimeDFS(invert_graph, i, time, visited);
        }
    }
    component = MainDFS(graph, time, n, components);
}

std::vector<std::vector<int>> MakeCondensationGraph(const std::vector<int> &components, const std::vector<std::vector<int>> &graph, int &n, int &component) {
    //конденсация графа
    std::vector<std::vector<int>> cond_graph(component);
    for (int i = 0; i < n; ++i) {
        std::vector<bool> visited(component);
        for (int u: graph[i]) {
            if (!visited[u] && components[u] != components[i]) {
                visited[components[u]] = true;
                cond_graph[components[i]].push_back(components[u]);
            }
        }
    }
    return cond_graph;
}

int MinCountTillConnected(std::vector<std::vector<int>> &graph, const std::vector<std::vector<int>> &invert_graph, int &n) {
    int component = 0;
    std::vector<int> components(n);
    Kasaray(graph, invert_graph, n, components, component);
    std::vector<std::vector<int>> condensation_graph = MakeCondensationGraph(components, graph, n, component);
    std::vector<std::vector<int>> condensation_invert_graph = MakeCondensationGraph(components, invert_graph, n,component);

    int count_graph = 0, count_invert_graph = 0;
    if (component == 1) { return 0; }
    for (int i = 0; i < component; ++i) {
        if (condensation_graph[i].empty()) ++count_graph;
    }
    for (int i = 0; i < component; ++i) {
        if (condensation_invert_graph[i].empty()) ++count_invert_graph;
    }
    return std::max(count_graph, count_invert_graph);
}

int main() {
    int n = 0, m = 0;
    std::cin >> n >> m;
    std::vector<std::vector<int>> graph(n);
    std::vector<std::vector<int>> invert_graph(n);
    for (int i = 0; i < m; ++i) {
        int v = 0, u = 0;
        std::cin >> v >> u;
        graph[--v].push_back(--u);
        invert_graph[u].push_back(v);
    }
    std::cout << MinCountTillConnected(graph, invert_graph, n);
    return 0;
}
