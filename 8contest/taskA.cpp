#include <iostream>
#include <queue>
#include <vector>

const int kInf = 2009000999;

struct Edge {
  int to;
  int cost;
};

std::vector<int> Dijkstra(int start, int nn,
                          const std::vector<std::vector<Edge>>& graph) {
  std::priority_queue<std::pair<int, int>, std::vector<std::pair<int, int>>,
                      std::greater<>>
      heap;
  std::vector<int> dist(nn, kInf);
  dist[start] = 0;
  heap.emplace(0, start);
  while (!heap.empty()) {
    int vert = heap.top().second;
    heap.pop();
    for (auto edge : graph[vert]) {
      if (dist[vert] + edge.cost < dist[edge.to]) {
        dist[edge.to] = dist[vert] + edge.cost;
        heap.emplace(dist[edge.to], edge.to);
      }
    }
  }
  return dist;
}

void Build(int nn, int mm, std::vector<std::vector<Edge>>& graph) {
  int uu;
  int vv;
  int cost;
  graph.assign(nn, std::vector<Edge>());
  for (int j = 0; j < mm; ++j) {
    std::cin >> uu >> vv >> cost;
    graph[uu].push_back({vv, cost});
    graph[vv].push_back({uu, cost});
  }
}

void Output(int nn, std::vector<int> dist) {
  for (int j = 0; j < nn; ++j) {
    if (dist[j] == kInf) {
      std::cout << kInf << ' ';
    } else {
      std::cout << dist[j] << ' ';
    }
  }
  std::cout << '\n';
}

int main() {
  int kk;
  int nn;
  int mm;
  int start;
  std::vector<std::vector<Edge>> graph;
  std::cin >> kk;
  for (int i = 0; i < kk; ++i) {
    std::cin >> nn >> mm;
    Build(nn, mm, graph);
    std::cin >> start;
    Output(nn, Dijkstra(start, nn, graph));
  }
  return 0;
}
