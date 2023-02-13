seed_seq seq{
  (uint64_t)chrono::duration_cast<chrono::nanoseconds>(
    chrono::high_resolution_clock::now().time_since_epoch())
  .count(),
  (uint64_t)__builtin_ia32_rdtsc(),
  (uint64_t)(uintptr_t)make_unique<char>().get()};
mt19937 rng(seq);

int n, m;
vector<vector<int>> g; // [0..n) -> [0..m)
vector<int> mtn, mtm;
vector<char> used;

bool try_kuhn(int v) {
  if (used[v]) return false;
  used[v] = true;
  for (int to : g[v]) if (mtm[to] == -1) {
      mtm[to] = v;
      mtn[v] = to;
      return true;
    }
  for (int to : g[v]) if (try_kuhn(mtm[to])) {
      mtm[to] = v;
      mtn[v] = to;
      return true;
    }
  return false;
}

void match() {
  mtn.assign(n, -1);
  mtm.assign(m, -1);

  vector<int> order(n);
  iota(order.begin(), order.end(), 0);
  shuffle(order.begin(), order.end(), rng);

  int ok = true;
  while (ok--) {
    used.assign(n, false);
    for (int v : order) {
      if (mtn[v] == -1) ok |= try_kuhn(v);
    }
  }
}

int main() {
  // ... read the graph ...

  match();

  for (int i = 0; i < m; ++i) {
    if (mtm[i] != -1) {
      printf("%d %d\n", mtm[i] + 1, i + 1);
    }
  }

  return 0;
}