#include <algorithm>
#include <iostream>
#include <vector>

class Hashtable {
 private:
  static const size_t kModule = 907;
  size_t capacity_ = 0;
  size_t size_ = 0;
  double load_factor_ = 0;
  std::vector<std::vector<int>*> pointer_;
  static size_t Hash(int key) { return key % kModule; }
  void Insert1(int key);
  void Rehash();
  void UpdateLoadFactor();

 public:
  explicit Hashtable(size_t capacity);
  void Insert(int key);
  void Erase(int key);
  bool Find(int key);
  ~Hashtable();
};

int main() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(nullptr);
  std::cout.tie(nullptr);
  int n, req;
  char command;
  std::cin >> n;
  Hashtable ht(4);
  for (int i = 0; i < n; ++i) {
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

Hashtable::Hashtable(size_t capacity) {
  capacity_ = capacity;
  size_ = 0;
  pointer_.resize(capacity_);
  for (size_t i = 0; i < capacity_; ++i) {
    pointer_[i] = nullptr;
  }
}

void Hashtable::Insert1(int key) {
  size_t index = Hash(key) % capacity_;
  if (pointer_[index] == nullptr) {
    ++size_;
    UpdateLoadFactor();
    pointer_[index] = new std::vector<int>(1, key);
  } else {
    auto find_iter =
        std::find(pointer_[index]->begin(), pointer_[index]->end(), key);
    if (pointer_[index]->end() == find_iter) {
      ++size_;
      UpdateLoadFactor();
      pointer_[index]->push_back(key);
    }
  }
}

void Hashtable::Insert(int key) {
  if (load_factor_ >= 0.75) {
    Rehash();
  }
  Insert1(key);
}

void Hashtable::Erase(int key) {
  size_t index = Hash(key) % capacity_;
  if (pointer_[index] != nullptr) {
    size_t i = 0;
    for (; i < (*pointer_[index]).size(); ++i) {
      if ((*pointer_[index])[i] == key) {
        break;
      }
    }
    if (i < (*pointer_[index]).size() && (*pointer_[index])[i] == key) {
      std::swap((*pointer_[index])[i], (*pointer_[index]).back());
      (*pointer_[index]).pop_back();
      --size_;
      UpdateLoadFactor();
    }
  }
}

bool Hashtable::Find(int key) {
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

void Hashtable::Rehash() {
  capacity_ *= 2;
  std::vector<std::vector<int>*> temp = pointer_;
  pointer_.assign(capacity_, nullptr);
  for (auto& i : temp) {
    if (i != nullptr) {
      for (int& tmp : *i) {
        Insert1(tmp);
      }
      delete i;
    }
  }
}

void Hashtable::UpdateLoadFactor() {
  load_factor_ = static_cast<double>(size_) / static_cast<double>(capacity_);
}

Hashtable::~Hashtable() {
  for (size_t i = 0; i < capacity_; ++i) {
    if (pointer_[i] != nullptr) {
      delete pointer_[i];
    }
  }
}
