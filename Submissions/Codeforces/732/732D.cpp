#include <bits/stdc++.h>
using namespace std;

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);

  int days, subjects;
  cin >> days >> subjects;

  vector<int> subject_on_day(days);
  for (int &i : subject_on_day) cin >> i, i--;

  vector<int> preparation_needed(subjects);
  for (int &i : preparation_needed) cin >> i;

  function<bool(int)> check =
    [&](int total_days) {
      vector<int> last_day_for_subject(subjects, -1);
      for (int day = 0; day < total_days; day++) {
        int subject = subject_on_day[day];
        if (subject != -1) {
          last_day_for_subject[subject] = day;
        }
      }

      int free_days = 0;
      int passed_subjects = 0;

      for (int day = 0; day < total_days; day++) {
        int subject = subject_on_day[day];
        if (subject != -1 and last_day_for_subject[subject] == day) {
          if (free_days < preparation_needed[subject]) return false;
          free_days -= preparation_needed[subject];
          passed_subjects++;
        }
        else {
          free_days++;
        }
      }

      return passed_subjects == subjects;
    };

  int L = 0, R = days + 1;
  while (R - L > 1) {
    int mid = (L + R) / 2;
    if (check(mid)) R = mid;
    else L = mid;
  }

  if (R > days) cout << "-1\n";
  else cout << R << "\n";

  return 0;
}