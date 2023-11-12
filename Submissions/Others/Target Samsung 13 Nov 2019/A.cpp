#include<bits/stdc++.h>
using namespace std;

int main() {
	int t;
	scanf("%d", &t);

	while (t--) {
		int n;
		scanf("%d", &n);

		vector<vector<int>> cost(n, vector<int>(n));
		for (int i = 0; i < n; i++) {
			for (int j = 0; j < n; j++) {
				scanf("%d", &cost[i][j]);
			}
		}

		vector<vector<int>> dp(1 << n, vector<int>(n, -1));
		dp[1 << 0][0] = 0;

		for (int mask = 3; mask < 1 << n; mask += 2) {
			for (int last = 0; last < n; last++) {
				if (mask >> last & 1) {
					int prv_mask = mask ^ 1 << last;
					for (int prv = 0; prv < n; prv++) {
						if (prv_mask >> prv & 1 and dp[prv_mask][prv] != -1) {
							int &ans = dp[mask][last];
							int cur = dp[prv_mask][prv] + cost[prv][last];
							ans = ans == -1 ? cur : min(ans, cur);
						}
					}
				}
			}
		}

		int ans = INT_MAX;
		int full_mask = (1 << n) - 1;
		for (int i = 0; i < n; i++) {
			if (dp[full_mask][i] != -1) {
				ans = min(ans, dp[full_mask][i] + cost[i][0]);
			}
		}

		printf("%d\n", ans);
	}

	return 0;
}