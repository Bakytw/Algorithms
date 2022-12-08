#include <algorithm>
#include <iostream>
#include <vector>

using Ll = long long;

struct PairsOfMins {
  Ll first_stat, second_stat;
  PairsOfMins(Ll first_stat, Ll second_stat)
      : first_stat(first_stat), second_stat(second_stat) {}
};

PairsOfMins MinPair(PairsOfMins one, PairsOfMins two);

class SparseTable {
 private:
  std::vector<size_t> log_;
  std::vector<std::vector<PairsOfMins>> sparse_;

 public:
  explicit SparseTable(const std::vector<Ll>& a);
  Ll Get(size_t l, size_t r);
};

int main() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(nullptr);
  std::cout.tie(nullptr);
  size_t n, m;
  std::cin >> n >> m;
  std::vector<Ll> sequence(n);
  for (size_t i = 0; i < n; ++i) {
    std::cin >> sequence[i];
  }
  SparseTable st(sequence);
  for (size_t i = 0; i < m; ++i) {
    Ll l, r;
    std::cin >> l >> r;
    std::cout << st.Get(l - 1, r - 1) << '\n';
  }
  return 0;
}

PairsOfMins MinPair(PairsOfMins one, PairsOfMins two) {
  std::vector<Ll> temp{one.first_stat, one.second_stat, two.first_stat,
                       two.second_stat};
  std::sort(temp.begin(), temp.end());
  temp.resize(std::unique(temp.begin(), temp.end()) - temp.begin());
  if (temp.size() > 1) {
    for (size_t i = 0; i < temp.size(); ++i) {
      if (temp[i] != temp[0]) {
        return {temp[0], temp[i]};
      }
    }
  }
  return {temp[0], temp[0]};
}

SparseTable::SparseTable(const std::vector<Ll>& a) {
  size_t n = a.size();
  log_.resize(n + 1);
  log_[1] = 0;
  for (size_t i = 2; i < n + 1; ++i) {
    log_[i] = log_[i - 1];
    if ((i & (i - 1)) == 0) {
      ++log_[i];
    }
  }
  sparse_.resize(log_[n] + 1);
  for (size_t i = 0; i < log_[n] + 1; ++i) {
    sparse_[i].resize(n, {0, 0});
  }
  for (size_t i = 0; i < n; ++i) {
    sparse_[0][i] = PairsOfMins(a[i], a[i]);
  }
  for (size_t k = 0; k < log_[n]; ++k) {
    for (size_t i = 0; i < n; ++i) {
      size_t j = i + (1 << k);
      if (j < n) {
        sparse_[k + 1][i] = MinPair(sparse_[k][i], sparse_[k][j]);
      }
    }
  }
}

Ll SparseTable::Get(size_t l, size_t r) {
  size_t k = log_[r - l + 1];
  return MinPair(sparse_[k][l], sparse_[k][r - (1 << k) + 1]).second_stat;
}
