#include <bits/stdc++.h>
 
using namespace std;
 
#define debug(a) cerr << #a << ": " << a << endl
 
typedef long long ll;
typedef pair<int, int> ii;
 
#define x first
#define y second
 
const int N = 1005;

class segTree {
private:
	int length;
	int U, D;
	int (*arr)[N];
	int st[4 * N];
	segTree *l_child, *r_child;
public:
	segTree(int arr[][N], int U, int D, int length) {
		this->arr = arr;
		this->U = U;
		this->D = D;
		this->length = length;
		if (U < D) {
			int mid = (U + D) / 2;
			l_child = new segTree(arr, U, mid, length);
			r_child = new segTree(arr, mid + 1, D, length);
		}
		build(1, 1, length);
	}
	void build(int stI, int L, int R) {
		if (L == R) {
			if (U == D) {
				st[stI] = arr[U][L];
			}
			else {
				int mid = (U + D) / 2;
				st[stI] = l_child->query(L, R, 1, 1, length) + r_child->query(L, R, 1, 1, length);
			}

			return;
		}

		int mid = (L + R) / 2;
		build((stI << 1), L, mid);
		build((stI << 1) + 1, mid + 1, R);

		st[stI] = st[(stI << 1)] + st[(stI << 1) + 1];
	}
	int query(int l, int r, int stI, int L, int R) {
		if (r < L || R < l) return 0;

		if (l <= L && R <= r) return st[stI];

		int mid = (L + R) / 2;
		int q1 = query(l, r, (stI << 1), L, mid);
		int q2 = query(l, r, (stI << 1) + 1, mid + 1, R);

		return q1 + q2;
	}
	int query(int x1, int x2, int y1, int y2) {
		if (x2 < U || D < x1) return 0;

		if (x1 <= U && D <= x2) return query(y1, y2, 1, 1, length);

		int q1 = l_child->query(x1, x2, y1, y2);
		int q2 = r_child->query(x1, x2, y1, y2);

		return q1 + q2;
	}
};

int n, q;
int a[N][N];

int main() {
	#ifdef LOCAL
	freopen("in", "r", stdin);
	freopen("out", "w", stdout);
	#endif
 
	cin >> n >> q;
	for (int i = 1; i <= n; i++) {
		char s[N];
		scanf(" %s", s + 1);

		for (int j = 1; j <= n; j++)
			a[i][j] = s[j] == '*';
	}
	
	segTree *root = new segTree(a, 1, n, n);

	while (q--) {
		int x1, y1, x2, y2;
		scanf("%d %d %d %d", &x1, &y1, &x2, &y2);

		printf("%d\n", root->query(x1, x2, y1, y2));
	}
 	
	return 0;
}