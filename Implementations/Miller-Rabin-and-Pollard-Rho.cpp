#include <bits/stdtr1c++.h>

using namespace std;

namespace rho {
	mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());

	const int MAXP = 1000010;
	const int BASE[] = {2, 450775, 1795265022, 9780504, 28178, 9375, 325};

	ll seq[MAXP];
	int primes[MAXP], spf[MAXP];

	inline ll mod_add(ll x, ll y, ll m){
		return (x += y) < m ? x : x - m;
	}

	inline ll mod_mul(ll x, ll y, ll m){
		ll res = x * y - (ll)((ld)x * y / m + 0.5) * m;
		return res < 0 ? res + m : res;
	}

	inline ll mod_pow(ll x, ll n, ll m){
		ll res = 1 % m;
		for (; n; n >>= 1){
			if (n & 1) res = mod_mul(res, x, m);
			x = mod_mul(x, x, m);
		}
		return res;
	}

	/// O(k logn logn logn), k = number of rounds performed
	inline bool miller_rabin(ll n){
		if (n <= 2 || (n & 1 ^ 1)) return (n == 2);
		if (n < MAXP) return spf[n] == n;

		ll c, d, s = 0, r = n - 1;
		for (; !(r & 1); r >>= 1, s++) {}

		/// each iteration is a round
		for (int i = 0; primes[i] < n && primes[i] < 32; i++){
			c = mod_pow(primes[i], r, n);
			for (int j = 0; j < s; j++){
				d = mod_mul(c, c, n);
				if (d == 1 && c != 1 && c != (n - 1)) return false;
				c = d;
			}
			if (c != 1) return false;
		}
		return true;
	}

	inline void init(){
		int i, j, k, cnt = 0;
		for (i = 2; i < MAXP; i++){
			if (!spf[i]) primes[cnt++] = spf[i] = i;
			for (j = 0, k; (k = i * primes[j]) < MAXP; j++){
				spf[k] = primes[j];
				if(spf[i] == spf[k]) break;
			}
		}
	}

	/// Expected complexity O(n^(1/4))
	ll pollard_rho(ll n){
		while (1){
			ll x = rand() % n, y = x, c = rand() % n, u = 1, v, t = 0;
			ll *px = seq, *py = seq;

			while (1){
				*py++ = y = mod_add(mod_mul(y, y, n), c, n);
				*py++ = y = mod_add(mod_mul(y, y, n), c, n);
				if((x = *px++) == y) break;

				v = u;
				u = mod_mul(u, abs(y - x), n);

				if (!u) return __gcd(v, n);
				if (++t == 32){
					t = 0;
					if ((u = __gcd(u, n)) > 1 && u < n) return u;
				}
			}
			if (t && (u = __gcd(u, n)) > 1 && u < n) return u;
		}
	}

	vector <ll> factorize(ll n){
		if (n == 1) return vector <ll>();
		if (miller_rabin(n)) return vector<ll> {n};

		vector <ll> v, w;
		while (n > 1 && n < MAXP){
			v.push_back(spf[n]);
			n /= spf[n];
		}
		if (n >= MAXP) {
			ll x = pollard_rho(n);
			v = factorize(x);
			w = factorize(n / x);
			v.insert(v.end(), w.begin(), w.end());
		}
		sort(v.begin(), v.end());
		return v;
	}
}
int main(){
	rho::init();
	vector <ll> v = rho::factorize(n);
	return 0;
}
