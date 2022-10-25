#include <iostream>

const short CHUNK_SIZE = 8;
const short POWER = 256;


void RadixSort(short byte, long long n, const long long* p_int, long long* to) {
  int count[POWER] = {0};
  int index[POWER] = {0};
  for (long long i = 0; i < n; ++i) {
    count[((p_int[i]) >> (byte * CHUNK_SIZE)) & (POWER - 1)]++;
  }
  for (long long i = 1; i < POWER; ++i) {
    index[i] = index[i - 1] + count[i - 1];
  }
  for (long long i = 0; i < n; ++i) {
    to[index[((p_int[i]) >> (byte * 8)) & (POWER - 1)]++] = p_int[i];
  }
}

void FastSort(long long* begin, const long long* end) {
  long long n = (end - begin);
  long long* tmp = new long long[n];
  for (short i = 0; i < CHUNK_SIZE; ++i) {
    RadixSort(i, n, begin, tmp);
    RadixSort(++i, n, tmp, begin);
  }
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
