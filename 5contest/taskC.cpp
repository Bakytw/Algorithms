#include <iostream>

class SplayTree {
 private:
  struct Node {
    Node* parent = nullptr;
    Node *left = nullptr, *right = nullptr;
    std::string key, value;
    Node(const std::string& key, const std::string& value)
        : key(key), value(value) {}
    ~Node() {
      delete left;
      delete right;
    }
  };
  Node* root_ = nullptr;

  void SetParent(Node* child, Node* parent) {
    if (child != nullptr) {
      child->parent = parent;
    }
  }

  void KeepParent(Node* v) {
    SetParent(v->left, v);
    SetParent(v->right, v);
  }

  void Rotate(Node* parent, Node* child) {
    Node* gparent = parent->parent;
    if (gparent != nullptr) {
      if (gparent->left == parent) {
        gparent->left = child;
      } else {
        gparent->right = child;
      }
    }
    if (parent->left == child) {
      Node* right_son_of_left = child->right;
      child->right = parent;
      parent->left = right_son_of_left;
    } else {
      Node* left_son_of_right = child->left;
      child->left = parent;
      parent->right = left_son_of_right;
    }
    root_ = child;
    KeepParent(child);
    KeepParent(parent);
    SetParent(child, gparent);
  }

  Node* Splay(Node* v) {
    if (v->parent == nullptr) {
      return v;
    }
    Node* parent = v->parent;
    Node* gparent = parent->parent;
    if (gparent == nullptr) {
      Rotate(parent, v);
      return root_;
    }
    if ((gparent->left == parent) == (parent->left == v)) {
      Rotate(gparent, parent);
      Rotate(parent, v);
    } else {
      Rotate(parent, v);
      Rotate(gparent, v);
    }
    root_ = Splay(v);
    return root_;
  }

 public:
  Node* Find(const std::string& key) {
    Node* current = root_;
    if (current == nullptr) {
      return nullptr;
    }
    while (true) {
      if (key == current->key) {
        return Splay(current);
      }
      if (key < current->key) {
        if (current->left != nullptr) {
          current = current->left;
        } else {
          return nullptr;
        }
      }
      if (key > current->key) {
        if (current->right != nullptr) {
          current = current->right;
        } else {
          return nullptr;
        }
      }
    }
  }

  Node* Insert(const std::string& key, const std::string& value) {
    Node* node = new Node(key, value);
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
    SetParent(node, tmp);
    if (tmp != nullptr) {
      if (node->key < tmp->key) {
        tmp->left = node;
      } else {
        tmp->right = node;
      }
    }
    return root_ = Splay(node);
  }

  ~SplayTree() { delete root_; }
};

int main() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(nullptr);
  std::cout.tie(nullptr);
  int n;
  std::cin >> n;
  SplayTree tree;
  std::string s1, s2;
  for (int i = 0; i < n; ++i) {
    std::cin >> s1 >> s2;
    tree.Insert(s1, s2);
    tree.Insert(s2, s1);
  }
  int q;
  std::cin >> q;
  for (int i = 0; i < q; ++i) {
    std::cin >> s1;
    auto* temp = tree.Find(s1);
    std::cout << temp->value << '\n';
  }
  return 0;
}
