#include <cmath>
#include <iomanip>
#include <iostream>

int main() {
  int n, q, l, r;
  std::cin >> n;
  long double* a = new long double[n];
  long double* mult = new long double[n];
  for (int i = 0; i < n; ++i) {
    std::cin >> a[i];
    if (i == 0) {
      mult[0] = pow(a[0], 1 / static_cast<long double>(n));
    } else {
      mult[i] = mult[i - 1] * pow(a[i], 1 / static_cast<long double>(n));
    }
  }
  std::cin >> q;
  for (int i = 0; i < q; ++i) {
    std::cin >> l >> r;
    if (l == 0) {
      std::cout << std::setprecision(6) << std::fixed
                << pow(mult[r], n / static_cast<long double>(r + 1))
                << std::endl;
    } else {
      std::cout << std::setprecision(6) << std::fixed
                << pow(mult[r] / mult[l - 1],
                       n / static_cast<long double>(r - l + 1))
                << std::endl;
    }
  }
  delete[] a;
  delete[] mult;
  return 0;
}
