#include <bits/stdc++.h>
using namespace std;

void test_case() {
  int n;
  cin >> n;

  string s;
  cin >> s;

  int k;
  cin >> k;

  vector<bool> is_special(26, false);
  for (int i = 0; i < k; i++) {
    char c;
    cin >> c;
    is_special[c - 'a'] = true;
  }

  int right_most_special;
  for (right_most_special = n - 1; right_most_special >= 0; right_most_special--) {
    if (is_special[s[right_most_special] - 'a']) {
      break;
    }
  }

  int segment_length = 0;
  int ans = 0;

  for (int i = 0; i < right_most_special; i++) {
    if (is_special[s[i] - 'a']) {
      segment_length = 1;
    }
    else {
      segment_length++;
    }

    ans = max(ans, segment_length);
  }

  cout << ans << "\n";
}

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);

  int t = 1;
  cin >> t;

  for (int cs = 1; cs <= t; cs++) {
    // cout << "Case " << cs << ": ";
    test_case();
  }

  return 0;
}