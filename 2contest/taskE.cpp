#include <iostream>
#include <string>
#include <vector>

class MaxMinHeap {
 private:
  std::vector<std::pair<int, int>> array_min_;
  std::vector<std::pair<int, int>> array_max_;
  int heap_size_min_ = 0;
  int heap_size_max_ = 0;

 public:
  bool Empty() { return array_min_.empty(); }
  int Size() { return heap_size_min_; }
  void ExchangeMin(int u, int v);
  void ExchangeMax(int u, int v);
  int SiftUpMin(int v);
  int SiftUpMax(int v);
  void SiftDownMin(int v);
  void SiftDownMax(int v);
  int GetMin() { return array_min_[0].first; }
  int GetMax() { return array_max_[0].first; }
  int ExtractMin();
  int ExtractMax();
  void Insert(int x);
  void EraseMin(int x);
  void EraseMax(int x);
  void Clear();
};

bool Checker(MaxMinHeap& heap, int type);

void Extraction(MaxMinHeap& heap, int type);

int main() {
  int n, m;
  std::string command;
  std::cin >> m;
  MaxMinHeap heap;
  for (int i = 0; i < m; ++i) {
    std::cin >> command;
    if (command == "insert") {
      std::cin >> n;
      heap.Insert(n);
      std::cout << "ok" << '\n';
    } else if (command == "extract_min") {
      Extraction(heap, 1);
    } else if (command == "get_min") {
      Checker(heap, 1);
    } else if (command == "extract_max") {
      Extraction(heap, 2);
    } else if (command == "get_max") {
      Checker(heap, 2);
    } else if (command == "size") {
      std::cout << heap.Size() << '\n';
    } else if (command == "clear") {
      heap.Clear();
      std::cout << "ok" << '\n';
    }
  }
  return 0;
}

void MaxMinHeap::ExchangeMin(int u, int v) {
  std::swap(array_min_[u], array_min_[v]);
  array_max_[array_min_[u].second].second = u;
  array_max_[array_min_[v].second].second = v;
}

void MaxMinHeap::ExchangeMax(int u, int v) {
  std::swap(array_max_[u], array_max_[v]);
  array_min_[array_max_[u].second].second = u;
  array_min_[array_max_[v].second].second = v;
}

int MaxMinHeap::SiftUpMin(int v) {
  while (v != 0) {
    if (array_min_[v].first < array_min_[(v - 1) / 2].first) {
      ExchangeMin(v, (v - 1) / 2);
      v = (v - 1) / 2;
    } else {
      break;
    }
  }
  return v;
}

int MaxMinHeap::SiftUpMax(int v) {
  while (v != 0) {
    if (array_max_[v].first > array_max_[(v - 1) / 2].first) {
      ExchangeMax(v, (v - 1) / 2);
      v = (v - 1) / 2;
    } else {
      break;
    }
  }
  return v;
}

void MaxMinHeap::SiftDownMin(int v) {
  while (2 * v + 1 < heap_size_min_) {
    int u = 2 * v + 1;
    if (u + 1 < heap_size_min_ &&
        array_min_[u + 1].first < array_min_[u].first) {
      ++u;
    }
    if (array_min_[u].first < array_min_[v].first) {
      ExchangeMin(u, v);
      v = u;
    } else {
      break;
    }
  }
}

void MaxMinHeap::SiftDownMax(int v) {
  while (2 * v + 1 < heap_size_max_) {
    int u = 2 * v + 1;
    if (u + 1 < heap_size_max_ &&
        array_max_[u + 1].first > array_max_[u].first) {
      ++u;
    }
    if (array_max_[u].first > array_max_[v].first) {
      ExchangeMax(u, v);
      v = u;
    } else {
      break;
    }
  }
}

int MaxMinHeap::ExtractMin() {
  int index = array_min_[0].second;
  ExchangeMin(0, heap_size_min_ - 1);
  array_min_.pop_back();
  --heap_size_min_;
  if (!array_min_.empty()) {
    SiftDownMin(0);
  }
  return index;
}

int MaxMinHeap::ExtractMax() {
  int index = array_max_[0].second;
  ExchangeMax(0, heap_size_max_ - 1);
  array_max_.pop_back();
  --heap_size_max_;
  if (!array_max_.empty()) {
    SiftDownMax(0);
  }
  return index;
}

void MaxMinHeap::Insert(int x) {
  array_max_.emplace_back(x, heap_size_max_);
  array_min_.emplace_back(x, heap_size_min_);
  SiftUpMin(heap_size_min_);
  SiftUpMax(heap_size_max_);
  ++heap_size_max_;
  ++heap_size_min_;
}

void MaxMinHeap::EraseMin(int x) {
  array_min_[x].first = 0;
  SiftUpMin(x);
  ExtractMin();
}

void MaxMinHeap::EraseMax(int x) {
  array_max_[x].first = 1000000001;
  SiftUpMax(x);
  ExtractMax();
}

void MaxMinHeap::Clear() {
  while (!Empty()) {
    ExtractMin();
    ExtractMax();
  }
}

bool Checker(MaxMinHeap& heap, int type) {
  if (heap.Empty()) {
    std::cout << "error" << '\n';
    return true;
  }
  if (type == 1) {
    std::cout << heap.GetMin() << '\n';
  } else {
    std::cout << heap.GetMax() << '\n';
  }
  return false;
}

void Extraction(MaxMinHeap& heap, int type) {
  if (type == 1) {
    if (Checker(heap, 1)) {
      return;
    }
    heap.EraseMax(heap.ExtractMin());
  } else {
    if (Checker(heap, 2)) {
      return;
    }
    heap.EraseMin(heap.ExtractMax());
  }
}
