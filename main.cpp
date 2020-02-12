#include <bits/stdc++.h>

using namespace std;

typedef long long ll;
typedef unsigned int uint;
typedef pair<int, int> pii;
#define x first
#define y second

#ifdef LOCAL
#include "debug.h"
#endif

const int N = int(1e5) + 10;
const int MOD = int(1e9) + 7;

void matmul(int mat1[2][2], int mat2[2][2], int matres[2][2]) {
	ll tmp[2][2];
	tmp[0][0] = mat1[0][0] * 1LL * mat2[0][0] + mat1[0][1] * 1LL * mat2[1][0];
	tmp[0][1] = mat1[0][0] * 1LL * mat2[0][1] + mat1[0][1] * 1LL * mat2[1][1];
	tmp[1][0] = mat1[1][0] * 1LL * mat2[0][0] + mat1[1][1] * 1LL * mat2[1][0];
	tmp[1][1] = mat1[1][0] * 1LL * mat2[0][1] + mat1[1][1] * 1LL * mat2[1][1];
	for (int r = 0; r < 2; r++)
		for (int c = 0; c < 2; c++)
			matres[r][c] = tmp[r][c] % MOD;
}

void matpow(int mat[2][2], ll e) {
	int buff[2][2];
	for (int r = 0; r < 2; r++)
		for (int c = 0; c < 2; c++)
			buff[r][c] = mat[r][c];

	mat[0][0] = mat[1][1] = 1;
	mat[0][1] = mat[1][0] = 0;

	while (e != 0) {
		if (e & 1) matmul(mat, buff, mat);
		matmul(buff, buff, buff);
		e /= 2;
	}
}

void matadd(int mat1[2][2], int mat2[2][2], int matres[2][2]) {
	ll tmp[2][2];
	for (int r = 0; r < 2; r++)
		for (int c = 0; c < 2; c++)
			tmp[r][c] = mat1[r][c] + mat2[r][c];
	for (int r = 0; r < 2; r++)
		for (int c = 0; c < 2; c++)
			matres[r][c] = tmp[r][c] % MOD;
}

int n, m;
int a[N];
int st[4 * N][2][2], lazy[4 * N][2][2];
void build(int stI, int L, int R) {
	lazy[stI][0][0] = lazy[stI][1][1] = 1;
	lazy[stI][0][1] = lazy[stI][1][0] = 0;

	if (L == R) {
		st[stI][0][0] = st[stI][0][1] = st[stI][1][0] = 1;
		st[stI][1][1] = 0;
		matpow(st[stI], a[L] - 1);
		return;
	}

	int mid = (L + R) / 2;
	build((stI << 1), L, mid);
	build((stI << 1) + 1, mid + 1, R);

	matadd(st[(stI << 1)], st[(stI << 1) + 1], st[stI]);
}
void build() {
	build(1, 1, n);
}
void pullUp(int stI) {
	int mat_left[2][2], mat_right[2][2];
	matmul(st[(stI << 1)], lazy[(stI << 1)], mat_left);
	matmul(st[(stI << 1) + 1], lazy[(stI << 1) + 1], mat_right);
	matadd(mat_left, mat_right, st[stI]);
	lazy[stI][0][0] = lazy[stI][1][1] = 1;
	lazy[stI][0][1] = lazy[stI][1][0] = 0;
}
void pushDown(int stI) {
	matmul(lazy[stI], lazy[(stI << 1)], lazy[(stI << 1)]);
	matmul(lazy[stI], lazy[(stI << 1)] + 1, lazy[(stI << 1)] + 1);
	pullUp(stI);
}
void update(int stI, int L, int R, int l, int r, int x) {
	if (r < L || R < l) return;

	if (l <= L && R <= r) {
		int base[2][2] = {{1, 1}, {1, 0}};
		matpow(base, x);
		matmul(base, lazy[stI], lazy[stI]);
		return;
	}

	int mid = (L + R) / 2;
	update((stI << 1), L, mid, l, r, x);
	update((stI << 1) + 1, mid + 1, R, l, r, x);

	pullUp(stI);
}
void update(int l, int r, int x) {
	update(1, 1, n, l, r, x);
}
void query(int stI, int L, int R, int l, int r, int matres[2][2]) {
	if (r < L || R < l) return;

	if (l <= L && R <= r) {
		int curr[2][2];
		matmul(st[stI], lazy[stI], curr);
		matadd(curr, matres, matres);
		return;
	}

	pushDown(stI);
	int mid = (L + R) / 2;
	query((stI << 1), L, mid, l, r, matres);
	query((stI << 1) + 1, mid + 1, R, l, r, matres);
}
void query(int l, int r, int matres[2][2]) {
	query(1, 1, n, l, r, matres);
}

int main() {
	#ifdef LOCAL
	freopen("in", "r", stdin);
	freopen("out", "w", stdout);
	#endif

	scanf("%d %d", &n, &m);
	for (int i = 1; i <= n; i++) scanf("%d", &a[i]);

	build();

	for (int i = 1; i <= m; i++) {
		int type;
		scanf("%d", &type);

		if (type == 1) {
			int l, r, x;
			scanf("%d %d %d", &l, &r, &x);
			update(l, r, x);
		}
		else {
			int l, r;
			scanf("%d %d", &l, &r);
			int matres[2][2] = {{0, 0}, {0, 0}};
			query(l, r, matres);
			printf("%d\n", matres[0][0]);
		}
	}

	return 0;
}