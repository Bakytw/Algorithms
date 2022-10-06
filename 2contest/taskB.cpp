#include <iostream>
#include <vector>

using std::swap;

long long Partition(std::vector<long long>& a, long long l, long long r,
                    long long pivot) {
  swap(a[(l + r) / 2], a[r]);
  long long i = l, j = r - 1;
  while (i <= j) {
    if (a[i] > pivot) {
      swap(a[i], a[j]);
      --j;
    } else {
      ++i;
    }
  }
  swap(a[i], a[r]);
  return i;
}

long long QuickSelect(std::vector<long long>& a, long long l, long long r,
                      long long k) {
  if (r - l <= 0) {
    return a[l];
  }
  long long pivot = a[(l + r) / 2];
  long long pivot_place = Partition(a, l, r, pivot);
  long long i = pivot_place - 1, j = pivot_place + 1;
  while (i >= l && a[pivot_place] == a[i]) {
    --i;
  }
  while (j <= r && a[pivot_place] == a[j]) {
    ++j;
  }

  if (k <= i - l + 1) {
    return QuickSelect(a, l, i, k);
  }
  if (k <= j - l) {
    return pivot;
  }
  return QuickSelect(a, j, r, k - (j - l));
}

int main() {
  long long n, k, first, second;
  std::cin >> n >> k >> first >> second;
  std::vector<long long> a(n);
  a[0] = first;
  a[1] = second;
  for (long long i = 2; i < n; ++i) {
    a[i] = (a[i - 1] * 123 + a[i - 2] * 45) % 10004321;
  }
  std::cout << QuickSelect(a, 0, n - 1, k);
  return 0;
}
