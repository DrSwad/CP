int n, m;
vector<vector<int>> g; // [0..n) -> [0..m)
vector<int> mtn, mtm;
vector<char> used;

bool try_kuhn(int v) {
  if (used[v]) return false;
  used[v] = true;
  for (int to : g[v]) {
    if (mtm[to] == -1 or try_kuhn(mtm[to])) {
      mtm[to] = v;
      mtn[v] = to;
      return true;
    }
  }
  return false;
}

void match() {
  mtn.assign(n, -1);
  mtm.assign(m, -1);

  vector<int> order(n);
  iota(order.begin(), order.end(), 0);
  // modify order if custom order needed

  used.assign(n, false);
  for (int v : order) {
    if (mtn[v] == -1 and try_kuhn(v)) {
      used.assign(n, false);
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