#include <bits/stdc++.h>

using namespace std;
using ll = long long;

const int N = 1e5 + 5;

bitset<2 * N> vis;
vector<int> ans[1000];

void print(int n) {

  cout << 2 << endl;

  int g1 = vis.count();
  ll sum = 0;
  cout << g1;
  for (int i = 1; i < 2 * n; i += 2) {
    if (vis[i]) {
      cout << " " << i;
      sum += i;
      g1--;
    }
  }

  ll target = 1LL * n * n;

  // cerr << n << endl;
  // cerr << sum << ' ' << target << endl;
  assert(sum == target / 2);

  cout << '\n';
  int g2 = n - vis.count();
  cout << g2;
  for (int i = 1; i < 2 * n; i += 2) {
    if (!vis[i]) {
      cout << " " << i;
      g2--;
    }
  }
  cout << '\n';
}

int main() {
  int n;

  cin >> n;

  if (n == 2) {
    cout << "-1\n"; return 0;
  }

  if (n % 4 == 2) {

    ll target = n * n;
    target /= 2;
    for (int i = 2 * n - 1; i >= 1; i -= 2) {
      if (target == 0) break;
    }

    if (target == 0) {
      print(n);
      return 0;
    }

    vis.reset();
    target = 1LL * n * n / 2;

    for (int i = 2 * n - 1; i >= 1; i -= 4) {
      if (target >= i) {
        vis[i] = 1;
        target -= i;
      }
      if (target == 0) break;
    }

    if (target == 0) {
      print(n);
      return 0;
    }

    for (int i = 2 * n - 3; i >= 1; i -= 4) {
      if (target >= i) {
        target -= i;
        vis[i] = 1;
      }
      if (target == 0) break;
    }

    cerr << target << endl;

    if (target == 0) {
      print(n);
      return 0;
    }

    cerr << target << endl;

    bool flag = false;
    for (int i = 3; i < 2 * n; i += 2) {
      if (vis[1]  and vis[i] and !vis[i + 2]) {
        vis[1] = 0;
        vis[i] = 0;
        vis[i + 2] = 1;
        flag = true; break;
      }
    }

    assert(flag);
    print(n);
    return 0;
  }
  else if (n % 4 == 0) {
    for (int i = 1, j = n + n - 1; i < j; i += 4, j -= 4) {
      vis[i] = vis[j] = 1;
    }
    print(n);
    return 0;
  }
  else {

    bool flag = false;
    for (int d = 2; d * d <= n and !flag; d++) {
      if (n % d == 0) {
        // cerr << d << endl;
        set<int> st;
        for (int i  = 1; i < n + n; i += 2) {
          st.insert(i);
        }
        bool cur_flag = true;
        for (int k = 0; k < d; k++) {
          ll target = 1LL * n * n / d;
          while (target >= *(prev(st.end()))) {
            cerr << target << " " << *(prev(st.end())) << endl;
            target -= *(prev(st.end()));
            ans[k].push_back(*(prev(st.end())));
            st.erase(prev(st.end()));
          }
          cout << endl;

          while (target > 0) {
            auto at = st.upper_bound(target);
            if (at == st.begin()) {
              cur_flag = false; break;
            }
            at--;
            cerr << target << " " << *at << endl;
            target -= *at;
            ans[k].push_back(*at);
            st.erase(at);
          }
        }

        if (cur_flag) {

          cout << d << '\n';
          for (int k = 0; k < d; k++) {
            cout << ans[k].size();
            for (auto x : ans[k]) cout << " " << x;
            cout << '\n';
          }

          flag = true; break;
        } else {
          for (int g = 0; g < d; g++) ans[g].clear();
        }
      }
    }

    if (!flag) {
      cout << "-1\n";
    }
  }
}

// 27, 25, 23, 21, 19, 17, 15, 13, 11, 9, 7,