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
  void Push(int elem);
  bool Empty() { return stacksize_ == 0u; }
  int Pop();
  int Min() { return top_->min; }
  void Clear();
  ~Stack() { Clear(); }
};

class Queue {
 private:
  Stack s1_, s2_;
  size_t queuesize_ = 0;

 public:
  size_t Size() { return queuesize_; }
  bool Empty() { return queuesize_ == 0u; }
  int Shifting();
  int Front();
  void Enqueue(int elem);
  int Dequeue();
  int Min();
  void Clear();
  ~Queue() { Clear(); }
};

void CheckErrors(int temp);

int main() {
  Queue q;
  int elem, n, answer;
  std::cin >> n;
  std::string word;
  for (int i = 0; i < n; ++i) {
    std::cin >> word;
    if (word == "enqueue") {
      std::cin >> elem;
      q.Enqueue(elem);
      std::cout << "ok" << std::endl;
    } else if (word == "dequeue") {
      answer = q.Dequeue();
      CheckErrors(answer);
    } else if (word == "front") {
      answer = q.Front();
      CheckErrors(answer);
    } else if (word == "size") {
      std::cout << q.Size() << std::endl;
    } else if (word == "clear") {
      q.Clear();
      std::cout << "ok" << std::endl;
    } else if (word == "min") {
      answer = q.Min();
      CheckErrors(answer);
    }
  }
  return 0;
}

void Stack::Push(int elem) {
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

int Stack::Pop() {
  if (Empty()) {
    return -1;
  }
  int temp = top_->value;
  if (stacksize_ == 1) {
    delete top_;
    top_ = nullptr;
  } else {
    top_ = top_->prev;
    delete top_->next;
    top_->next = nullptr;
  }
  --stacksize_;
  return temp;
}

void Stack::Clear() {
  while (!Empty()) {
    Pop();
  }
}

int Queue::Shifting() {
  if (Empty()) {
    return -1;
  }
  if (s2_.Empty()) {
    while (!s1_.Empty()) {
      s2_.Push(s1_.Back());
      s1_.Pop();
    }
  }
  return 0;
}

int Queue::Front() {
  Shifting();
  if (s2_.Empty()) {
    return -1;
  }
  return s2_.Back();
}

void Queue::Enqueue(int elem) {
  s1_.Push(elem);
  ++queuesize_;
}

int Queue::Dequeue() {
  if (Empty()) {
    return -1;
  }
  Front();
  --queuesize_;
  return s2_.Pop();
}

int Queue::Min() {
  if (Empty()) {
    return -1;
  }
  if (s1_.Empty() || s2_.Empty()) {
    return s1_.Empty() ? s2_.Min() : s1_.Min();
  }
  return std::min(s2_.Min(), s1_.Min());
}

void Queue::Clear() {
  s1_.Clear();
  s2_.Clear();
  queuesize_ = 0;
}

void CheckErrors(int temp) {
  if (temp == -1) {
    std::cout << "error" << '\n';
  } else {
    std::cout << temp << '\n';
  }
}
