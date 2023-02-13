#include <bits/stdc++.h>
using namespace std;

const int H = 18;
const int N = (1 << H) + 5;
const int H_UP = 11;
const int Q = 1e5 + 5;
const int MAX_W = 1e5 + 5;

int n;
int v[N], w[N];
int q;
int queries[Q];
vector<int> queries_at_node[N];
int ans[Q];

vector<pair<int, int>> calculate_kdp(vector<pair<int, int>> curr_kdp, int w, int v) {
  vector<pair<int, int>> new_kdp;
  for (auto [curr_w, curr_v] : curr_kdp) {
    if (curr_w + w < MAX_W) {
      new_kdp.push_back({curr_w + w, curr_v + v});
    }
  }

  int curr_sz = curr_kdp.size();
  int new_sz = new_kdp.size();
  vector<pair<int, int>> merged_kdp;
  for (int i = 0, j = 0; i < curr_sz or j < new_sz; ) {
    if (i == curr_sz) merged_kdp.push_back(new_kdp[j++]);
    else if (j == new_sz) merged_kdp.push_back(curr_kdp[i++]);
    else if (new_kdp[j].first < curr_kdp[i].first) merged_kdp.push_back(new_kdp[j++]);
    else if (curr_kdp[i].first < new_kdp[j].first) merged_kdp.push_back(curr_kdp[i++]);
    else if (new_kdp[j].second > curr_kdp[i].second) merged_kdp.push_back(new_kdp[j++]), i++;
    else merged_kdp.push_back(curr_kdp[i++]), j++;
  }

  int prv = 0;
  for (auto & [w, v] : merged_kdp) {
    v = max(v, prv);
    prv = v;
  }

  return merged_kdp;
}

vector<pair<int, int>> upper_half_kdp;
void dfs(int at, vector<pair<int, int>> parent_kdp) {
  if (at > n) return;

  int h = 32 - __builtin_clz(at);
  auto current_kdp = calculate_kdp(
    h != H_UP + 1 ? parent_kdp : vector<pair<int, int>>(1, {0, 0}),
    w[at],
    v[at]
    );
  if (h == H_UP) upper_half_kdp = current_kdp;

  for (int qi : queries_at_node[at]) {
    int l = queries[qi];
    if (h <= H_UP) {
      ans[qi] = prev(lower_bound(current_kdp.begin(), current_kdp.end(), make_pair(l + 1, -1)))->second;
    }
    else {
      for (auto [w, v] : current_kdp) {
        if (w > l) break;
        ans[qi] = max(
          ans[qi],
          v + prev(lower_bound(upper_half_kdp.begin(), upper_half_kdp.end(), make_pair((l - w) + 1, -1)))->second
          );
      }
    }
  }

  dfs(at << 1, current_kdp);
  dfs(at << 1 | 1, current_kdp);
}

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);

  cin >> n;
  for (int i = 1; i <= n; i++) {
    cin >> v[i] >> w[i];
  }

  cin >> q;
  for (int i = 1; i <= q; i++) {
    int v, l;
    cin >> v >> l;
    queries[i] = l;
    queries_at_node[v].push_back(i);
  }

  dfs(1, {{0, 0}});

  for (int i = 1; i <= q; i++) {
    cout << ans[i] << "\n";
  }

  return 0;
}