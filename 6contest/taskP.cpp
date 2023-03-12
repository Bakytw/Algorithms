/*
 * dp[i][j] - количество способов распределения районов в первых i+1
 * столбцах, если последний столбец был заполнен с учетом битовой маски j
 */
#include <iostream>
#include <vector>

const long long kMod = 1000000007;

int main() {
  long long n, m, t;
  std::cin >> n >> m;
  t = 1 << n;
  std::vector<std::vector<char>> input(n, std::vector<char>(m));
  std::vector<std::pair<long long, long long>> defence(m,
                                                       std::make_pair(-1, 0));
  std::vector<std::vector<long long>> dp(m, std::vector<long long>((1 << n)));
  for (long long i = 0; i < n; ++i) {
    for (long long j = 0; j < m; ++j) {
      std::cin >> input[i][j];
    }
  }
  for (long long i = 0; i < m; ++i) {
    for (long long j = 0; j < n; ++j) {
      switch (input[j][i]) {
        case '-':
          defence[i].first &= ~(1 << j);
          break;
        case '+':
          defence[i].second |= 1 << j;
          break;
        default:
          break;
      }
    }
  }
  for (long long i = 0; i < 1 << n; ++i) {
    dp[0][(i | defence[0].second) & defence[0].first] = 1;
  }
  for (long long i = 1; i < m; ++i) {
    for (long long j = 0; j < t; ++j) {
      bool flag = true;
      long long mask = (j | defence[i].second) & defence[i].first;
      for (long long k = 0; k < n - 1; ++k) {
        if ((mask & 1) == (((mask >> 1) & 1))) {
          flag = false;
          break;
        }
        mask >>= 1;
      }
      if (flag) {
        dp[i][(j | defence[i].second) & defence[i].first] =
            (dp[i - 1][(j | defence[i].second) & defence[i].first] +
             dp[i - 1]
               [((j | defence[i].second) & defence[i].first) ^ (t - 1)]) %
            kMod;
      } else {
        dp[i][(j | defence[i].second) & defence[i].first] =
            dp[i - 1][((j | defence[i].second) & defence[i].first) ^ (t - 1)];
      }
    }
  }
  long long ans = 0;
  for (long long i = 0; i < t; ++i) {
    ans += dp[m - 1][i] % kMod;
    ans %= kMod;
  }
  std::cout << ans;
  return 0;
}
