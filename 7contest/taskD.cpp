#include <iostream>
#include <vector>

void TopologicalSort(int v, const std::vector<std::vector<int>>& g,
                     std::vector<bool>& used, std::vector<int>& top_sort) {
  used[v] = true;
  for (auto u : g[v]) {
    if (!used[u]) {
      TopologicalSort(u, g, used, top_sort);
    }
  }
  top_sort.push_back(v);
}

void ConnectedComponents(int v, int c, const std::vector<std::vector<int>>& g,
                         std::vector<bool>& used, std::vector<int>& comp) {
  used[v] = true;
  comp[v] = c;
  for (auto u : g[v]) {
    if (!used[u]) {
      ConnectedComponents(u, c, g, used, comp);
    }
  }
}

void BuildGraphComponents(int n, int m, int& count, std::vector<int>& comp) {
  int a, b;
  std::vector<int> top_sort;
  std::vector<std::vector<int>> g1(n + 1);
  std::vector<std::vector<int>> g2(n + 1);
  std::vector<bool> used(n + 1, false);
  for (int i = 0; i < m; i++) {
    std::cin >> a >> b;
    g1[a].push_back(b);
    g2[b].push_back(a);
  }
  for (int u = 1; u <= n; ++u) {
    if (!used[u]) {
      TopologicalSort(u, g1, used, top_sort);
    }
  }
  used.assign(n, false);
  while (!top_sort.empty()) {
    int u = top_sort.back();
    top_sort.pop_back();
    if (!used[u]) {
      ConnectedComponents(u, ++count, g2, used, comp);
    }
  }
}

int main() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(nullptr);
  std::cout.tie(nullptr);
  int n, m, c = 0;
  std::cin >> n >> m;
  std::vector<int> comp(n + 1);
  BuildGraphComponents(n, m, c, comp);
  std::cout << c << '\n';
  for (int u = 1; u <= n; ++u) {
    std::cout << comp[u] << ' ';
  }
  return 0;
}
