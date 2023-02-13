#include <bits/stdc++.h>
using namespace std;

#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
using namespace __gnu_pbds;
typedef tree<int, null_type, less<int>, rb_tree_tag,
    tree_order_statistics_node_update>
    ordered_set;
// find_by_order(k) : k'th element (0-indexed)
// order_of_key(k) : number of items strictly smaller than k
// auto cmp = [](int a, int b) { return a < b; };
// tree<int, null_type, decltype(cmp)> x(cmp);
// tree<int, null_type, function<bool(int, int)>> y(
//     [](int a, int b) { return a < b; });

string s;
int n;
vector<string> dict;
vector<int> kthDict;
vector<int> dictOrder;
int q;
vector<vector<tuple<int, int, int>>> lQueries;
vector<vector<int>> endsAt;

vector<int> getSubEnds(int id) {
  int sLen = s.length();
  int tLen = dict[id].length();

  vector<vector<int>> dp(tLen, vector<int>(sLen));
  for (int tI = tLen - 1; ~tI; tI--) {
    for (int sI = sLen - 1; ~sI; sI--) {
      if (tI == tLen - 1) {
        dp[tI][sI] = s[sI] == dict[id][tI] ? sI
            : sI < sLen - 1                ? dp[tI][sI + 1]
                                           : sLen;
      } else {
        dp[tI][sI] = sI == sLen - 1 ? sLen
            : s[sI] == dict[id][tI] ? dp[tI + 1][sI + 1]
                                    : dp[tI][sI + 1];
      }
    }
  }

  return dp[0];
}

int main() {
  cin >> s;
  int sLen = s.length();
  cin >> n >> q;

  dict.resize(n);
  for (int i = 0; i < n; i++) { cin >> dict[i]; }

  kthDict.resize(n);
  iota(kthDict.begin(), kthDict.end(), 0);
  sort(kthDict.begin(), kthDict.end(),
      [&](int i, int j) { return dict[i] < dict[j]; });
  dictOrder.resize(n);
  for (int i = 0; i < n; i++) { dictOrder[kthDict[i]] = i; }

  lQueries.resize(sLen);
  for (int i = 0; i < q; i++) {
    int l, r, k;
    scanf("%d %d %d", &l, &r, &k);
    l--, r--, k--;

    lQueries[l].emplace_back(r, k, i);
  }
  for (int i = 0; i < sLen; i++) {
    sort(lQueries[i].begin(), lQueries[i].end());
  }

  endsAt.resize(n);
  for (int i = 0; i < n; i++) { endsAt[i] = getSubEnds(i); }

  vector<int> ans(q);
  for (int l = 0; l < sLen; l++) {
    vector<vector<int>> insertAt(sLen + 1);
    for (int i = 0; i < n; i++) {
      insertAt[endsAt[i][l]].push_back(i);
    }

    ordered_set st;

    int qI = 0;
    for (int r = l; r < sLen; r++) {
      for (int i : insertAt[r]) { st.insert(dictOrder[i]); }

      while (
          qI < lQueries[l].size() and get<0>(lQueries[l][qI]) <= r) {
        auto [qR, qK, _qI] = lQueries[l][qI];
        ans[_qI] =
            st.size() <= qK ? -1 : kthDict[*st.find_by_order(qK)];
        qI++;
      }
    }
  }

  for (int i = 0; i < q; i++) {
    if (ans[i] == -1) puts("NO SUCH WORD");
    else
      cout << dict[ans[i]].substr(0, 10) << "\n";
  }

  return 0;
}