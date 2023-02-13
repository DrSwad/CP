#include <bits/stdc++.h>
using namespace std;

int g[2];
int p[2];
int s;

void processPoint(int to) {
  p[to]++;
  if (p[to] == 10 or (p[to] >= 5 and p[to] - p[to ^ 1] >= 2)) {
    g[to]++;
    p[0] = p[1] = 0;
  }
  s = to;
}

void announce() {
  string a = to_string(g[0]), b = to_string(g[1]);
  if (g[0] >= 2 or g[1] >= 2) {
    (!s ? a : b) += string(" (winner)");
  } else {
    a += string(" (") + to_string(p[0])
        + (s == 0 ? string("*") : string("")) + string(")");
    b += string(" (") + to_string(p[1])
        + (s == 1 ? string("*") : string("")) + string(")");
  }
  cout << a << " - " << b << endl;
}

int main() {
  string str;
  cin >> str;

  for (char c : str) {
    if (c == 'Q') {
      announce();
    } else {
      processPoint((s == 1) == (c == 'S'));
    }
  }

  return 0;
}