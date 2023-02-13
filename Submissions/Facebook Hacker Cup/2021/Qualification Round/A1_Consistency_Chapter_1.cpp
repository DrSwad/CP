#include <bits/stdc++.h>
using namespace std;

const int ALPHA = 26;
const int INF = ALPHA;

void test_case() {
  string s;
  cin >> s;

  vector<vector<int>> dist(ALPHA, vector<int>(ALPHA, ALPHA));
  for (int i = 0; i < ALPHA; i++) dist[i][i] = 0;

  vector<bool> is_vowel(ALPHA, false);
  is_vowel['A' - 'A'] = true;
  is_vowel['E' - 'A'] = true;
  is_vowel['I' - 'A'] = true;
  is_vowel['O' - 'A'] = true;
  is_vowel['U' - 'A'] = true;

  for (int i = 0; i < ALPHA; i++) {
    for (int j = 0; j < ALPHA; j++) {
      if (i != j and is_vowel[i] != is_vowel[j]) {
        dist[i][j] = 1;
      }
    }
  }

  for (int k = 0; k < ALPHA; k++) {
    for (int i = 0; i < ALPHA; i++) {
      for (int j = 0; j < ALPHA; j++) {
        dist[i][j] = min(dist[i][j], dist[i][k] + dist[k][j]);
      }
    }
  }

  int ans = -1;

  for (int i = 0; i < ALPHA; i++) {
    bool possible = true;
    int curr_dist = 0;

    for (char c : s) {
      if (dist[c - 'A'][i] >= ALPHA) possible = false;
      else curr_dist += dist[c - 'A'][i];
    }

    if (possible) {
      ans = ans == -1 ? curr_dist : min(ans, curr_dist);
    }
  }

  cout << ans << "\n";
}

int main() {
  ios::sync_with_stdio(false);
  cin.tie(0);

  int t;
  cin >> t;

  for (int cs = 1; cs <= t; cs++) {
    cout << "Case #" << cs << ": ";
    test_case();
  }

  return 0;
}