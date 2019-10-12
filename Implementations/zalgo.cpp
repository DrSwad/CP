#include <bits/stdc++.h>

using namespace std;

const int N = 1e5 + 10;

int n;
string s;
int z[N];

void zalgo() {
	int L = 0, R = 0;
	for (int i = 1; i < n; i++) {
		if (i > R) {
			L = R = i;
			while (R < n && s[R - L] == s[R]) R++;
			z[i] = R - L;
			R--;
		}
		else {
			int k = i - L;
			if (z[k] < R - i + 1) z[i] = z[k];
			else {
				L = i;
				while (R < n && s[R - L] == s[R]) R++;
				z[i] = R - L;
				R--;
			}
		}
	}
}

int main() {
	#ifdef LOCAL
	freopen("in", "r", stdin);
	freopen("out", "w", stdout);
	#endif

	n = 5;
	s = "ababa";
	zalgo();
	for (int i = 1; i < 5; i++) cerr << z[i] << " ";

	return 0;
}