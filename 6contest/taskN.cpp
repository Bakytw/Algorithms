/*
 * dp[i][j][h] - минимальное расстояние редактирования между подстроками s[1:i]
 * и t[1:j] при условии, что было сделано не более h операций
 */
#include <iostream>
#include <vector>

const long long kInf = 1e18;

int main() {
  std::string s, t;
  long long k;
  std::cin >> s >> t;
  std::cin >> k;
  auto n = static_cast<long long>(s.size()),
       m = static_cast<long long>(t.size());
  s.insert(s.begin(), '$');
  t.insert(t.begin(), '$');
  std::vector<std::vector<std::vector<long long>>> dp(
      n + 1, std::vector<std::vector<long long>>(
                 m + 1, std::vector<long long>(k + 1, kInf)));
  dp[0][0][0] = 0;
  for (long long i = 0; i <= k; ++i) {
    if (i >= n) {
      break;
    }
    dp[i][0][i] = i;
  }
  for (long long i = 0; i <= k; ++i) {
    if (i >= m) {
      break;
    }
    dp[0][i][i] = i;
  }
  for (long long i = 1; i <= n; ++i) {
    for (long long j = 1; j <= m; ++j) {
      for (long long h = 0; h <= k; ++h) {
        if (s[i] == t[j]) {
          dp[i][j][h] = dp[i - 1][j - 1][h];
        } else {
          dp[i][j][h] = std::min(dp[i][j][h], dp[i - 1][j - 1][h] + 1);
          if (h > 0) {
            dp[i][j][h] = std::min(dp[i][j][h], dp[i - 1][j][h - 1] + 1);
            dp[i][j][h] = std::min(dp[i][j][h], dp[i][j - 1][h - 1] + 1);
          }
        }
      }
    }
  }
  long long ans = kInf;
  for (long long i = 0; i <= k; ++i) {
    ans = std::min(ans, std::max(dp[n][m][i] - k, 0LL));
  }
  if (ans < kInf / 2) {
    std::cout << ans << '\n';
  } else {
    std::cout << -1 << '\n';
  }
  return 0;
}
