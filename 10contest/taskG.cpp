// no_concepts
#include <iostream>
#include <vector>

const static int kSigma = 26;

class Trie {
 public:
  void Add(const std::string& s, int i) {
    if (t_.empty()) {
      t_.emplace_back();
    }
    int v = 0;
    int sz = static_cast<int>(s.size());
    for (int j = 0; j < sz; ++j) {
      if (t_[v].to[ToDigit(s[sz - j - 1])] == -1) {
        t_.emplace_back();
        t_[v].to[ToDigit(s[sz - j - 1])] = static_cast<int>(t_.size()) - 1;
      }
      if (IsPalindrom(s, 0, sz - j - 1)) {
        t_[v].indeces_pal.push_back(i);
      }
      v = t_[v].to[ToDigit(s[sz - j - 1])];
    }
    t_[v].indeces.push_back(i);
    t_[v].indeces_pal.push_back(i);
  }

  std::vector<std::vector<int>> CountPalindroms(
      int& p, std::vector<std::string>& dict) {
    int dict_size = static_cast<int>(dict.size());
    std::vector<std::vector<int>> palindroms(dict_size);
    for (int i = 0; i < dict_size; ++i) {
      std::string s = dict[i];
      int sz = static_cast<int>(s.size());
      int v = t_[0].to[ToDigit(s[0])];
      int temp = v;
      bool flag = true;
      for (int j = 0; j < sz - 1; ++j) {
        if (v != -1 && IsPalindrom(s, j + 1, sz - 1)) {
          for (int k : t_[v].indeces) {
            if (k != i) {
              palindroms[i].push_back(k);
              ++p;
            }
          }
        }
        if (v == -1 || t_[v].to[ToDigit(s[j + 1])] == -1) {
          flag = j + 1 >= sz;
          break;
        }
        v = t_[v].to[ToDigit(s[j + 1])];
        temp = j + 2 == sz ? v : temp;
      }
      if (temp != -1 && flag) {
        for (int j = 0; j < static_cast<int>(t_[temp].indeces_pal.size());
             ++j) {
          if (t_[v].indeces_pal[j] != i) {
            palindroms[i].push_back(t_[v].indeces_pal[j]);
            ++p;
          }
        }
      }
    }
    return palindroms;
  }

 private:
  struct Node {
    std::vector<int> indeces_pal;
    std::vector<int> indeces;
    std::vector<int> to;
    Node() { to.assign(kSigma, -1); }
  };

  bool IsPalindrom(const std::string& s, int i, int j) const {
    while (i < j) {
      if (s[i] != s[j]) {
        return false;
      }
      ++i;
      --j;
    }
    return true;
  }

  static int ToDigit(char c) { return c - 'a'; }

  std::vector<Node> t_;
};

void Output(int p, const std::vector<std::vector<int>>& palindroms) {
  std::cout << p << std::endl;
  for (int i = 1; i <= static_cast<int>(palindroms.size()); ++i) {
    for (int j = 0; j < static_cast<int>(palindroms[i - 1].size()); ++j) {
      std::cout << i << ' ' << palindroms[i - 1][j] + 1 << std::endl;
    }
  }
}

int main() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(nullptr);
  std::cout.tie(nullptr);
  int n, p = 0;
  std::cin >> n;
  Trie trie;
  std::vector<std::string> dict;
  for (int i = 0; i < n; ++i) {
    std::string s;
    std::cin >> s;
    dict.push_back(s);
    trie.Add(s, i);
  }
  std::vector<std::vector<int>> palindroms(trie.CountPalindroms(p, dict));
  Output(p, palindroms);
  return 0;
}
