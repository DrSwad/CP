void initSp(int n) {
	memset(P, -1, sizeof P);
	for (int i = 0; i < n; i++) {
		P[0][i] = par[i];
	}
	for (int i = 1; i < LOGN; i++) {
		for (int j = 0; j < n; j++) {
			if (P[i - 1][j] != -1) {
				P[i][j] = P[i - 1][P[i - 1][j]];
			}
		}
	}
}