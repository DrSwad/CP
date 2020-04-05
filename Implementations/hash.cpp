typedef unsigned long long hash;
#define BASE 79
const hash MOD = 10000000000000061LL, codes[] = {59, 61, 3, 73, 79, 2, 89, 97, 103, 107, 109, 113, 5, 137, 139, 151, 157, 163, 167, 173, 181, 191, 193, 199, 211, 223, 227, 229, 233, 239, 241, 251, 257, 263, 269, 271, 277, 293};

char s[MAXN];
hash pows[MAXN];
hash pref[MAXN];

hash mul(hash a, hash b, hash m) {
	hash q = (hash)((long double)a * (long double)b / (long double)m);
	hash r = a * b - q * m;
	return (r + 5 * m) % m;
}

void prepocessHash() {
	pows[0] = BASE;
	for (int i = 1; i < n; i++) {
		pows[i] = mul(pows[i - 1], BASE, MOD);
	}

	hash current = 0;
	for (int i = 0; i < n; i++) {
		hash tmp = pows[i] * (hash)codes['z' - s[i]];
		current = (current + tmp) % MOD;
		pref[i] = current;
	}
}

hash substringHash(int i, int j) {
	if (i == 0) {
		return pref[j];
	}
	if (pref[j] >= pref[i - 1]) {
		return pref[j] - pref[i - 1];
	}
	return pref[j] + MOD - pref[i - 1];
}