#include <iostream>
#include <vector>

class SegmentTree {
 private:
  std::vector<long long> tree_;
  size_t size_ = 1;

 public:
  [[nodiscard]] size_t Size() const { return size_; }
  explicit SegmentTree(const std::vector<long long>& array);
  void Update(long long v, long long tl, long long tr, long long pos,
              long long delta);
  long long GetMax(long long v, long long tl, long long tr, long long l,
                   long long r);
  long long GetIndex(long long v, long long tl, long long tr, long long index,
                     long long x);
};

int main() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(nullptr);
  std::cout.tie(nullptr);
  long long n, m;
  std::cin >> n >> m;
  std::vector<long long> places(n);
  for (long long i = 0; i < n; ++i) {
    std::cin >> places[i];
  }
  SegmentTree st(places);
  auto seg_size = static_cast<long long>(st.Size());
  for (long long j = 0; j < m; ++j) {
    long long command, i, x;
    std::cin >> command >> i >> x;
    if (command == 0) {
      st.Update(1, 0, seg_size - 1, i - 1, x - places[i - 1]);
      places[i - 1] = x;
    } else if (command == 1) {
      std::cout << st.GetIndex(1, 0, seg_size - 1, i - 1, x) << '\n';
    }
  }
  return 0;
}

SegmentTree::SegmentTree(const std::vector<long long>& array) {
  while (size_ < array.size()) {
    size_ <<= 1;
  }
  tree_.resize(2 * size_);
  for (size_t i = size_; i < size_ + array.size(); ++i) {
    tree_[i] = array[i - size_];
  }
  for (size_t i = size_ - 1; i >= 1; --i) {
    tree_[i] = std::max(tree_[2 * i], tree_[2 * i + 1]);
  }
}

void SegmentTree::Update(long long v, long long tl, long long tr, long long pos,
                         long long delta) {
  if (tl == tr) {
    tree_[v] += delta;
    return;
  }
  long long tm = (tl + tr) >> 1;
  if (pos <= tm) {
    Update(2 * v, tl, tm, pos, delta);
  } else {
    Update(2 * v + 1, tm + 1, tr, pos, delta);
  }
  tree_[v] = std::max(tree_[2 * v], tree_[2 * v + 1]);
}

long long SegmentTree::GetMax(long long v, long long tl, long long tr,
                              long long l, long long r) {
  if (tl == l && tr == r) {
    return tree_[v];
  }
  long long tm = (tr + tl) >> 1, ans = -1;
  if (l <= tm) {
    ans = std::max(ans, GetMax(2 * v, tl, tm, l, std::min(tm, r)));
  }
  if (r >= tm + 1) {
    ans = std::max(ans, GetMax(2 * v + 1, tm + 1, tr, std::max(tm + 1, l), r));
  }
  return ans;
}

long long SegmentTree::GetIndex(long long v, long long tl, long long tr,
                                long long index, long long x) {
  if (v == 1 && GetMax(v, tl, tr, index, tr) < x) {
    return -1;
  }
  if (v >= static_cast<long long>(size_)) {
    return v - static_cast<long long>(size_) + 1;
  }
  long long tm = (tr + tl) >> 1;
  if (GetMax(2 * v, tl, tm, index, tm) >= x) {
    return GetIndex(2 * v, tl, tm, std::min(index, tm), x);
  }
  return GetIndex(2 * v + 1, tm + 1, tr, std::max(tm + 1, index), x);
}
