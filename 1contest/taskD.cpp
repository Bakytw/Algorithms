#include <deque>
#include <iostream>

void Queue(int n) {
  char ch;
  int num;
  std::deque<int> left, right;
  for (int i = 0; i < n; ++i) {
    std::cin >> ch;
    if (ch == '+') {
      std::cin >> num;
      right.push_back(num);
    } else if (ch == '*') {
      std::cin >> num;
      right.push_front(num);
    } else if (ch == '-') {
      std::cout << left.front() << std::endl;
      left.pop_front();
    }
    if (right.size() > left.size()) {
      left.push_back(right.front());
      right.pop_front();
    }
  }
}

int main() {
  int n;
  std::cin >> n;
  Queue(n);
  return 0;
}
