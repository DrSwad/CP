#include <bits/stdc++.h>
using namespace std;

int main() {
	int rows, cols, k;
	scanf("%d %d %d", &rows, &cols, &k);

	vector<vector<int>> grid(rows, vector<int>(cols));
	for (int row = 0; row < rows; row++) {
		for (int col = 0; col < cols; col++) {
			scanf("%d", &grid[row][col]);
		}
	}

	int ans = 0;

	for (int mask = 0; mask < 1 << cols; mask++) {
		int cnt = __builtin_popcount(mask);

		if (cnt <= k and cnt % 2 == k % 2) {
			int cur = 0;
			for (int row = 0; row < rows; row++) {
				bool okay = true;
				for (int col = 0; col < cols; col++) {
					if (grid[row][col] ^ (mask >> col & 1) == 0) {
						okay = false;
						break;
					}
				}
				cur += okay;
			}
			ans = max(ans, cur);
		}
	}

	printf("%d\n", ans);

	return 0;
}