#include <bits/stdc++.h>
using namespace std;

const int N = 25143;
const int MX = 16 * 26;

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);

  vector<string> s;
  {
    string line;
    while (getline(cin, line), !line.empty()) {
      s.push_back(line);
    }
  }

  sort(s.begin(), s.end());
  s.resize(unique(s.begin(), s.end()) - s.begin());

  int n = s.size();
  vector<vector<int>> adj(n);
  for (int i = 0; i < n; i++) adj[i].reserve(MX);

  map<string, vector<int>> mp[16];
  for (int i = 0; i < n; i++) {
    for (int j = 0; j < s[i].size(); j++) {
      string cur = s[i];
      cur.erase(cur.begin() + j);
      if (mp[j].find(cur) != mp[j].end()) {
        const auto &v = mp[j][cur];
        for (int k : v) {
          adj[i].push_back(k);
          adj[k].push_back(i);
        }
      }
      mp[j][cur].push_back(i);
    }
  }

  bool first_test = true;
  string line;
  while (getline(cin, line)) {
    if (!first_test) cout << "\n";
    first_test = false;

    string from_s, to_s;
    stringstream ss(line);
    ss >> from_s >> to_s;

    int from = lower_bound(s.begin(), s.end(), from_s) - s.begin();
    int to = lower_bound(s.begin(), s.end(), to_s) - s.begin();
    if (from >= n or to >= n) {
      cout << "No solution.\n";
      continue;
    }

    vector<int> dist(n, n);
    vector<int> parent(n, -1);
    queue<int> q;

    dist[from] = 0;
    q.push(from);

    while (!q.empty() and dist[to] == n) {
      int at = q.front();
      q.pop();

      for (int to : adj[at]) {
        if (dist[to] == n) {
          dist[to] = dist[at] + 1;
          parent[to] = at;
          q.push(to);
        }
      }
    }

    if (dist[to] == n) {
      cout << "No solution.\n";
      continue;
    }

    stack<int> ans;
    int at = to;

    while (at != -1) {
      ans.push(at);
      at = parent[at];
    }

    while (!ans.empty()) {
      cout << s[ans.top()] << "\n";
      ans.pop();
    }
  }

  return 0;
}