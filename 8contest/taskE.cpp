#include <iostream>
#include <vector>

const int kNotedge = 100000;

struct Edge {
  int from;
  int to;
  int cost;
};

bool NegativeCycle(int nn, std::vector<int>& dists,
                   const std::vector<Edge>& edges, std::vector<int>& parents) {
  int iter = -1;
  for (int i = 0; i < nn; ++i) {
    iter = -1;
    for (const auto& edge : edges) {
      if (dists[edge.to] > dists[edge.from] + edge.cost) {
        dists[edge.to] = dists[edge.from] + edge.cost;
        parents[edge.to] = edge.from;
        iter = edge.to;
      }
    }
  }
  if (iter == -1) {
    return false;
  }
  for (int i = 0; i < nn; ++i) {
    iter = parents[iter];
  }
  std::vector<int> path;
  int current = iter;
  while (true) {
    path.push_back(current);
    if (current == iter && path.size() > 1) {
      break;
    }
    current = parents[current];
  }
  std::reverse(path.begin(), path.end());
  std::cout << "YES\n" << path.size() << '\n';
  for (int vert : path) {
    std::cout << vert + 1 << ' ';
  }
  return true;
}

void Build(int nn, std::vector<Edge>& edges) {
  for (int i = 0; i < nn; ++i) {
    for (int j = 0; j < nn; ++j) {
      int cost;
      std::cin >> cost;
      if (cost == kNotedge) {
        continue;
      }
      edges.push_back({i, j, cost});
    }
  }
}

int main() {
  int nn;
  std::cin >> nn;
  std::vector<Edge> edges;
  std::vector<int> dists(nn, 0);
  std::vector<int> parents(nn, -1);
  Build(nn, edges);
  std::vector<int> negative;
  if (!NegativeCycle(nn, dists, edges, parents)) {
    std::cout << "NO\n";
  }
  return 0;
}
