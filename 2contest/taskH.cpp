#include <iostream>
#include <vector>

using std::swap;

int Partition(std::vector<int>& a, int l, int r, int pivot) {
  swap(a[(l + r) / 2], a[r]);
  int i = l, j = r - 1;
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

void QuickSort(std::vector<int>& a, int l, int r) {
  if (r - l <= 0) {
    return;
  }
  int pivot_place = Partition(a, l, r, a[(l + r) / 2]);
  int i = pivot_place - 1, j = pivot_place + 1;
  while (i >= l && a[pivot_place] == a[i]) {
    --i;
  }
  while (j <= r && a[pivot_place] == a[j]) {
    ++j;
  }
  QuickSort(a, l, i);
  QuickSort(a, j, r);
}

int main() {
  int n;
  std::cin >> n;
  std::vector<int> a(n);
  for (int i = 0; i < n; ++i) {
    std::cin >> a[i];
  }
  QuickSort(a, 0, n - 1);
  for (int i = 0; i < n; ++i) {
    std::cout << a[i] << ' ';
  }
  return 0;
}
