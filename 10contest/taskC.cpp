// no_concepts
#include <iostream>
#include <queue>
#include <vector>

class Trie {
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
  std::vector<Node> t_;

 public:
  Trie() { t_.emplace_back(); }
  void Add(const std::string& str, int index) {
    int vertex = 0;
    for (auto c : str) {
      if (t_[vertex].to[c - 'a'] == -1) {
        t_.emplace_back();
        t_[vertex].to[c - 'a'] = static_cast<int>(t_.size()) - 1;
      }
      vertex = t_[vertex].to[c - 'a'];
    }
    t_[vertex].indices.push_back(index);
    t_[vertex].size = static_cast<int>(str.size());
    t_[vertex].term = true;
  }

  void AhoCorasik() {
    t_[0].link = 0;
    for (int i = 0; i < kSigma; ++i) {
      if (t_[0].to[i] == -1) {
        t_[0].to[i] = 0;
      }
    }

    std::queue<int> queue;
    queue.push(0);
    while (!queue.empty()) {
      int v = queue.front();
      queue.pop();

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

        queue.push(u);
      }
    }
  }

  int GetLink(int u) const { return t_[u].link; }

  bool GetTerm(int u) const { return t_[u].term; }

  int GetUp(int u) const { return t_[u].up; }

  int GetSize(int u) const { return t_[u].size; }

  int GetVertex(int u, int c) const { return t_[u].to[c]; }

  std::vector<int> GetIndices(int u) const { return t_[u].indices; }
};

std::vector<std::vector<size_t>> Entries(const Trie& trie, int num,
                                         const std::string& str) {
  int v = 0;
  std::vector<std::vector<size_t>> entries(num);
  for (size_t i = 0; i < str.size(); ++i) {
    v = trie.GetVertex(v, str[i] - 'a');
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

void Output(const std::vector<std::vector<size_t>>& entries, int num) {
  for (int i = 0; i < num; ++i) {
    std::cout << entries[i].size() << ' ';
    for (auto index : entries[i]) {
      std::cout << index + 1 << ' ';
    }
    std::cout << '\n';
  }
}

int main() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(nullptr);
  std::cout.tie(nullptr);

  std::string str;
  int num;
  Trie trie;
  std::cin >> str;
  std::cin >> num;
  for (int i = 0; i < num; ++i) {
    std::string word;
    std::cin >> word;
    trie.Add(word, i);
  }

  trie.AhoCorasik();
  std::vector<std::vector<size_t>> entries(Entries(trie, num, str));
  Output(entries, num);
  return 0;
}
