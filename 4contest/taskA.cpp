#include <algorithm>
#include <iostream>
#include <list>
#include <vector>

class Hashtable {
 private:
  static const size_t kModule = 907;
  size_t capacity_ = 0;
  std::vector<std::list<size_t>*> pointer_;
  static size_t Hash(size_t key) { return key % kModule; }

 public:
  explicit Hashtable(size_t size);
  void Insert(size_t key);
  void Erase(size_t key);
  bool Find(size_t key);
  ~Hashtable();
};

int main() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(nullptr);
  std::cout.tie(nullptr);
  size_t n, req;
  char command;
  std::cin >> n;
  Hashtable ht(1000000);

  for (size_t i = 0; i < n; ++i) {
    std::cin >> command >> req;
    if (command == '+') {
      ht.Insert(req);
    } else if (command == '?') {
      bool flag = ht.Find(req);
      if (flag) {
        std::cout << "YES" << '\n';
        continue;
      }
      std::cout << "NO" << '\n';
    } else if (command == '-') {
      ht.Erase(req);
    }
  }
  return 0;
}

Hashtable::Hashtable(size_t size) {
  capacity_ = size;
  pointer_.resize(capacity_);
  for (size_t i = 0; i < capacity_; ++i) {
    pointer_[i] = nullptr;
  }
}

void Hashtable::Insert(size_t key) {
  size_t index = Hash(key) % capacity_;
  if (pointer_[index] == nullptr) {
    pointer_[index] = new std::list<size_t>(1, key);
  } else {
    auto find_iter =
        std::find(pointer_[index]->begin(), pointer_[index]->end(), key);
    if (pointer_[index]->end() == find_iter) {
      pointer_[index]->push_back(key);
    }
  }
}

void Hashtable::Erase(size_t key) {
  size_t index = Hash(key) % capacity_;
  if (pointer_[index] != nullptr) {
    pointer_[index]->remove(key);
  }
}

bool Hashtable::Find(size_t key) {
  size_t index = Hash(key) % capacity_;
  if (pointer_[index] != nullptr) {
    auto find_iter =
        std::find(pointer_[index]->begin(), pointer_[index]->end(), key);
    if (pointer_[index]->end() != find_iter) {
      return true;
    }
  }
  return false;
}

Hashtable::~Hashtable() {
  for (size_t i = 0; i < capacity_; ++i) {
    if (pointer_[i] != nullptr) {
      delete pointer_[i];
    }
  }
}
