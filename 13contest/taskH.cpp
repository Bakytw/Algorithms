#include <algorithm>
#include <iostream>
#include <vector>

struct Point {
  long long x, y;
  Point() = default;
  Point(int xx, long long yy) : x(xx), y(yy) {}
};

bool CmpX(const Point& p1, const Point& p2) {
  return p1.x < p2.x || (p1.x == p2.x && p1.y < p2.y);
}

bool CmpUp(const Point& p1, const Point& p2, const Point& p3) {
  return p1.x * (p2.y - p3.y) + p2.x * (p3.y - p1.y) + p3.x * (p1.y - p2.y) < 0;
}

bool CmpDown(const Point& p1, const Point& p2, const Point& p3) {
  return p1.x * (p2.y - p3.y) + p2.x * (p3.y - p1.y) + p3.x * (p1.y - p2.y) > 0;
}

void UpDownHelper(std::vector<Point>& points, size_t index,
                  std::vector<Point>& up_or_down,
                  bool (&cmp)(const Point&, const Point&, const Point&)) {
  while (up_or_down.size() > 1 &&
         !cmp(up_or_down[up_or_down.size() - 2],
              up_or_down[up_or_down.size() - 1], points[index])) {
    up_or_down.pop_back();
  }
  up_or_down.push_back(points[index]);
}

void ConvexHull(std::vector<Point>& points) {
  std::sort(points.begin(), points.end(), &CmpX);
  Point p1 = points[0];
  Point p2 = points.back();
  std::vector<Point> up(1, p1);
  std::vector<Point> down(1, p1);
  for (size_t i = 1; i < points.size(); ++i) {
    if (i == points.size() - 1 || CmpUp(p1, points[i], p2)) {
      UpDownHelper(points, i, up, CmpUp);
    }
    if (i == points.size() - 1 || CmpDown(p1, points[i], p2)) {
      UpDownHelper(points, i, down, CmpDown);
    }
  }
  points.clear();
  for (size_t i = 0; i < up.size(); ++i) {
    points.push_back(up[i]);
  }
  for (size_t i = down.size() - 2; i > 0; --i) {
    points.push_back(down[i]);
  }
}

void PrintArea(std::vector<Point>& points) {
  long long ans = 0;
  for (size_t i = 0; i < points.size(); ++i) {
    ans += (points[i].x * points[(i + 1) % points.size()].y -
            points[(i + 1) % points.size()].x * points[i].y);
  }
  if (ans % 2 == 0) {
    std::cout << std::to_string(std::abs(ans) / 2) << ".0";
  } else {
    std::cout << std::to_string(std::abs(ans) / 2) << ".5";
  }
}

int main() {
  long long nn;
  std::cin >> nn;
  std::vector<Point> points(nn);
  for (int i = 0; i < nn; ++i) {
    std::cin >> points[i].x >> points[i].y;
  }
  ConvexHull(points);
  std::cout << points.size() << '\n';
  for (auto pp : points) {
    std::cout << pp.x << ' ' << pp.y << '\n';
  }
  PrintArea(points);
  return 0;
}
