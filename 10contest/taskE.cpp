// no_concepts
#include <iostream>
#include <vector>

const static int kSigma = 10;

class Trie {
 public:
  void Add(const std::string& s) {
    if (t_.empty()) {
      t_.emplace_back();
    }
    int v = 0;
    for (size_t j = 0; j < 2 * s.size(); ++j) {
      ++t_[v].supref;
      size_t curr = j % 2 == 0 ? j / 2 : s.size() - 1 - j / 2;
      if (t_[v].to[ToDigit(s[curr])] == -1) {
        t_.emplace_back();
        t_[v].to[ToDigit(s[curr])] = static_cast<int>(t_.size()) - 1;
        t_.back().size = j + 1;
      }
      v = t_[v].to[ToDigit(s[curr])];
    }
    ++t_[v].supref;
  }

  std::vector<int> Groups(int k, int sz) {
    std::vector<int> groups(2 * sz);
    for (int i = 0; i < Size() - 1; ++i) {
      if (t_[i + 1].supref >= k && t_[i + 1].size % 2 == 0) {
        groups[t_[i + 1].size / 2] += 1;
      }
    }
    return groups;
  }

 private:
  struct Node {
    std::vector<int> to;
    size_t size;
    int supref = 0;
    Node() { to.assign(kSigma, -1); }
  };

  int Size() const { return static_cast<int>(t_.size()); }

  static int ToDigit(char c) { return c - '0'; }

  std::vector<Node> t_;
};

void Output(const std::vector<int>& answer, int n, int k) {
  int q, l;
  std::cin >> q;
  for (int i = 0; i < q; ++i) {
    std::cin >> l;
    if (l != 0) {
      std::cout << answer[l] << '\n';
    } else {
      if (n < k) {
        std::cout << "0\n";
      } else {
        std::cout << "1\n";
      }
    }
  }
}

int main() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(nullptr);
  std::cout.tie(nullptr);
  int n, k, sz = 0;
  std::cin >> n >> k;
  Trie trie;
  for (int i = 0; i < n; ++i) {
    std::string s;
    std::cin >> s;
    sz = std::max(sz, static_cast<int>(s.size()));
    trie.Add(s);
  }
  std::vector<int> answer(trie.Groups(k, sz));
  Output(answer, n, k);
  return 0;
}
