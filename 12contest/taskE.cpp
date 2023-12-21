#include <iostream>

long long ModPow(long long xx, long long deg, long long mod) {
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

long long QuadraticNonresidue(long long pp) {
  long long ii;
  for (ii = 2; ii <= pp; ++ii) {
    if (ModPow(ii, (pp - 1) / 2, pp) == pp - 1) {
      break;
    }
  }
  return ii;
}

long long SquareRoot(long long aa, long long pp) {
  if (ModPow(aa, (pp - 1) / 2, pp) == pp - 1 && pp > 2 && aa > 0) {
    return -1;
  }
  long long ss = 0;
  long long qq = pp - 1;
  while ((qq & 1) == 0 && qq > 1) {
    qq >>= 1;
    ++ss;
  }
  if (ss == 1) {
    return ModPow(aa, (pp + 1) / 4, pp);
  }
  long long zz = QuadraticNonresidue(pp);
  long long cc = ModPow(zz, qq, pp);
  long long rr = ModPow(aa, (qq + 1) / 2, pp);
  long long tt = ModPow(aa, qq, pp);
  long long mm = ss;
  while (tt != 1) {
    long long temp = tt;
    long long ii;
    for (ii = 0; temp != 1; ++ii) {
      temp = (temp * temp) % pp;
      if (ii == mm) {
        return 0;
      }
    }
    long long bb = ModPow(cc, ModPow(2, mm - ii - 1, pp - 1), pp);
    long long b2 = (bb * bb) % pp;
    rr = (rr * bb) % pp;
    tt = (tt * b2) % pp;
    cc = b2;
    mm = ii;
  }
  return rr;
}

int main() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(nullptr);
  int tt;
  std::cin >> tt;
  long long aa;
  long long pp;
  for (int i = 0; i < tt; ++i) {
    std::cin >> aa >> pp;
    long long ans = SquareRoot(aa, pp);
    if (ans == -1) {
      std::cout << "IMPOSSIBLE\n";
    } else {
      std::cout << ans << '\n';
    }
  }
  return 0;
}
