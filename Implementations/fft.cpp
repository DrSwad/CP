#include <bits/stdc++.h>

using namespace std;

typedef long long ll;
typedef complex<double> base;

const int N = 1e5 + 10;
const double PI = acos(-1);

void fft(vector<base> &a, bool inv) {
	int n = a.size();
	int j = 0;

	for (int i = 1; i < n; i++) {
		int bit = n >> 1;

		while (j >= bit) {
			j -= bit;
			bit >>= 1;
		}
		j += bit;

		if (i < j) swap(a[i], a[j]);
	}

	vector<base> roots(n / 2);
	double ang = 2 * PI / n * (inv ? -1 : 1);
	for (int i = 0; i < n / 2; i++)
		roots[i] = base(cos(ang * i), sin(ang * i));

	for (int i = 2; i <= n; i <<= 1) {
		int step = n / i;

		for (int j = 0; j < n; j += i) {
			for (int k = 0; k < i / 2; k++) {
				base u = a[j + k], v = a[j + k + i / 2] * roots[k * step];
				a[j + k] = u + v;
				a[j + k + i / 2] = u - v;
			}
		}
	}

	if (inv) for (int i = 0; i < n; i++) a[i] /= n;
}

vector<ll> multiply(vector<ll> &a, vector<ll> &b) {
	vector<base> fa(a.begin(), a.end()), fb(b.begin(), b.end());

	int n = 2;
	while (n < a.size() + b.size()) n <<= 1;

	fa.resize(n);
	fft(fa, false);

	fb.resize(n);
	fft(fb, false);

	for (int i = 0; i < n; i++) fa[i] *= fb[i];

	fft(fa, 1);
	vector<ll> ret(n);
	for (int i = 0; i < n; i++) ret[i] = (ll)round(fa[i].real());

	return ret;
}

int main() {
	vector<ll> a = {1, 2, 1}, b = {0, 1, 1};
	vector<ll> mul = multiply(a, b);

	for (int val : mul) cerr << val << " ";

	return 0;
}