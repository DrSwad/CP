#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
const int max_progress = 100;
const ll inf_time = 1e18;

void test_case() {
  int jobs, options;
  cin >> jobs >> options;

  vector<int> deadlines(jobs);
  for (int &deadline : deadlines) cin >> deadline;

  vector<int> option_time(options);
  vector<int> option_progress(options);
  vector<vector<int>> job_options(jobs);
  for (int i = 0; i < options; i++) {
    int job;
    cin >> job >> option_time[i] >> option_progress[i];
    job_options[job - 1].push_back(i);
  }

  ll cur_time = 0;
  vector<int> ans;

  for (int job = 0; job < jobs; job++) {
    vector<ll> min_time(max_progress + 1, inf_time);
    vector use_option(1, vector(max_progress + 1, -1));
    min_time[0] = 0;

    for (int i = 0; i < job_options[job].size(); i++) {
      use_option.push_back(use_option.back());
      int option = job_options[job][i];
      for (int nxt_progress = max_progress; nxt_progress >= 0; nxt_progress--) {
        int prv_progress = max(0, nxt_progress - option_progress[option]);
        if (min_time[nxt_progress] > min_time[prv_progress] + option_time[option]) {
          min_time[nxt_progress] = min_time[prv_progress] + option_time[option];
          use_option[i + 1][nxt_progress] = i;
        }
      }
    }

    cur_time += min_time[max_progress];
    if (min_time[max_progress] == inf_time or cur_time > deadlines[job]) {
      cout << "-1\n";
      return;
    }

    int need_progress = max_progress;
    int i = (int)job_options[job].size() - 1;
    while (need_progress > 0) {
      assert(i >= 0);
      i = use_option[i + 1][need_progress];
      assert(i >= 0);
      int option = job_options[job][i];
      need_progress -= option_progress[option];
      ans.push_back(option + 1);
      i--;
    }
  }

  cout << ans.size() << "\n";
  for (int i = 0; i < ans.size(); i++) {
    if (i) cout << " ";
    cout << ans[i];
  }
  cout << "\n";
}

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);

  int t;
  cin >> t;

  for (int cs = 1; cs <= t; cs++) {
    test_case();
  }

  return 0;
}