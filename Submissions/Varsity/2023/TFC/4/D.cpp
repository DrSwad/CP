#include <bits/stdc++.h>
using namespace std;

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);

  const int WEEK_SZ = 7;
  const string week_days[] = {"monday", "tuesday", "wednesday", "thursday", "friday", "saturday", "sunday"};
  const int MONTH_SZ = 12;
  const int month_days[] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};

  int w1, w2;
  {
    string day1, day2;
    cin >> day1 >> day2;
    w1 = find(week_days, week_days + WEEK_SZ, day1) - week_days;
    w2 = find(week_days, week_days + WEEK_SZ, day2) - week_days;
  }

  for (int month = 0; month < MONTH_SZ - 1; month++) {
    int w3 = (w1 + month_days[month]) % WEEK_SZ;
    if (w2 == w3) {
      cout << "YES\n";
      return 0;
    }
  }

  cout << "NO\n";

  return 0;
}