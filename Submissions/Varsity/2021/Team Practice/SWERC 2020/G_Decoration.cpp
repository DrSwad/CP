#include <bits/stdc++.h>
using namespace std;

const int N = 1e6 + 5;

int n, k;
int p[N], cnt[N], divs[N];
int out[N];
vector<int> in[N];
deque<int> path;
long long sum;
bool done[N];
int freq[N];
long long ans[N];

void init_graph() {
  divs[0] = 0;
  divs[1] = 1;

  for (int i = 2; i < n; i++) {
    for (int j = i; j < n; j += i) {
      if (!p[j]) {
        p[j] = i;
        if (j / i % i == 0) cnt[j] = cnt[j / i] + 1;
        else cnt[j] = 1;
      }
    }
  }

  for (int i = 2; i < n; i++) {
    divs[i] = divs[i / p[i]] / cnt[i] * (cnt[i] + 1);
  }

  for (int i = 0; i < n; i++) {
    int j = (i + divs[i]) % n;
    out[i] = j;
    in[j].push_back(i);
  }
}

void init_path(int root) {
  path = deque<int>();
  sum = 0;
  int v = root;
  while (path.size() < k and freq[v] == 0) {
    path.push_back(v);
    sum += v;
    freq[v]++;
    v = out[v];
  }
}

void push_front(int v) {
  path.push_front(v), sum += v, freq[v]++;
  while (path.size() > k or freq[path.back()] > 1) {
    int last = path.back();
    sum -= last;
    path.pop_back();
    freq[last]--;
  }
}

void pop_front() {
  int v = path.front();
  freq[v]--;
  while (path.size() <= k and freq[out[path.back()]] == 0) {
    int last = out[path.back()];
    sum += last;
    path.push_back(last);
    freq[last]++;
  }
  path.pop_front(), sum -= v;
}

void dfs(int v) {
  if (path.size() == k) ans[v] = sum;
  else ans[v] = LLONG_MAX;
  done[v] = true;

  for (int u : in[v]) {
    if (!done[u]) {
      push_front(u);
      dfs(u);
      pop_front();
    }
  }

  int u = out[v];
  if (!done[u]) {
    pop_front();
    dfs(u);
    push_front(v);
  }
}

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);

  cin >> n >> k;

  init_graph();

  for (int i = 0; i < n; i++) {
    if (!done[i]) {
      init_path(i);
      dfs(i);
    }
  }

  int root = min_element(ans, ans + n) - ans;
  if (ans[root] == LLONG_MAX) cout << "-1\n";
  else {
    int v = root;
    for (int i = 0; i < k; i++) {
      if (i) cout << " ";
      cout << v;
      v = out[v];
    }
    cout << "\n";
  }

  return 0;
}