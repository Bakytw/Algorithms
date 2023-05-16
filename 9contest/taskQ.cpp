#include <iostream>
#include <limits>
#include <vector>

const long long kInf = std::numeric_limits<long long>::max();

struct Graph {
  long long from_, to_;
  long long capacity_, cost_, flow_;
  Graph() = default;
  Graph(long long from, long long to, long long capacity, long long cost, long long flow)
      : from_(from), to_(to), capacity_(capacity), cost_(cost), flow_(flow) {}
};

void AddEdge(std::vector<Graph>& g, long long from, long long to, long long capacity,
             long long cost, long long flow, long long index) {
  Graph direct(from, to, capacity, cost, flow);
  Graph reverse(to, from, 0, -cost, flow);
  g[index * 2] = direct;
  g[index * 2 + 1] = reverse;
}

bool BellmanFord(const std::vector<Graph>& g, std::vector<long long>& parent, long long N) {
  std::vector<long long> dist(N, kInf);
  dist[0] = 0;
  for (long long n = 0; n <= N; ++n) {
    bool flag = false;
    for (long long i = 0; i < static_cast<long long>(g.size()); ++i) {
      if (dist[g[i].from_] != kInf) {
        if (dist[g[i].from_] + g[i].cost_ < dist[g[i].to_] &&
            g[i].flow_ < g[i].capacity_) {
          dist[g[i].to_] = dist[g[i].from_] + g[i].cost_;
          parent[g[i].to_] = i;
          flag = true;
        }
      }
    }
    if (!flag) {
      break;
    }
  }
  return dist[N - 1] != kInf;
}

long long MaxFlow(std::vector<Graph>& g, long long N) {
  long long max_flow = 0;
  long long min_cost = 0;
  std::vector<long long> parent(2 * N);
  while (BellmanFord(g, parent, N)) {
    long long tmp_flow = kInf;
    for (long long v = N - 1; v != 0; v = g[parent[v]].from_) {
      tmp_flow =
          std::min(tmp_flow, g[parent[v]].capacity_ - g[parent[v]].flow_);
    }
    for (long long v = N - 1; v != 0; v = g[parent[v]].from_) {
      g[parent[v]].flow_ += tmp_flow;
      g[parent[v] ^ 1].flow_ -= tmp_flow;
      min_cost += tmp_flow * g[parent[v]].cost_;
    }
    max_flow += tmp_flow;
  }
  return min_cost;
}

int main() {
  long long n, m;
  std::cin >> n >> m;
  std::vector<Graph> g(2 * m);
  for (long long i = 0; i < m; ++i) {
    long long from, to, capacity, cost;
    std::cin >> from >> to >> capacity >> cost;
    AddEdge(g, from - 1, to - 1, capacity, cost, 0, i);
  }
  std::cout << MaxFlow(g, n) << '\n';
  return 0;
}
