/*
 * dp[i][j] - количество способов выбрать j элементов из i элементов без
 * повторений
 */
#include <iostream>
#include <vector>

int NumberOfCombinations(int i, int j, std::vector<std::vector<int>>& dp) {
  if (i == 0 || j == 0 || i == j) {
    return dp[i][j] = 1;
  }
  if (j == 1) {
    return dp[i][j] = i;
  }
  if (dp[i - 1][j] > 0) {
    dp[i][j] = dp[i - 1][j];
  } else {
    dp[i][j] = NumberOfCombinations(i - 1, j, dp);
  }
  if (dp[i - 1][j - 1] > 0) {
    dp[i][j] += dp[i - 1][j - 1];
  } else {
    dp[i][j] += NumberOfCombinations(i - 1, j - 1, dp);
  }
  return dp[i][j];
}

int main() {
  int n, k, ans = -1;
  std::cin >> n >> k;
  std::vector<std::vector<int>> dp(n + 1,
                                   std::vector<int>(std::min(k, 30) + 1, 0));
  for (int i = 0; i <= n; ++i) {
    int sum = 0;
    for (int j = 0; j <= i && j <= std::min(k, 30); ++j) {
      sum += NumberOfCombinations(i, j, dp);
    }
    if (sum >= n) {
      ans = i;
      break;
    }
  }
  std::cout << ans;
  return 0;
}
