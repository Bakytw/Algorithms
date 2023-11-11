#include <cmath>
#include <iostream>
#include <unordered_set>

long long Pow(long long xx, long long deg, long long mod) {
  long long result = 1;
  while (deg != 0) {
    if (deg % 2 == 0) {
      deg /= 2;
      xx = (xx * xx + mod) % mod;
    } else {
      --deg;
      result = (result * xx + mod) % mod;
    }
  }
  return result;
}

long long DiscreteLog(long long mm, long long base, long long value,
                      std::unordered_set<long long>& setik) {
  auto kk = static_cast<int>(std::sqrt(mm));
  long long temp = 1;
  long long gk = base;
  for (int i = 0; i < kk; ++i) {
    setik.insert(temp);
    temp = (temp * base) % mm;
    if (i != kk - 1) {
      gk = (gk * base) % mm;
    }
  }
  gk = Pow(gk, mm - 2, mm);
  for (int i = 0; i <= kk; ++i) {
    if (setik.count(value) == 1) {
      temp = 1;
      long long jj;
      for (jj = 0; temp != value; ++jj) {
        temp = (temp * base) % mm;
      }
      return i * kk + jj;
    }
    value = (value * gk) % mm;
  }
  return -1;
}

int main() {
  std::unordered_set<long long> setik;
  long long pp;
  long long bb;
  long long nn;
  while (std::cin >> pp >> bb >> nn) {
    long long ans = DiscreteLog(pp, bb, nn, setik);
    if (ans == -1) {
      std::cout << "no solution\n";
    } else {
      std::cout << ans << '\n';
    }
    setik.clear();
  }
  return 0;
}
