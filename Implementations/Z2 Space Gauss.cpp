void tryGauss(int mask) {
	for (int i = 0; i < n; i++) {
		if ((mask & 1 << i) == 0) continue;

		if (!basis[i]) {
			basis[i] = mask;
			++sz;
			
			break;
		}

		mask ^= basis[i];
	}
}