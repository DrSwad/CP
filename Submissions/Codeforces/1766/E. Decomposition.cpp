#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

vector<vector<int>> states;
int total_states;
vector<vector<int>> state_adj;

vector<int> make_move(vector<int> v, int val) {
  int at = 0;
  while (at < v.size() and (v[at] & val) == 0) at++;
  if (at < v.size()) v[at] = val;
  else v.push_back(val);
  return v;
}

void init_states() {
  map<vector<int>, int> state_id;
  queue<int> q;
  q.push(total_states);
  states.push_back({});
  state_adj.push_back({});
  state_id[vector<int>()] = total_states++;

  while (!q.empty()) {
    int at = q.front(); q.pop();

    for (int val = 1; val <= 3; val++) {
      vector<int> nxt_state = make_move(states[at], val);

      if (state_id.find(nxt_state) == state_id.end()) {
        q.push(total_states);
        states.push_back(nxt_state);
        state_adj.push_back({});
        state_id[nxt_state] = total_states++;
      }

      state_adj[at].push_back(state_id[nxt_state]);
    }
  }
}

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);

  init_states();

  int n;
  cin >> n;

  vector<int> a(n);
  for (int &i : a) cin >> i;

  ll ans = 0;

  // handle zeroes separately
  for (int i = 0; i < n; i++) {
    if (a[i] == 0) {
      ans += (ll)(i + 1) * (n - i);
    }
  }

  vector<vector<ll>> dp(n + 1, vector<ll>(total_states, 0));
  dp[0][0] = 1;

  for (int i = 1; i <= n; i++) {
    for (int prv_state = 0; prv_state < total_states; prv_state++) {
      if (a[i - 1]) {
        dp[i][state_adj[prv_state][a[i - 1] - 1]] += dp[i - 1][prv_state];
      }
      else {
        dp[i][prv_state] += dp[i - 1][prv_state];
      }
    }
    dp[i][0]++;

    for (int cur_state = 0; cur_state < total_states; cur_state++) {
      ans += (ll)dp[i][cur_state] * states[cur_state].size();
    }
  }

  cout << ans << "\n";
  
  return 0;
}
