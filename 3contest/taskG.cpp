#include <algorithm>
#include <iostream>
#include <vector>

struct Point {
  long long x, y, w;
  explicit Point(long long x = 0, long long y = 0, long long w = 0)
      : x(x), y(y), w(w) {}
};

bool operator<(const Point& a, const Point& b) { return a.x < b.x; }

long long Search(const std::vector<long long>& arr, long long temp) {
  return std::lower_bound(arr.begin(), arr.end(), temp) - arr.begin() - 1;
}

long long Search(const std::vector<Point>& arr, Point temp) {
  return std::lower_bound(arr.begin(), arr.end(), temp) - arr.begin() - 1;
}

class FenwickOfFenwicks {
 private:
  struct Fenwick {
    size_t size = 0;
    std::vector<long long> sums;
    std::vector<long long> y_s;
    void Update(long long y, long long delta) {
      for (size_t i = Search(y_s, y + 1); i < size; i = (i | (i + 1))) {
        sums[i] += delta;
      }
    }
    long long GetSum(long long y) {
      long long answer = 0;
      for (long long i = Search(y_s, y + 1); i >= 0; i = (i & (i + 1)) - 1) {
        answer += sums[i];
      }
      return answer;
    }
  };
  size_t fenwicks_size_ = 0;
  std::vector<Fenwick> fenwicks_;
  std::vector<long long> sorted_x_;

 public:
  explicit FenwickOfFenwicks(const std::vector<Point>& triple);
  void Update(Point temp);
  long long GetSum(Point temp);
};

int main() {
  long long n;
  std::cin >> n;
  std::vector<Point> triple(n);
  for (long long i = 0; i < n; ++i) {
    std::cin >> triple[i].x >> triple[i].y >> triple[i].w;
  }
  FenwickOfFenwicks fof(triple);
  long long m;
  std::cin >> m;
  for (long long i = 0; i < m; ++i) {
    std::string buffer;
    long long req1, req2;
    std::cin >> buffer >> req1 >> req2;
    if (buffer == "change") {
      --req1;
      triple[req1].w = req2 - triple[req1].w;
      fof.Update(triple[req1]);
      triple[req1].w = req2;
    } else if (buffer == "get") {
      std::cout << fof.GetSum(Point(req1, req2)) << "\n";
    }
  }
  return 0;
}

FenwickOfFenwicks::FenwickOfFenwicks(const std::vector<Point>& triple) {
  std::vector<Point> new_triple = triple;
  std::sort(new_triple.begin(), new_triple.end());
  sorted_x_.resize(triple.size());
  for (size_t i = 0; i < triple.size(); ++i) {
    sorted_x_[i] = triple[i].x;
  }
  std::sort(sorted_x_.begin(), sorted_x_.end());
  sorted_x_.resize(std::unique(sorted_x_.begin(), sorted_x_.end()) -
                   sorted_x_.begin());
  fenwicks_size_ = sorted_x_.size();
  fenwicks_.resize(fenwicks_size_);
  for (size_t i = 0; i < fenwicks_size_; ++i) {
    long long start =
        (i & (i + 1)) > 0
            ? Search(new_triple, Point(sorted_x_[(i & (i + 1)) - 1] + 1)) + 1
            : 0;
    long long finish = Search(new_triple, Point(sorted_x_[i] + 1)) + 1;
    for (long long j = start; j < finish; ++j) {
      fenwicks_[i].y_s.push_back(new_triple[j].y);
      ++fenwicks_[i].size;
    }
    std::sort(fenwicks_[i].y_s.begin(), fenwicks_[i].y_s.end());
    fenwicks_[i].sums.resize(fenwicks_[i].size);
  }
  for (auto& i : triple) {
    Update(i);
  }
}

void FenwickOfFenwicks::Update(Point temp) {
  for (size_t i = Search(sorted_x_, temp.x + 1); i < fenwicks_size_;
       i = (i | (i + 1))) {
    fenwicks_[i].Update(temp.y, temp.w);
  }
}

long long FenwickOfFenwicks::GetSum(Point temp) {
  long long answer = 0;
  for (long long i = Search(sorted_x_, temp.x + 1); i >= 0;
       i = (i & (i + 1)) - 1) {
    answer += fenwicks_[i].GetSum(temp.y);
  }
  return answer;
}
