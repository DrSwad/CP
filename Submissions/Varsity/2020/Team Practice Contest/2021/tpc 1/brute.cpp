#include <bits/stdc++.h>
using namespace std;

const int N = 405;

int n;
int d[N];
int t[3][N];
bool poss[3][N][N];

void go(int id1, int st1, int id2, int st2) {
  int dpi;
  if (id1 == 0 and id2 == 1) dpi = 0;
  if (id1 == 0 and id2 == 2) dpi = 1;
  if (id1 == 1 and id2 == 2) dpi = 2;

  int done1 = 0, done2 = 0;
  bool moved1 = false, moved2 = false;
  for (int at1 = st1, at2 = st2; (!moved1 or at1 != st1) and (!moved2 or at2 != st2); ) {
    if (at1 == at2) return void(poss[dpi][st1][st2] = false);
    int takes1 = t[id1][at1] + d[at1] - done1;
    int takes2 = t[id2][at2] + d[at2] - done2;

    if (takes1 < takes2) {
      at1++;
      if (at1 == n) at1 = 0;
      done1 = 0;
      done2 += takes1;
      moved1 = true;
    } else if (takes2 < takes1) {
      at2++;
      if (at2 == n) at2 = 0;
      done2 = 0;
      done1 += takes2;
      moved2 = true;
    } else {
      at1++, at2++;
      if (at1 == n) at1 = 0;
      if (at2 == n) at2 = 0;
      done1 = done2 = 0;
      moved1 = moved2 = true;
    }
  }

  return void(poss[dpi][st1][st2] = true);
}

int go(int id, int from, int time) {
  int at = from;
  do {
    int need = t[id][at] + d[at];
    if (time < need) break;
    time -= need;
    at++;
    if (at == n) at = 0;
  } while (at != from);
  return at == from ? -1 : at;
}

int collides(vector<int> st) {
  for (int T = 0; T < 1000; T++) {
    vector<int> at(3);
    for (int i = 0; i < 3; i++) {
      at[i] = go(i, st[i], T);
    }
    for (int i = 0; i < 3; i++) {
      for (int j = i + 1; j < 3; j++) {
        if (~at[i] and at[i] == at[j]) {
          return T;
        }
      }
    }
  }
  return -1;
}

int main() {
  scanf("%d", &n);
  for (int i = 0; i < n; i++) scanf("%d", &d[i]);
  for (int it = 0; it < 3; it++) {
    for (int i = 0; i < n; i++) scanf("%d", &t[it][i]);
  }

  for (int id1 = 0; id1 < 3; id1++) {
    for (int id2 = id1 + 1; id2 < 3; id2++) {
      for (int st1 = 0; st1 < n; st1++) {
        for (int st2 = 0; st2 < n; st2++) {
          go(id1, st1, id2, st2);
        }
      }
    }
  }

  for (int st1 = 0; st1 < n; st1++) {
    for (int st2 = 0; st2 < n; st2++) {
      for (int st3 = 0; st3 < n; st3++) {
        if (poss[0][st1][st2] and poss[1][st1][st3] and poss[2][st2][st3]) {
          printf("%d %d %d", st1 + 1, st2 + 1, st3 + 1);
          puts("");
          return 0;
        }
      }
    }
  }

  puts("impossible");

  return 0;
}