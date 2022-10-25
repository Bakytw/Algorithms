#include <iostream>
#include <string>
#include <vector>

class Heap {
 private:
  std::vector<long long> array_min_;
  int pointer_[1000000] = {0};
  int num_[1000000] = {0};
  int count_ = 1;
  int heap_size_min_ = 0;

 public:
  bool Empty() { return array_min_.empty(); }
  void Exchange(long long u, long long v);
  void SiftUp(long long v);
  void SiftDown(long long v);
  long long Peek();
  void ExtractMin();
  void Insert(long long x);
  void DecreaseKey(long long t, long long delta);
  void Clear();
};

int main() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(nullptr);
  int q;
  long long delta, i, x;
  std::string s;
  std::cin >> q;
  Heap heap;
  for (int k = 0; k < q; ++k) {
    std::cin >> s;
    if (s == "insert") {
      std::cin >> x;
      heap.Insert(x);
    } else if (s == "getMin") {
      std::cout << heap.Peek() << '\n';
    } else if (s == "extractMin") {
      heap.ExtractMin();
    } else if (s == "decreaseKey") {
      std::cin >> i >> delta;
      heap.DecreaseKey(i, delta);
    }
  }
  return 0;
}

void Heap::Exchange(long long u, long long v) {
  std::swap(num_[u], num_[v]);
  std::swap(pointer_[num_[u]], pointer_[num_[v]]);
  std::swap(array_min_[u], array_min_[v]);
}

void Heap::SiftUp(long long v) {
  while (v != 0) {
    if (array_min_[v] < array_min_[(v - 1) / 2]) {
      Exchange(v, (v - 1) / 2);
      v = (v - 1) / 2;
    } else {
      break;
    }
  }
}

void Heap::SiftDown(long long v) {
  while (2 * v + 1 < heap_size_min_) {
    long long u = 2 * v + 1;
    if (u + 1 < heap_size_min_ && array_min_[u + 1] < array_min_[u]) {
      ++u;
    }
    if (array_min_[u] < array_min_[v]) {
      Exchange(u, v);
      v = u;
    } else {
      break;
    }
  }
}

long long Heap::Peek() {
  ++count_;
  return array_min_[0];
}

void Heap::ExtractMin() {
  Exchange(0, heap_size_min_ - 1);
  array_min_.pop_back();
  --heap_size_min_;
  ++count_;
  if (!array_min_.empty()) {
    SiftDown(0);
  }
}

void Heap::Insert(long long x) {
  array_min_.push_back(x);
  ++heap_size_min_;
  pointer_[count_ - 1] = heap_size_min_ - 1;
  num_[array_min_.size() - 1] = count_ - 1;
  ++count_;
  SiftUp(heap_size_min_ - 1);
}

void Heap::DecreaseKey(long long t, long long delta) {
  array_min_[pointer_[t - 1]] -= delta;
  ++count_;
  SiftUp(pointer_[t - 1]);
}

void Heap::Clear() {
  while (!Empty()) {
    ExtractMin();
  }
}
