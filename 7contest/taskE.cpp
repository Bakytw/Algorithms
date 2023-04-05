#include <algorithm>
#include <iostream>
#include <map>
#include <vector>

class Graph {
 private:
  std::vector<int> tin_, ret_;
  std::vector<bool> used_;
  std::vector<std::vector<std::pair<int, int>>> g_;
  int timer_;

 public:
  explicit Graph(int n) : tin_(n), ret_(n), used_(n), g_(n), timer_(0) {}
  void Set(int from, int to, int i) {
    g_[from].emplace_back(to, i);
    g_[to].emplace_back(from, i);
  }
  void Dfs(std::map<std::pair<int, int>, int>& map, std::vector<int>& bridges,
           int v, int p = -1) {
    if (used_[v]) {
      return;
    }
    used_[v] = true;
    tin_[v] = ++timer_;
    ret_[v] = timer_;
    for (size_t i = 0; i < g_[v].size(); ++i) {
      int to = g_[v][i].first;
      if (to == p) {
        continue;
      }
      if (used_[to]) {
        ret_[v] = std::min(ret_[v], tin_[to]);
        continue;
      }
      Dfs(map, bridges, to, v);
      ret_[v] = std::min(ret_[v], ret_[to]);
      if (ret_[to] > tin_[v] && map[{to, v}] < 2) {
        bridges.push_back(g_[v][i].second);
      }
    }
  }
};

int main() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(nullptr);
  std::cout.tie(nullptr);
  int n, m, a, b;
  std::cin >> n >> m;
  Graph graph(n + 1);
  std::map<std::pair<int, int>, int> input;
  for (int i = 1; i <= m; ++i) {
    std::cin >> a >> b;
    graph.Set(a, b, i);
    ++input[{a, b}];
    ++input[{b, a}];
  }
  std::vector<int> bridges;
  for (int i = 1; i <= n; ++i) {
    graph.Dfs(input, bridges, i);
  }
  std::sort(bridges.begin(), bridges.end());
  std::cout << bridges.size() << '\n';
  for (auto i : bridges) {
    std::cout << i << '\n';
  }
  return 0;
}
