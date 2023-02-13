#include <bits/stdc++.h>
using namespace std;

vector<vector<int>> solve_bottom_right(int dx, int dy, int m, const vector<pair<int, int>> &shops) {
  int n = shops.size();

  vector<vector<int>> triangle_carry(dx, vector<int>(dy, 0));
  vector<vector<int>> rect_carry(dx, vector<int>(dy, 0));

  auto rect_add = [&](int x1, int y1, int x2, int y2, int add) {
    x1 = max(0, x1);
    x2 = min(x2, dx - 1);
    y1 = max(0, y1);
    y2 = min(y2, dy - 1);
    if (x2 >= x1 and y2 >= y1) {
      rect_carry[x2][y1] += add;
      if (x1 - 1 >= 0) rect_carry[x1 - 1][y1] -= add;
      if (y2 + 1 <= dy - 1) rect_carry[x2][y2 + 1] -= add;
      if (x1 - 1 >= 0 and y2 + 1 <= dy - 1) rect_carry[x1 - 1][y2 + 1] += add;
    }
  };

  auto triangle_add = [&](int x, int y, int add) {
    if (y < 0) x -= (-y), y += (-y);
    if (x >= 0) {
      if (x >= dx) {
        rect_add(0, y, dx - 1, y + (x - dx), add);
        int steps = x - (dx - 1);
        x -= steps;
        y += steps;
      }

      if (y < dy) {
        triangle_carry[x][y] += add;
      }
    }
  };

  vector<vector<int>> dp(dx, vector<int>(dy, 0));

  for (auto [x, y] : shops) {
    triangle_add(x + m, y, 1);
    triangle_add(x - 1, y + m + 1, -1);
    rect_add(0, y, x - 1, y + m, -1);
    // cerr << "State after adding shop " << x << " " << y << "\n";
    // cerr << "Rect carry:\n";
    // for (int x = 0; x < dx; x++) {
    //   for (int y = 0; y < dx; y++) {
    //     cerr << rect_carry[x][y] << " ";
    //   }
    //   cerr << endl;
    // }
    // cerr << "Triangle carry:\n";
    // for (int x = 0; x < dx; x++) {
    //   for (int y = 0; y < dx; y++) {
    //     cerr << triangle_carry[x][y] << " ";
    //   }
    //   cerr << endl;
    // }
  }

  for (int y = 0; y < dy; y++) {
    for (int x = dx - 1; x >= 0; x--) {
      if (x + 1 < dx) triangle_carry[x][y] += triangle_carry[x + 1][y];
      if (x + 1 < dx) rect_carry[x][y] += rect_carry[x + 1][y];
    }
    for (int x = dx - 1; x >= 0; x--) {
      if (x + 1 < dx and y - 1 >= 0) triangle_carry[x][y] += triangle_carry[x + 1][y - 1];
      if (y - 1 >= 0) rect_carry[x][y] += rect_carry[x][y - 1];
      dp[x][y] = triangle_carry[x][y] + rect_carry[x][y];
    }
  }

  // cerr << "State after adding all the shops\n";
  // cerr << "Rect carry:\n";
  // for (int x = 0; x < dx; x++) {
  //   for (int y = 0; y < dx; y++) {
  //     cerr << rect_carry[x][y] << " ";
  //   }
  //   cerr << endl;
  // }
  // cerr << "Triangle carry:\n";
  // for (int x = 0; x < dx; x++) {
  //   for (int y = 0; y < dx; y++) {
  //     cerr << triangle_carry[x][y] << " ";
  //   }
  //   cerr << endl;
  // }

  return dp;
}

void test_case(int dx, int dy, int n, int q) {
  vector<pair<int, int>> shops(n);

  for (auto & [x, y] : shops) {
    cin >> x >> y;
    x--, y--;
  }

  while (q--) {
    int m;
    cin >> m;

    vector<vector<int>> dp(dx, vector<int>(dy, 0));

    // bottom-right
    {
      vector<pair<int, int>> nshops = shops;
      vector<vector<int>> ndp = solve_bottom_right(dx, dy, m, nshops);
      for (int x = 0; x < dx; x++) {
        for (int y = 0; y < dy; y++) {
          dp[x][y] += ndp[x][y];
        }
      }
    }

    // cerr << "Status after bottom-right\n";
    // for (int x = 0; x < dx; x++) {
    //   for (int y = 0; y < dy; y++) {
    //     cerr << dp[x][y] << " ";
    //   }
    //   cerr << endl;
    // }

    // top-right
    if (m >= 1) {
      vector<pair<int, int>> nshops;
      for (auto [x, y] : shops) {
        if (x - 1 >= 0) {
          nshops.emplace_back((dx - 1) - (x - 1), y);
        }
      }

      vector<vector<int>> ndp = solve_bottom_right(dx, dy, m - 1, nshops);
      for (int x = 0; x < dx; x++) {
        for (int y = 0; y < dy; y++) {
          dp[x][y] += ndp[(dx - 1) - x][y];
        }
      }
    }

    // bottom-left
    if (m >= 1) {
      vector<pair<int, int>> nshops;
      for (auto [x, y] : shops) {
        if (y - 1 >= 0) {
          nshops.emplace_back(x, (dy - 1) - (y - 1));
        }
      }

      vector<vector<int>> ndp = solve_bottom_right(dx, dy, m - 1, nshops);
      for (int x = 0; x < dx; x++) {
        for (int y = 0; y < dy; y++) {
          dp[x][y] += ndp[x][(dy - 1) - y];
        }
      }
    }

    // top-left
    if (m >= 2) {
      vector<pair<int, int>> nshops;
      for (auto [x, y] : shops) {
        if (x - 1 >= 0 and y - 1 >= 0) {
          nshops.emplace_back((dx - 1) - (x - 1), (dy - 1) - (y - 1));
        }
      }

      vector<vector<int>> ndp = solve_bottom_right(dx, dy, m - 2, nshops);
      for (int x = 0; x < dx; x++) {
        for (int y = 0; y < dy; y++) {
          dp[x][y] += ndp[(dx - 1) - x][(dy - 1) - y];
        }
      }
    }

    int mx = 0;
    for (int x = 0; x < dx; x++) {
      for (int y = 0; y < dy; y++) {
        mx = max(mx, dp[x][y]);
      }
    }

    int ans_x = -1, ans_y;
    for (int y = 0; y < dy; y++) {
      for (int x = 0; x < dx; x++) {
        if (dp[x][y] == mx and ans_x == -1) {
          ans_x = x, ans_y = y;
        }
      }
    }

    cout << mx << " (" << ans_x + 1 << "," << ans_y + 1 << ")\n";
  }
}

int main() {
  // freopen("in_E.txt", "r", stdin);

  int dx, dy, n, q;
  for (int cs = 1; ; cs++) {
    cin >> dx >> dy >> n >> q;
    if (dx) {
      cout << "Case " << cs << ":\n";
      test_case(dx, dy, n, q);
    }
    else {
      break;
    }
  }

  return 0;
}