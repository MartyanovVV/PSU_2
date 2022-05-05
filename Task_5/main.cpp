#include <iostream>
#include <vector>
#include <queue>

//https://contest.yandex.ru/contest/36361/run-report/67756460/

std::vector<int> vertex_rate(std::vector<std::vector<double>> &graph, int &n, int &v) {
    std::vector<int> result;
    for (int i = 0; i < n; ++i) {
        if (graph[v][i] != -1)
            result.push_back(i);
    }
    return result;
}

struct PairGreater {
    bool operator()(std::pair<int, int> &a, std::pair<int, int> &b) {
        return a.second < b.second;
    }
};

bool trade_arbitrage(std::vector<std::vector<double>> &graph, int &n) {
    for (int i = 0; i < n; ++i) {
        std::vector<double> trade(n, 1);
        std::priority_queue<std::pair<int, int>, std::vector<std::pair<int, int>>, PairGreater> rate;
        rate.push(std::pair<int, int>(i, 1));
        while (!rate.empty()) {
            auto top = rate.top();
            rate.pop();
            if (i == top.first && trade[i] > 1) return true;
            std::vector<int> list_vertex = vertex_rate(graph, n, top.first);
            for (auto v: list_vertex) {
                double new_trade = trade[top.first] * graph[top.first][v];
                if (new_trade > trade[v]) {
                    trade[v] = new_trade;
                    rate.push(std::pair<int, int>(v, trade[v]));
                }
            }
        }
    }
    return false;
}

int main() {
    int n;
    std::cin >> n;
    std::vector<std::vector<double>> matr(n, std::vector<double>(n, -1));
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            if (i != j) {
                std::cin >> matr[i][j];
            }
        }
    }
    if (trade_arbitrage(matr, n)) {
        std::cout << "YES" << std::endl;
    } else {
        std::cout << "NO" << std::endl;
    }
    return 0;
}
