// Online C++ compiler to run C++ program online
#include <bits/stdc++.h>
using namespace std;

int le = 1;
int ri = 2;
int up = 3;
int down = 4;
int all = 0;

struct tpos {
  int x;
  int y;
  int t;
  int prevdir;
};

int vals[100][100];
bool vi[100][100];
tpos st;
int n;
int m;

int main() {
  int t;
  cin >> t;
  while (t--) {
    for (int i = 0; i < 100; i++) {
      for (int j = 0; j < 100; j++) {
        vi[i][j] = false;
      }
    }

    cin >> n;
    cin >> m;
    cin >> st.x;
    cin >> st.y;
    st.t = 1;
    st.prevdir = all;
    int l;
    cin >> l;
    for (int i = 0; i <= n; i++)
    {
      for (int j = 0; j <= m; j++)
      {
        if (i < n && j < m) cin >> vals[i][j];
        else vals[i][j] = 0;
      }
    }

    int ans = 0;
    queue<tpos> q;
    q.push(st);

    while (!q.empty()) {
      tpos temp = q.front();
      int x = temp.x;
      int y = temp.y;
      int T = temp.t;
      int pd = temp.prevdir;
      // cout << "x = " << x << " y = " << y << " t = " << T << " pd = " << pd << " ans = " << ans << endl;
      q.pop();

      if (vi[x][y]) continue;
      vi[x][y] = true;
      if (T == l + 1 || vals[x][y] == 0) continue;

      tpos temp1 = temp;
      temp1.t = T + 1;
      tpos temp2 = temp1;

      if (vals[x][y] == 1) {
        if (x != 0) {
          temp2.x = x - 1;
          temp2.prevdir = up;
          q.push(temp2);
        }

        temp2 = temp1;
        temp2.x = x + 1;
        temp2.prevdir = down;
        q.push(temp2);

        if (y != 0) {
          temp2 = temp1;
          temp2.y = y - 1;
          temp2.prevdir = le;
          q.push(temp2);
        }

        temp2 = temp1;
        temp2.y = y + 1;
        temp2.prevdir = ri;
        q.push(temp2);
      }

      if (vals[x][y] == 2) {
        if (pd == all) {
          temp2.x = x + 1;
          temp2.prevdir = down;
          q.push(temp2);

          temp2 = temp1;
          if (x != 0) {
            temp2.x = x - 1;
            temp2.prevdir = up;
            q.push(temp2);
          }
        }
        else if (pd == down) {
          temp2.x = x + 1;
          temp2.prevdir = down;
          q.push(temp2);
        }
        else if (pd == up) {
          if (x != 0) {
            temp2.x = x - 1;
            temp2.prevdir = up;
            q.push(temp2);
          }
        }
        else continue;
      }

      if (vals[x][y] == 3) {
        if (pd == all) {
          temp2.y = y + 1;
          temp2.prevdir = ri;
          q.push(temp2);

          temp2 = temp1;
          if (y != 0) {
            temp2.y = y - 1;
            temp2.prevdir = le;
            q.push(temp2);
          }
        }

        else if (pd == ri) {
          temp2.y = y + 1;
          temp2.prevdir = ri;
          q.push(temp2);
        }
        else if (pd == le) {
          if (y != 0) {
            temp2.y = y - 1;
            temp2.prevdir = le;
            q.push(temp2);
          }
        }
        else continue;
      }

      if (vals[x][y] == 4) {
        if (pd == all) {
          temp2.y = y + 1;
          temp2.prevdir = ri;
          q.push(temp2);

          temp2 = temp1;
          if (x != 0) {
            temp2.x = x - 1;
            temp2.prevdir = up;
            q.push(temp2);
          }
        }

        else if (pd == le) {
          if (x != 0) {
            temp2.x = x - 1;
            temp2.prevdir = up;
            q.push(temp2);
          }
        }

        else if (pd == down) {
          temp2.y = y + 1;
          temp2.prevdir = ri;
          q.push(temp2);
        }
        else continue;
      }

      if (vals[x][y] == 5) {
        if (pd == all) {
          temp2.y = y + 1;
          temp2.prevdir = ri;
          q.push(temp2);

          temp2 = temp1;
          temp2.x = x + 1;
          temp2.prevdir = down;
          q.push(temp2);
        }

        else if (pd == le) {
          temp2.x = x + 1;
          temp2.prevdir = down;
          q.push(temp2);
        }

        else if (pd == up) {
          temp2.y = y + 1;
          temp2.prevdir = ri;
          q.push(temp2);
        }
        else continue;
      }

      if (vals[x][y] == 6) {
        if (pd == all) {
          if (y != 0) {
            temp2.y = y - 1;
            temp2.prevdir = le;
            q.push(temp2);
          }

          temp2 = temp1;
          temp2.x = x + 1;
          temp2.prevdir = down;
          q.push(temp2);
        }

        else if (pd == ri) {
          temp2.x = x + 1;
          temp2.prevdir = down;
          q.push(temp2);
        }

        else if (pd == up) {
          if (y != 0) {
            temp2.y = y - 1;
            temp2.prevdir = le;
            q.push(temp2);
          }
        }
        else continue;
      }

      if (vals[x][y] == 7) {
        if (pd == all) {
          if (y != 0) {
            temp2.y = y - 1;
            temp2.prevdir = le;
            q.push(temp2);
          }

          if (x != 0) {
            temp2 = temp1;
            temp2.x = x - 1;
            temp2.prevdir = up;
            q.push(temp2);
          }
        }

        else if (pd == ri) {
          if (x != 0) {
            temp2 = temp1;
            temp2.x = x - 1;
            temp2.prevdir = up;
            q.push(temp2);
          }
        }

        else if (pd == down) {
          if (y != 0) {
            temp2.y = y - 1;
            temp2.prevdir = le;
            q.push(temp2);
          }
        }
        else continue;
      }
      ans++;

    }
    printf("%d\n", ans);
  }
}