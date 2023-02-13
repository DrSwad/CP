#include <bits/stdc++.h>
using namespace std;

int main() {
  int n, k;
  cin >> n >> k;

  vector<int> a(n);
  for (int &i : a) scanf("%d", &i);

  map<int, int> freq;
  set<int> nums;

  for (int i = 0; i < n; i++) {
    freq[a[i]]++;
    if (freq[a[i]] == 1) nums.insert(a[i]);
    else if (freq[a[i]] == 2) nums.erase(a[i]);

    if (i >= k) {
      freq[a[i - k]]--;
      if (freq[a[i - k]] == 1) nums.insert(a[i - k]);
      else if (freq[a[i - k]] == 0) nums.erase(a[i - k]);
    }

    if (i >= k - 1) {
      if (nums.empty()) cout << "Nothing" << endl;
      else cout << *nums.rbegin() << endl;
    }
  }

  return 0;
}