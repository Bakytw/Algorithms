/*
 * dp[i][j] - максимальная сумма награды, которую можно получить, если выполнить
 * первые i поручений при ограничении ресурсов в j единиц.
 */
#include <algorithm>
#include <iostream>
#include <vector>

const long long kInf = 1e9;

int main() {
  long long n, s;
  std::cin >> n >> s;
  std::vector<long long> m(n + 1), c(n + 1);
  std::vector<std::vector<long long>> dp(n + 1,
                                         std::vector<long long>(s + 1, -kInf));
  std::vector<std::vector<long long>> prev(n + 1,
                                           std::vector<long long>(s + 1, -1));
  for (long long i = 0; i <= s; ++i) {
    dp[0][i] = 0;
  }
  for (long long elem = 1; elem <= n; elem++) {
    std::cin >> m[elem];
  }
  for (long long elem = 1; elem <= n; elem++) {
    std::cin >> c[elem];
  }
  for (long long elem = 1; elem <= n; elem++) {
    for (long long weight = 0; weight <= s; weight++) {
      dp[elem][weight] = dp[elem - 1][weight];
      prev[elem][weight] = weight;
      if (weight >= m[elem]) {
        if (dp[elem - 1][weight - m[elem]] + c[elem] > dp[elem][weight]) {
          dp[elem][weight] = dp[elem - 1][weight - m[elem]] + c[elem];
          prev[elem][weight] = weight - m[elem];
        }
      }
    }
  }
  long long it = n;
  long long cur_weight = s;
  std::vector<long long> ans_list;
  while (it > 0) {
    if (cur_weight != prev[it][cur_weight]) {
      ans_list.push_back(it);
    }
    cur_weight = prev[it][cur_weight];
    --it;
  }
  std::reverse(ans_list.begin(), ans_list.end());
  for (long long x : ans_list) {
    std::cout << x << '\n';
  }
  return 0;
}
