#include <iostream>

static const long long kInf = 1e9;

class AVLTree {
 private:
  struct Node {
    Node *left = nullptr, *right = nullptr;
    long long key, height = 0;
    Node(long long key) : key(key), height(1) {}
    ~Node() {
      delete left;
      delete right;
    }
  };
  Node* root_ = nullptr;

  long long Height(Node* node) { return node != nullptr ? node->height : 0; }

  long long UpdateHeight(Node* node) {
    node->height = 1 + std::max(Height(node->left), Height(node->right));
    return node->height;
  }

  long long Factor(Node* node) {
    return node != nullptr ? Height(node->right) - Height(node->left) : 0;
  }

  Node* RotateRight(Node* node) {
    if (node != nullptr) {
      Node* left = node->left;
      Node* right_son_of_left = left->right;
      left->right = node;
      node->left = right_son_of_left;
      UpdateHeight(node);
      UpdateHeight(left);
      return left;
    }
    return node;
  }

  Node* RotateLeft(Node* node) {
    if (node != nullptr) {
      Node* right = node->right;
      Node* left_son_of_right = right->left;
      right->left = node;
      node->right = left_son_of_right;
      UpdateHeight(node);
      UpdateHeight(right);
      return right;
    }
    return node;
  }

  Node* Balance(Node* node) {
    UpdateHeight(node);
    if (Factor(node) == 2) {
      if (Factor(node->right) < 0) {
        node->right = RotateRight(node->right);
      }
      return RotateLeft(node);
    }
    if (Factor(node) == -2) {
      if (Factor(node->left) > 0) {
        node->left = RotateLeft(node->left);
      }
      return RotateRight(node);
    }
    return node;
  }

 public:
  Node* Insert(long long key) {
    Node* node = new Node(key);
    if (root_ == nullptr) {
      root_ = node;
      return root_;
    }
    Node* tmp = nullptr;
    Node* current = root_;
    while (current != nullptr) {
      tmp = current;
      if (node->key < current->key) {
        current = current->left;
      } else {
        current = current->right;
      }
    }
    if (tmp != nullptr) {
      if (node->key < tmp->key) {
        tmp->left = node;
      } else {
        tmp->right = node;
      }
    }
    return Balance(node);
  }

  long long FindNext(long long i) {
    if (root_ == nullptr) {
      return kInf;
    }
    return Next(root_, i);
  }

  long long Next(Node* node, long long i) {
    if (i > node->key) {
      if (node->right != nullptr) {
        return Next(node->right, i);
      }
      return kInf;
    }
    if (node->left != nullptr) {
      return std::min(Next(node->left, i), node->key);
    }
    return node->key;
  }

  ~AVLTree() { delete root_; }
};

int main() {
  long long n, key, prev = 0;
  char command;
  AVLTree tree;
  std::cin >> n;
  for (long long i = 0; i < n; ++i) {
    std::cin >> command >> key;
    if (command == '+') {
      tree.Insert((key + prev) % kInf);
      prev = 0;
    } else if (command == '?') {
      auto temp = tree.FindNext(key);
      if (temp == kInf) {
        prev = -1;
      } else {
        prev = temp;
      }
      std::cout << prev << '\n';
    }
  }
  return 0;
}
