// no_concepts
#include <iostream>
#include <map>
#include <queue>
#include <set>
#include <vector>

const static int kSigma = 26;

struct Node {
  std::vector<int> to;
  std::vector<int> indices;
  int size{0};
  int link{-1};
  int up{-1};
  bool term{false};
  Node() { to.assign(kSigma, -1); };
};

class Trie {
 public:
  void Add(const std::string& s, int i) {
    if (t_.empty()) {
      t_.emplace_back();
    }
    int v = 0;
    for (auto c : s) {
      if (t_[v].to[c - 'a'] == -1) {
        t_.emplace_back();
        t_[v].to[c - 'a'] = static_cast<int>(t_.size()) - 1;
      }
      v = t_[v].to[c - 'a'];
    }
    t_[v].indices.push_back(i);
    t_[v].size = static_cast<int>(s.size());
    t_[v].term = true;
  }

  void AhoCorasik() {
    t_[0].link = 0;
    for (int i = 0; i < kSigma; ++i) {
      if (t_[0].to[i] == -1) {
        t_[0].to[i] = 0;
      }
    }
    std::queue<int> q;
    q.push(0);
    while (!q.empty()) {
      int v = q.front();
      q.pop();
      for (int c = 0; c < kSigma; ++c) {
        int u = t_[v].to[c];
        if (t_[u].link != -1) {
          continue;
        }
        t_[u].link = v == 0 ? 0 : t_[t_[v].link].to[c];
        if (t_[t_[u].link].term) {
          t_[u].up = t_[u].link;
        } else {
          t_[u].up = t_[t_[u].link].up;
        }
        for (int d = 0; d < kSigma; ++d) {
          if (t_[u].to[d] == -1) {
            t_[u].to[d] = t_[t_[u].link].to[d];
          }
        }
        q.push(u);
      }
    }
  }

  int GetLink(int u) const { return t_[u].link; }

  bool GetTerm(int u) const { return t_[u].term; }

  int GetUp(int u) const { return t_[u].up; }

  int GetSize(int u) const { return t_[u].size; }

  int GetVertex(int u, int c) const { return t_[u].to[c]; }

  std::vector<int> GetIndices(int u) const { return t_[u].indices; }

 private:
  std::vector<Node> t_;
};

std::vector<std::vector<int>> Entries(const Trie& trie, int n,
                                      const std::string& s) {
  int v = 0;
  std::vector<std::vector<int>> entries(n);
  for (int i = 0; i < static_cast<int>(s.size()); ++i) {
    v = trie.GetVertex(v, s[i] - 'a');
    if (trie.GetTerm(v)) {
      for (auto u : trie.GetIndices(v)) {
        entries[u].push_back(i + 1 - trie.GetSize(v));
      }
    }
    int u = trie.GetUp(v);
    while (u != -1) {
      for (auto k : trie.GetIndices(u)) {
        entries[k].push_back(i + 1 - trie.GetSize(u));
      }
      u = trie.GetUp(u);
    }
  }
  return entries;
}

void Output(const std::vector<std::vector<int>>& entries, int n) {
  for (int i = 0; i < n; ++i) {
    std::cout << entries[i].size() << ' ';
    for (auto index : entries[i]) {
      std::cout << index + 1 << ' ';
    }
    std::cout << std::endl;
  }
}

int main() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(nullptr);
  std::cout.tie(nullptr);
  std::string s;
  int n;
  Trie trie;
  std::cin >> s;
  std::cin >> n;
  for (int i = 0; i < n; ++i) {
    std::string p;
    std::cin >> p;
    trie.Add(p, i);
  }
  trie.AhoCorasik();
  std::vector<std::vector<int>> entries(Entries(trie, n, s));
  Output(entries, n);
  return 0;
}
