#include <bits/stdc++.h>
using namespace std;

const int N = 2e6 + 6;
const int LOGN = 22;

int n, k;
pair<int, int> segs[N];
int nxt[N][LOGN];

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);

  int n, k;
  cin >> n >> k;

  for (int i = 0; i < k; i++) {
    int a, b;
    cin >> a >> b;
    a--, b--;
    if (a > b) b += n;
    b++;

    segs[i * 2] = {a, b};
    segs[i * 2 + 1] = {a + n, min(2 * n, b + n)};
  }
  k *= 2;

  sort(segs, segs + k);

  vector<pair<int, int>> st;
  for (int i = k - 1; i >= 0; i--) {
    while (!st.empty() and segs[st.back().second].second <= segs[i].second) {
      st.pop_back();
    }
    st.push_back({segs[i].first, i});

    nxt[i][0] = lower_bound(st.begin(), st.end(), make_pair(segs[i].second, k), greater<pair<int, int>>())->second;

    for (int j = 1; j < LOGN; j++) {
      nxt[i][j] = nxt[nxt[i][j - 1]][j - 1];
    }
  }

  int ans = -1;
  for (int i = 0; i < k; i++) {
    int st = segs[i].first;
    int en = st + n;
    if (segs[nxt[i][LOGN - 1]].second < en) continue;

    int curr = 1;
    if (segs[i].second < en) {
      int id = i;
      for (int j = LOGN - 1; j >= 0; j--) {
        if (segs[nxt[id][j]].second < en) {
          id = nxt[id][j];
          curr += 1 << j;
        }
      }
      curr++;
    }

    ans = ans == -1 ? curr : min(ans, curr);
  }

  if (ans == -1) cout << "impossible\n";
  else cout << ans << "\n";

  return 0;
}