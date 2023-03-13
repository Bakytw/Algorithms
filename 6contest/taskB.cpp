/*
 * dp[i] - наименьшее число, на которое заканчивается невозразрастающая
 * последовательность длины i
 */
#include <algorithm>
#include <iostream>
#include <vector>

const long long kInf = 1e10;

void DpBuild(std::vector<long long>& dp, std::vector<long long>& pos,
             std::vector<long long>& prev, const std::vector<long long>& a,
             long long n);
int main() {
  long long n, ans = -1, it = -1;
  std::cin >> n;
  std::vector<long long> a(n);
  for (long long i = 0; i < n; ++i) {
    std::cin >> a[i];
    a[i] *= -1;
  }
  std::vector<long long> dp(n + 1, kInf);
  std::vector<long long> pos(n + 1, -1);
  std::vector<long long> prev(n + 1, -1);
  DpBuild(dp, pos, prev, a, n);
  for (long long i = 0; i < n + 1; ++i) {
    if (dp[i] < kInf) {
      ans = i;
      it = i;
    }
  }
  std::cout << ans << '\n';
  it = pos[it];
  std::vector<long long> ans_list;
  while (it != -1) {
    ans_list.push_back(it);
    it = prev[it];
  }
  reverse(ans_list.begin(), ans_list.end());
  for (long long x : ans_list) {
    std::cout << x + 1 << ' ';
  }
  std::cout << '\n';
  return 0;
}

void DpBuild(std::vector<long long>& dp, std::vector<long long>& pos,
             std::vector<long long>& prev, const std::vector<long long>& a,
             long long n) {
  dp[0] = -kInf;
  for (long long i = 0; i < n; ++i) {
    auto temp = upper_bound(dp.begin(), dp.end(), a[i]) - dp.begin();
    dp[temp] = a[i];
    pos[temp] = i;
    prev[i] = pos[temp - 1];
  }
}
