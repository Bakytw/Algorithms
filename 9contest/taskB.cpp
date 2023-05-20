#include <algorithm>
#include <iostream>
#include <vector>

struct DSU {
  std::vector<size_t> rank;
  std::vector<size_t> pr;

  DSU(size_t count) {
    rank.resize(count, 1);
    pr.resize(count);
    for (size_t i = 0; i < count; ++i) {
      pr[i] = i;
    }
  }

  size_t Get(size_t element) {
    if (pr[element] == element) {
      return element;
    }
    return pr[element] = Get(pr[element]);
  }

  void Unite(size_t first, size_t second) {
    first = Get(first);
    second = Get(second);
    if (first == second) {
      return;
    }
    if (rank[first] < rank[second]) {
      std::swap(first, second);
    }
    pr[second] = first;
    rank[first] += rank[second];
  }
};

int main() {
  size_t nn, mm;
  std::cin >> nn >> mm;
  DSU dsu(nn);
  std::vector<std::pair<size_t, std::pair<size_t, size_t>>> queries;
  for (size_t i = 0; i < mm; ++i) {
    size_t e, b, w;
    std::cin >> e >> b >> w;
    queries.push_back({w, {e - 1, b - 1}});
  }
  size_t ans = 0;
  sort(queries.begin(), queries.end());
  for (const auto &i : queries) {
    if (dsu.Get(i.second.first) == dsu.Get(i.second.second)) {
      continue;
    }
    ans += i.first;
    dsu.Unite(i.second.first, i.second.second);
  }
  std::cout << ans;
  return 0;
}
