#include <bits/stdc++.h>
using namespace std;

bool check(int n, const vector<vector<int>> &segs, const vector<int> &p) {
  if (p.size() != n) return false;

  vector<int> ip(n);
  for (int i = 0; i < n; i++) {
    ip[p[i]] = i;
  }

  vector<bool> vis_r(n, false);
  for (const auto &seg : segs) {
    int sz = seg.size();
    int mn = n, mx = -1;
    for (int i : seg) {
      mn = min(mn, ip[i]);
      mx = max(mx, ip[i]);
    }
    if (mx - mn != sz - 1) return false;
    vis_r[mx] = true;
  }

  for (int i = 1; i < n; i++) {
    if (!vis_r[i]) return false;
  }

  return true;
}

void test_case() {
  int n;
  cin >> n;

  vector<vector<int>> segs(n - 1), isegs(n);
  for (int i = 0; i < n - 1; i++) {
    int sz;
    cin >> sz;
    segs[i].resize(sz);
    for (int &j : segs[i]) {
      cin >> j, j--;
      isegs[j].push_back(i);
    }
  }

  vector<int> freq;
  vector<bool> seg_vis;
  vector<int> p;

  for (int it = 0; it < 2; it++) {
    freq.assign(n, 0);
    for (int i = 0; i < n; i++) {
      freq[i] = isegs[i].size();
    }
    seg_vis.assign(n - 1, true);
    p.clear();

    vector<int> q;
    for (int i = 0; i < n; i++) {
      if (freq[i] == 1) {
        q.push_back(i);
      }
    }

    int last = -1;
    while (!q.empty()) {
      assert(q.size() <= 2);

      int i;
      if (q.size() == 1) i = q[0], q.pop_back();
      else {
        if ((last != -1 and q[1] != last) or (last == -1 and it == 1)) {
          i = q[1];
          q.pop_back();
          last = q[0];
        }
        else {
          i = q[0];
          q.erase(q.begin());
          last = q[1];
        }
      }

      if (freq[i] != 1) break;
      assert(freq[i] == 1);

      int seg_id = -1;
      for (int j : isegs[i]) {
        if (seg_vis[j]) seg_id = j;
      }
      assert(seg_id != -1);

      p.push_back(i);
      seg_vis[seg_id] = false;
      for (int j : segs[seg_id]) {
        freq[j]--;
        if (freq[j] == 1) {
          q.push_back(j);
        }
      }
    }

    if (p.size() == n - 1) {
      vector<bool> got(n, false);
      for (int i : p) got[i] = true;
      int missing = find(got.begin(), got.end(), false) - got.begin();
      p.push_back(missing);
      reverse(p.begin(), p.end());
      if (check(n, segs, p)) break;
    }
  }

  assert(p.size() == n);
  for (int i = 0; i < n; i++) {
    if (i) cout << " ";
    cout << p[i] + 1;
  }
  cout << "\n";
}

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);

  int t;
  cin >> t;

  for (int cs = 1; cs <= t; cs++) {
    test_case();
  }

  return 0;
}