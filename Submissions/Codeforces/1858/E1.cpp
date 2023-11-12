#include <bits/stdc++.h>
using namespace std;

const int N = 1e6;
const int logn = 20;

int sz;
int a[N + 1];
vector<int> adj[N + 1];
int sp[N + 1][logn];
stack<int> st;
vector<int> queries_at[N + 1];

int cnt;
int freq[N + 1];
int ans[N + 1];

void dfs(int at) {
  if (at) {
    if (freq[a[at]] == 0) cnt++;
    freq[a[at]]++;
  }

  for (int iq : queries_at[at]) {
    ans[iq] = cnt;
  }

  for (int to : adj[at]) {
    dfs(to);
  }

  if (at) {
    freq[a[at]]--;
    if (freq[a[at]] == 0) cnt--;
  }
}

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);

  sz = 1;
  int at = 0;

  int q;
  cin >> q;

  int tot_q = 0;
  while (q--) {
    char type;
    cin >> type;

    if (type == '?') {
      queries_at[at].push_back(tot_q++);
    }
    else if (type == '!') {
      at = st.top();
      st.pop();
    }
    else if (type == '+') {
      int prv = at;
      st.push(prv);
      at = sz;

      int x;
      cin >> x;
      a[sz++] = x;

      adj[prv].push_back(at);

      sp[at][0] = prv;
      for (int i = 1; i < logn; i++) {
        sp[at][i] = sp[sp[at][i - 1]][i - 1];
      }
    }
    else {
      assert(type == '-');
      st.push(at);

      int k;
      cin >> k;

      for (int i = 0; i < logn; i++) {
        if (k >> i & 1) {
          at = sp[at][i];
        }
      }
    }
  }

  dfs(0);

  for (int i = 0; i < tot_q; i++) {
    cout << ans[i] << "\n";
  }

  return 0;
}