#include <iostream>

void RadixSort(short byte, long long n, const long long* p_int, long long* to) {
  int count[256] = {0};
  int index[256] = {0};
  for (long long i = 0; i < n; ++i) {
    count[((p_int[i]) >> (byte * 8)) & 255]++;
  }
  for (long long i = 1; i < 256; ++i) {
    index[i] = index[i - 1] + count[i - 1];
  }
  for (long long i = 0; i < n; ++i) {
    to[index[((p_int[i]) >> (byte * 8)) & 255]++] = p_int[i];
  }
}

void FastSort(long long* begin, const long long* end) {
  long long n = (end - begin);
  long long* tmp = new long long[n];
  RadixSort(0, n, begin, tmp);
  RadixSort(1, n, tmp, begin);
  RadixSort(2, n, begin, tmp);
  RadixSort(3, n, tmp, begin);
  RadixSort(4, n, begin, tmp);
  RadixSort(5, n, tmp, begin);
  RadixSort(6, n, begin, tmp);
  RadixSort(7, n, tmp, begin);
  delete[] tmp;
}

int main() {
  int n;
  std::cin >> n;
  long long* array = new long long[n];
  for (long long i = 0; i < n; ++i) {
    std::cin >> array[i];
  }
  FastSort(array, array + n);
  for (long long i = 0; i < n; ++i) {
    std::cout << array[i] << '\n';
  }
  delete[] array;
  return 0;
}
