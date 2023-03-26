#include <iostream>
#include <vector>

void Dfs1(int v, const std::vector<std::vector<int>>& g,
          std::vector<bool>& used, std::vector<int>& top_sort) {
  used[v] = true;
  for (auto u : g[v]) {
    if (!used[u]) {
      Dfs1(u, g, used, top_sort);
    }
  }
  top_sort.push_back(v);
}

void Dfs2(int v, int c, const std::vector<std::vector<int>>& g,
          std::vector<bool>& used, std::vector<int>& comp) {
  used[v] = true;
  comp[v] = c;
  for (auto u : g[v]) {
    if (!used[u]) {
      Dfs2(u, c, g, used, comp);
    }
  }
}

int main() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(nullptr);
  std::cout.tie(nullptr);
  int n, m, a, b;
  std::cin >> n >> m;
  std::vector<bool> used(n + 1, false);
  std::vector<std::vector<int>> g1(n + 1);
  std::vector<std::vector<int>> g2(n + 1);
  std::vector<int> comp(n + 1);
  std::vector<int> top_sort;
  for (int i = 0; i < m; i++) {
    std::cin >> a >> b;
    g1[a].push_back(b);
    g2[b].push_back(a);
  }
  for (int u = 1; u <= n; ++u) {
    if (!used[u]) {
      Dfs1(u, g1, used, top_sort);
    }
  }
  used.assign(n, false);
  int c = 0;
  while (!top_sort.empty()) {
    int u = top_sort.back();
    top_sort.pop_back();
    if (!used[u]) {
      Dfs2(u, ++c, g2, used, comp);
    }
  }
  std::cout << c << '\n';
  for (int u = 1; u <= n; ++u) {
    std::cout << comp[u] << ' ';
  }
  return 0;
}
