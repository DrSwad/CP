#include <bits/stdc++.h>

using namespace std;
typedef vector<int> vi;
#define mp make_pair

struct SA {
	const int L;
	string s;
	vector<vi> P;
	vector<pair<pair<int,int>,int>> M;

	SA(const string &s) : L(s.length()), s(s), P(1, vi(L, 0)), M(L) {
		for (int i = 0; i < L; i++) P[0][i] = int(s[i]);
		for (int sk = 1, l = 1; sk < L; sk *= 2, l++) {
			P.push_back(vi(L, 0));
			for (int i = 0; i < L; i++)
				M[i] = mp(mp(P[l - 1][i], i + sk < L ? P[l - 1][i + sk] : -1000), i);
			sort(M.begin(), M.end());
			for (int i = 0; i < L; i++)
				P[l][M[i].second] = (i > 0 && M[i].first == M[i-1].first) ? P[l][M[i-1].second] : i;
		}
	}

	vi GetSA() { return P.back(); }

	// returns the length of the longest common prefix of s[i...L-1] and s[j...L-1]
	int LCP(int i, int j) {
		int len = 0;
		if (i == j) return L - i;
		for (int k = P.size() - 1; k >= 0 && i < L && j < L; k--) {
			if (P[k][i] == P[k][j]) {
				i += 1 << k;
				j += 1 << k;
				len += 1 << k;
			}
		}
		return len;
	}
};

// Usage
int main() {
	// bobocel is the 0'th suffix
	//  obocel is the 5'th suffix
	//   bocel is the 1'st suffix
	//    ocel is the 6'th suffix
	//     cel is the 2'nd suffix
	//      el is the 3'rd suffix
	//       l is the 4'th suffix
	SA suffix("bobocel");
	vi v = suffix.GetSA();

	// Expected output: 0 5 1 6 2 3 4
	//                  2
	for (int i = 0; i < v.size(); i++) cout << v[i] << " ";
	cout << endl;
	cout << suffix.LCP(0, 2) << endl;

	return 0;
}