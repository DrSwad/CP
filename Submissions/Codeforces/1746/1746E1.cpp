#include <bits/stdc++.h>
using namespace std;

bool query(vector<int> S) {
  cout << "? " << S.size();
  for (int i : S) cout << " " << i + 1;
  cout << endl;
  string res;
  cin >> res;
  return res == "YES";
}

void answer(int ans) {
  cout << "! " << ans + 1 << endl;
  string res;
  cin >> res;
  if (res == ":)") exit(EXIT_SUCCESS);
}

vector<int> prune(vector<int> S) {
  assert(!S.empty());

  int n = S.size();
  vector<int> state(n, -1);

  vector<int> S1, S2;
  bool res1, res2;

  for (int i = 0; i < n; i++) {
    if (i % 2 < 1) S1.push_back(S[i]);
    if (i % 4 < 2) S2.push_back(S[i]);
  }

  res1 = query(S1);
  res2 = query(S2);

  vector<int> nS;
  for (int i = 0; i < n; i++) {
    int in1 = i % 2 < 1;
    int in2 = i % 4 < 2;
    if (in1 == res1 or in2 == res2) {
      nS.push_back(S[i]);
    }
  }

  return nS;
}

void solve3(vector<int> S) {
  assert(S.size() == 3);
  for (int it = 0; it < 2; it++) {
    if (!query({S[0], S[1]})) {
      answer(S[2]);

      if (query({S[0]})) answer(S[0]);
      else answer(S[1]);
    }
  }

  answer(S[0]);
  answer(S[1]);
}

int main() {
  int n;
  cin >> n;

  if (n == 1) answer(0);
  if (n == 2) answer(0), answer(1);

  vector<int> S(n);
  iota(S.begin(), S.end(), 0);

  while (S.size() != 3) {
    S = prune(S);
  }

  solve3(S);

  return 0;
}