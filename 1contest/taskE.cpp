#include <iostream>
#include <string>

class Stack {
 private:
  struct Node {
    int value, min = 1e9;
    Node* next = nullptr;
    Node* prev = nullptr;
    Node(int elem) : value(elem) {}
  };
  Node* top_ = nullptr;
  size_t stacksize_ = 0;

 public:
  size_t Size() { return stacksize_; }
  int Back() { return top_->value; }

  void Push(int elem) {
    if (top_ == nullptr) {
      top_ = new Node(elem);
      top_->min = elem;
    } else {
      top_->next = new Node(elem);
      top_->next->prev = top_;
      top_ = top_->next;
      top_->min = std::min(elem, top_->prev->min);
    }
    ++stacksize_;
  }

  bool Empty() { return stacksize_ == 0u; }

  void Pop() {
    if (Empty()) {
      return;
    }
    if (stacksize_ == 1) {
      delete top_;
      top_ = nullptr;
    } else {
      top_ = top_->prev;
      delete top_->next;
      top_->next = nullptr;
    }
    --stacksize_;
  }

  int Min() { return top_->min; }

  void Clear() {
    while (!Empty()) {
      Pop();
    }
  }

  ~Stack() { Clear(); }
};

class Queue {
 private:
  Stack s1_, s2_;
  size_t queuesize_ = 0;

 public:
  size_t Size() { return queuesize_; }

  bool Empty() { return queuesize_ == 0u; }
  void Shifting() {
    if (Empty()) {
      std::cout << "error" << std::endl;
      return;
    }
    if (s2_.Empty()) {
      while (!s1_.Empty()) {
        s2_.Push(s1_.Back());
        s1_.Pop();
      }
    }
  }

  void Front() {
    Shifting();
    if (s2_.Empty()) {
      return;
    }
    std::cout << s2_.Back() << std::endl;
  }

  void Enqueue(int elem) {
    s1_.Push(elem);
    ++queuesize_;
  }

  void Dequeue() {
    if (Empty()) {
      std::cout << "error" << std::endl;
      return;
    }
    Front();
    s2_.Pop();
    --queuesize_;
  }

  void Min() {
    int ans = 0;
    if (Empty()) {
      std::cout << "error" << std::endl;
      return;
    }
    if (s1_.Empty() || s2_.Empty()) {
      ans = s1_.Empty() ? s2_.Min() : s1_.Min();
    } else {
      ans = std::min(s2_.Min(), s1_.Min());
    }
    std::cout << ans << std::endl;
  }

  void Clear() {
    s1_.Clear();
    s2_.Clear();
    queuesize_ = 0;
  }

  ~Queue() { Clear(); }
};

int main() {
  Queue q;
  int elem, n;
  std::cin >> n;
  std::string word;
  for (int i = 0; i < n; ++i) {
    std::cin >> word;
    if (word == "enqueue") {
      std::cin >> elem;
      q.Enqueue(elem);
      std::cout << "ok" << std::endl;
    } else if (word == "dequeue") {
      q.Dequeue();
    } else if (word == "front") {
      q.Front();
    } else if (word == "size") {
      std::cout << q.Size() << std::endl;
    } else if (word == "clear") {
      q.Clear();
      std::cout << "ok" << std::endl;
    } else if (word == "min") {
      q.Min();
    }
  }
  return 0;
}
