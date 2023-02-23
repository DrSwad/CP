#include <bits/stdc++.h>
using namespace std;

string s;
string curr;
long long ans;

void go(int at, long long carry = 0) {
  if (at == s.length()) {
    if (curr == "") ans += carry;
    return;
  }

  curr += s[at];
  go(at + 1, carry);

  carry += stoll(curr);
  string tmp = curr;
  curr = "";
  go(at + 1, carry);
  curr = tmp;
  curr.pop_back();
}

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);

  cin >> s;

  go(0);

  cout << ans << "\n";

  return 0;
}