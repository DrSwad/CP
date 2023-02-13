#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);

  int n;
  ll k;
  cin >> n >> k;

  vector<int> freq(n, 0);
  freq[0] = n;
  ll sum = 0;

  for (int i = 1; i < n and sum != k; i++) {
    freq[i] = freq[i - 1] - 1;
    sum += freq[i - 1] - 1;
    freq[i - 1] = 1;

    while (sum > k) {
      freq[i]--;
      freq[i - 1]++;
      sum--;
    }
  }

  if (sum != k) cout << "Impossible\n";
  else {
    deque<char> ans;
    for (int i = n - 1; i >= 0; i--) {
      if (freq[i]) {
        ans.push_front('(');
        ans.push_back(')');
        freq[i]--;

        while (freq[i]--) {
          ans.push_back('(');
          ans.push_back(')');
        }
      }
    }

    while (!ans.empty()) {
      cout << ans.front();
      ans.pop_front();
    }
    cout << "\n";
  }

  return 0;
}