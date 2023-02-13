#include <bits/stdc++.h>
using namespace std;

struct Rect {
  int u, d, l, r;
};

string to_string(Rect rect) {
  return to_string(rect.u) + string(1, ' ') + to_string(rect.d) + string(1, ' ') + to_string(rect.l) + string(1, ' ') + to_string(rect.r);
}

vector<Rect> split_doubles_nested_in_singles(vector<Rect> rects) {
  int n = rects.size();

  vector<int> order(n);
  iota(order.begin(), order.end(), 0);

  sort(
    order.begin(),
    order.end(),
    [&](int i, int j) {
    return make_pair(rects[i].l, -rects[i].r) < make_pair(rects[j].l, -rects[j].r);
  }
    );

  for (int it = 0; it < 2; it++) {
    int max_r = 0;

    for (int i = 0; i < n; i++) {
      int id = order[i];
      auto&rect = rects[id];

      if ((it == 0 and rect.u == 1) or (it == 1 and rect.d == 2)) {
        if (rect.u != rect.d and max_r >= rect.r) {
          if (it == 0) rect.u = 2;
          else rect.d = 1;
        }
        else max_r = max(max_r, rect.r);
      }
    }
  }

  return rects;
}

vector<Rect> filter_nested_singles(vector<Rect> rects) {
  int n = rects.size();

  vector<int> order(n);
  iota(order.begin(), order.end(), 0);

  sort(
    order.begin(),
    order.end(),
    [&](int i, int j) {
    return make_pair(rects[i].l, -rects[i].r) < make_pair(rects[j].l, -rects[j].r);
  }
    );

  for (int it = 0; it < 2; it++) {
    int max_r = 0;

    for (int i = 0; i < n; i++) {
      int id = order[i];
      auto&rect = rects[id];

      if ((it == 0 and rect.u == 1) or (it == 1 and rect.d == 2)) {
        if (rect.u == rect.d and max_r >= rect.r) rect.u = rect.d = rect.l = rect.r = 0;
        else max_r = max(max_r, rect.r);
      }
    }
  }

  return rects;
}

vector<Rect> trim_singles(vector<Rect> rects) {
  int n = rects.size();

  vector<int> order(n);
  iota(order.begin(), order.end(), 0);

  {
    sort(
      order.begin(),
      order.end(),
      [&](int i, int j) {
      return rects[i].l < rects[j].l;
    }
      );

    for (int it = 0; it < 2; it++) {
      int max_r = 0;

      for (int i = 0; i < n; i++) {
        int id = order[i];
        auto&rect = rects[id];

        if ((it == 0 and rect.u == 1) or (it == 1 and rect.d == 2)) {
          if (rect.d == rect.u) {
            rect.l = max(rect.l, max_r + 1);
            if (rect.l > rect.r) rect.u = rect.d = rect.l = rect.r = 0;
          }
          if (rect.u) max_r = max(max_r, rect.r);
        }
      }
    }
  }

  {
    sort(
      order.begin(),
      order.end(),
      [&](int i, int j) {
      return -rects[i].r < -rects[j].r;
    }
      );

    for (int it = 0; it < 2; it++) {
      int min_l = int(1e9) + 1;

      for (int i = 0; i < n; i++) {
        int id = order[i];
        auto&rect = rects[id];

        if ((it == 0 and rect.u == 1) or (it == 1 and rect.d == 2)) {
          if (rect.d == rect.u) {
            rect.r = min(rect.r, min_l - 1);
            if (rect.l > rect.r) rect.u = rect.d = rect.l = rect.r = 0;
          }
          if (rect.u) min_l = min(min_l, rect.l);
        }
      }
    }
  }

  return rects;
}

vector<Rect> trim_doubles(vector<Rect> rects) {
  int n = rects.size();

  vector<int> order(n);
  iota(order.begin(), order.end(), 0);

  {
    sort(
      order.begin(),
      order.end(),
      [&](int i, int j) {
      return rects[i].l < rects[j].l;
    }
      );

    for (int it = 0; it < 2; it++) {
      int max_r = 0;

      for (int i = 0; i < n; i++) {
        int id = order[i];
        auto&rect = rects[id];
        if (rect.u == rect.d) continue;

        if ((it == 0 and rect.u == 1) or (it == 1 and rect.d == 2)) {
          rect.l = max(rect.l, max_r + 1);
          if (rect.l > rect.r) rect.u = rect.d = rect.l = rect.r = 0;
          if (rect.u) max_r = max(max_r, rect.r);
        }
      }
    }
  }

  {
    sort(
      order.begin(),
      order.end(),
      [&](int i, int j) {
      return -rects[i].r < -rects[j].r;
    }
      );

    for (int it = 0; it < 2; it++) {
      int min_l = int(1e9) + 1;

      for (int i = 0; i < n; i++) {
        int id = order[i];
        auto&rect = rects[id];
        if (rect.u == rect.d) continue;

        if ((it == 0 and rect.u == 1) or (it == 1 and rect.d == 2)) {
          rect.r = min(rect.r, min_l - 1);
          if (rect.l > rect.r) rect.u = rect.d = rect.l = rect.r = 0;
          if (rect.u) min_l = min(min_l, rect.l);
        }
      }
    }
  }

  return rects;
}

void test_case() {
  int n;
  cin >> n;

  vector<Rect> rects(n);
  for (auto &rect : rects) {
    cin >> rect.u >> rect.l >> rect.d >> rect.r;
  }

  rects = split_doubles_nested_in_singles(rects);
  rects = filter_nested_singles(rects);
  rects = trim_singles(rects);
  rects = trim_doubles(rects);

  int s = 0;
  for (auto rect : rects) {
    if (rect.u) {
      s += (rect.d - rect.u + 1) * (rect.r - rect.l + 1);
    }
  }
  cout << s << "\n";

  for (auto rect : rects) {
    cout << rect.u << " " << rect.l << " " << rect.d << " " << rect.r << "\n";
  }
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