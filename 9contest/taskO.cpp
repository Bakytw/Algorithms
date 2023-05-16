#include <iostream>
#include <limits>
#include <queue>
#include <set>
#include <vector>

const int kInf = std::numeric_limits<int>::max();

struct Graph {
  int from_, to_;
  double capacity_, flow_;
  Graph() = default;
  Graph(int from, int to, double capacity, double flow)
      : from_(from), to_(to), capacity_(capacity), flow_(flow) {}
};

struct Flow {
  std::vector<Graph> edge;
  std::vector<std::vector<size_t>> edge_index;
  std::vector<size_t> dist;
  std::vector<size_t> ptr;
  Flow() = default;
};

void AddEdge(Flow& flow, int from, int to, double capacity, double f) {
  Graph direct(from, to, capacity, f);
  Graph reverse(to, from, 0, f);
  flow.edge_index[from].push_back(flow.edge.size());
  flow.edge.push_back(direct);
  flow.edge_index[to].push_back(flow.edge.size());
  flow.edge.push_back(reverse);
}

bool Bfs(Flow& flow, int N) {
  flow.dist.assign(N + 20, kInf);
  std::queue<int> q;
  flow.dist[N] = 0;
  q.push(N);
  while (!q.empty()) {
    int v = q.front();
    q.pop();
    for (int i = 0; i < flow.edge_index[v].size(); ++i) {
      size_t index = flow.edge_index[v][i];
      int to = flow.edge[index].to_;
      if (1e-8 < flow.edge[index].capacity_ - flow.edge[index].flow_ &&
          flow.dist[v] + 1 < flow.dist[to]) {
        flow.dist[to] = flow.dist[v] + 1;
        q.push(to);
      }
    }
  }
  return flow.dist[N + 1] != kInf;
}

double Dfs(Flow& f, int N, int v, double flow) {
  if (flow < 1e-8 || v == N + 1) {
    return flow;
  }
  for (size_t i = f.ptr[v]; i < f.edge_index[v].size(); ++i) {
    size_t index = f.edge_index[v][i];
    int to = f.edge[index].to_;
    if (f.dist[to] != f.dist[v] + 1) {
      continue;
    }
    double pushed = Dfs(f, N, to, std::min(flow, f.edge[index].capacity_ - f.edge[index].flow_));
    if (pushed > 0) {
      f.edge[index].flow_ += pushed;
      f.edge[index ^ 1].flow_ -= pushed;
      return pushed;
    }
    ++f.ptr[v];
  }
  return 0;
}

double MaxFlow(Flow& flow, int N) {
  double max_flow = 0;
  while (Bfs(flow, N)) {
    double w;
    flow.ptr.assign(N + 20, 0);
    while ((w = Dfs(flow, N, N, kInf)) > 1e-8) {
      max_flow += w;
    }
  }
  return max_flow;
}

void Check(Flow& flow, std::vector<std::vector<int>>& edge,
           std::vector<int>& deg, int N, int M, double mid) {
  flow.edge_index.resize(200);
  flow.ptr.resize(200);
  for (int i = 0; i < N; ++i) {
    for (int j = 0; j < edge[i].size(); ++j) {
      AddEdge(flow, edge[i][j], i, 1, 0);
    }
  }
  for (int i = 0; i < N + 1; ++i) {
    AddEdge(flow, N, i, M * 2, 0);
    AddEdge(flow, i, N + 1, M * 2 + mid * 2.0 - deg[i], 0);
  }
  MaxFlow(flow, N);
}

void CountReachableVertices(const Flow& flow, std::vector<bool>& used, int& res, int N, int v) {
  used[v] = true;
  res += (v < N);
  for (int i = 0; i < flow.edge_index[v].size(); ++i) {
    size_t index = flow.edge_index[v][i];
    int to = flow.edge[index].to_;
    if (flow.edge[index].capacity_ - flow.edge[index].flow_ > 1e-8 &&
        !used[to]) {
      CountReachableVertices(flow, used, res, N, to);
    }
  }
}

void FindReachableVertices(const Flow& flow, std::set<int>& set, std::vector<bool>& used, int& res,
                           int N, int v) {
  used[v] = true;
  if (v < N) {
    set.insert(v + 1);
  }
  res += (v < N);
  for (int i = 0; i < flow.edge_index[v].size(); ++i) {
    size_t index = flow.edge_index[v][i];
    int to = flow.edge[index].to_;
    if (flow.edge[index].capacity_ - flow.edge[index].flow_ > 1e-8 &&
        !used[to]) {
      FindReachableVertices(flow, set, used, res, N, to);
    }
  }
}

int main() {
  int n, m;
  std::cin >> n >> m;
  if (m == 0) {
    std::cout << 1 << '\n' << 1;
    return 0;
  }
  std::vector<std::vector<int>> edge(n);
  std::vector<int> deg(n + 2, 0);
  for (int i = 1; i <= m; ++i) {
    int from, to;
    std::cin >> from >> to;
    ++deg[from - 1];
    ++deg[to - 1];
    edge[from - 1].push_back(to - 1);
    edge[to - 1].push_back(from - 1);
  }
  double left = 0.49;
  double right = m / 2.0;
  double mid;
  double EPS = 1.0 / n / (n - 1);
  while (left + EPS < right) {
    Flow flow;
    mid = 0.5 * (left + right);
    Check(flow, edge, deg, n, m, mid);
    int res = 0;
    std::vector<bool> used(n * 2, false);
    CountReachableVertices(flow, used, res, n, n);
    if (res > 0) {
      left = mid;
    } else {
      right = mid;
    }
  }
  Flow flow;
  Check(flow, edge, deg, n, m, left);
  std::set<int> set;
  int res = 0;
  std::vector<bool> used(n + 20, false);
  FindReachableVertices(flow, set, used, res, n, n);
  std::cout << res << '\n';
  for (auto v : set) {
    std::cout << v << '\n';
  }
  return 0;
}
