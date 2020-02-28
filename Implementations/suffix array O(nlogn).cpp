// Everything is 0-indexed
char s[N]; // Suffix array will be built for this string
int SA[N], iSA[N]; // SA is the suffix array, iSA[i] stores the rank of the i'th suffix
int cnt[N], nxt[N]; // Internal stuff
bool bh[N], b2h[N]; // Internal stuff
int lcp[N]; // Stores lcp of SA[i] and SA[i + 1]; lcp[n - 1] = 0
int lcpSparse[LOGN][N]; // lcpSparse[i][j] = min(lcp[j], ..., lcp[j - 1 + (1 << i)])

void buildSA(int n) {
	for (int i = 0; i < n; i++) SA[i] = i;
	sort(SA, SA + n, [](int i, int j) { return s[i] < s[j]; });

	for (int i = 0; i < n; i++) {
		bh[i] = i == 0 || s[SA[i]] != s[SA[i - 1]];
		b2h[i] = 0;
	}

	for (int h = 1; h < n; h <<= 1) {
		int tot = 0;
		for (int i = 0, j; i < n; i = j) {
			j = i + 1;
			while (j < n && !bh[j]) j++;
			nxt[i] = j; tot++;
		} if (tot == n) break;

		for (int i = 0; i < n; i = nxt[i]) {
			for (int j = i; j < nxt[i]; j++)
				iSA[SA[j]] = i;
			cnt[i] = 0;
		}

		cnt[iSA[n - h]]++;
		b2h[iSA[n - h]] = 1;
		for (int i = 0; i < n; i = nxt[i]) {
			for (int j = i; j < nxt[i]; j++) {
				int s = SA[j] - h;
				if (s < 0) continue;
				int head = iSA[s];
				iSA[s] = head + cnt[head]++;
				b2h[iSA[s]] = 1;
			}
			for (int j = i; j < nxt[i]; j++) {
				int s = SA[j] - h;
				if (s < 0 || !b2h[iSA[s]]) continue;
				for (int k = iSA[s] + 1; !bh[k] && b2h[k]; k++)
					b2h[k] = 0;
			}
		}
		for (int i = 0; i < n; i++) {
			SA[iSA[i]] = i;
			bh[i] |= b2h[i];
		}
	}
	for (int i = 0; i < n; i++) iSA[SA[i]] = i;
}

void buildLCP(int n) {
	for (int i = 0, k = 0; i < n; i++) {
		if (iSA[i] == n - 1) {
			k = 0;
			lcp[n - 1] = 0;
			continue;
		}
		int j = SA[iSA[i] + 1];
		while (i + k < n && j + k < n && s[i + k] == s[j + k]) k++;
		lcp[iSA[i]] = k;
		if (k) k--;
	}
}

void buildLCPSparse(int n) {
	for (int i = 0; i < n; i++) lcpSparse[0][i] = lcp[i];
	for (int i = 1; i < LOGN; i++) {
		for (int j = 0; j < n; j++) {
			lcpSparse[i][j] = min(lcpSparse[i - 1][j], lcpSparse[i - 1][min(n - 1, j + (1 << (i - 1)))]);
		}
	}
}

pair<int, int> minLCPRange(int n, int from, int minLCP) {
	int r = from;
	for (int i = LOGN - 1; i >= 0; i--) {
		if (r + (1 << i) >= n) continue;
		if (lcpSparse[i][r] >= minLCP) r += 1 << i;
	}

	int l = from;
	for (int i = LOGN - 1; i >= 0; i--) {
		if (l - (1 << i) < 0) continue;
		if (lcpSparse[i][l - (1 << i)] >= minLCP) l -= 1 << i;
	}

	return make_pair(l, r);
}