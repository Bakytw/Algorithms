#include <algorithm>
#include <iostream>
#include <vector>

struct Point {
  long long x;
  long long y;
  Point() = default;
  Point(long long xx, long long yy) : x(xx), y(yy) {}
};

Point operator-(const Point& p1, const Point& p2) {
  return {p1.x - p2.x, p1.y - p2.y};
}

Point operator+(const Point& p1, const Point& p2) {
  return {p1.x + p2.x, p1.y + p2.y};
}

long long CrossProd(const Point& p1, const Point& p2) {
  return p1.x * p2.y - p1.y * p2.x;
}

bool IsInside(std::vector<Point>& polygon, Point pp) {
  if (CrossProd(polygon[1] - polygon[0], pp - polygon[0]) < 0 ||
      CrossProd(polygon[polygon.size() - 1] - polygon[0], pp - polygon[0]) >
          0) {
    return false;
  }
  int left = 1;
  int right = static_cast<int>(polygon.size()) - 1;
  while (left + 1 < right) {
    int mid = (left + right) >> 1;
    if (CrossProd(polygon[mid] - polygon[0], pp - polygon[0]) > 0) {
      left = mid;
    } else {
      right = mid;
    }
  }
  return CrossProd(polygon[right] - polygon[left], pp - polygon[left]) >= 0;
}

void Rotate(std::vector<Point>& polygon) {
  auto iterator =
      min_element(polygon.begin(), polygon.end(), [&](auto p1, auto p2) {
        return p1.x == p2.x ? p1.y < p2.y : p1.x < p2.x;
      });
  rotate(polygon.begin(), iterator, polygon.end());
}

std::vector<Point> MinkowskiSum(std::vector<Point>& one,
                                std::vector<Point>& two) {
  Rotate(one);
  Rotate(two);
  one.push_back(one[0]);
  one.push_back(one[1]);
  two.push_back(two[0]);
  two.push_back(two[1]);
  size_t ii = 0;
  size_t jj = 0;
  std::vector<Point> answer;
  while (ii < one.size() - 2 || jj < two.size() - 2) {
    answer.push_back(one[ii] + two[jj]);
    long long angle = CrossProd(one[ii + 1] - one[ii], two[jj + 1] - two[jj]);
    if (angle >= 0) {
      ++ii;
    }
    if (angle <= 0) {
      ++jj;
    }
  }
  return answer;
}

int main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);
  std::vector<std::vector<Point>> zones(3);
  for (int i = 0; i < 3; ++i) {
    int nn;
    std::cin >> nn;
    zones[i].resize(nn);
    for (int j = 0; j < nn; ++j) {
      int x_i;
      int y_i;
      std::cin >> x_i >> y_i;
      zones[i][j] = Point(x_i, y_i);
    }
  }
  auto sum0_1(MinkowskiSum(zones[0], zones[1]));
  auto sum(MinkowskiSum(sum0_1, zones[2]));
  int mm;
  std::cin >> mm;
  for (int j = 0; j < mm; ++j) {
    int x_j;
    int y_j;
    std::cin >> x_j >> y_j;
    if (IsInside(sum, {3 * x_j, 3 * y_j})) {
      std::cout << "YES\n";
    } else {
      std::cout << "NO\n";
    }
  }
  return 0;
}
