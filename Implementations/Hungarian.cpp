#include <bits/stdc++.h>

using namespace std;

struct Hungarian { // Returns minimum possible sum of assignment values
	int n,i,j,k,l,m,p,q,V[109][109],R[109],C[109],M[109],P[109],N[109],U[109];
	Hungarian(int n) : n(n) {
		for(i=109; i--;) R[i]=C[i]=M[i]=P[i]=N[i]=U[i]=0;
	}
	int solve() {
		for(i=1; i<=n; ++i) {
			for(j=1; j<=n; ++j) U[j]=N[j]=1000000009;
			for(M[p=q=0]=i,U[0]=N[0]=1000000009; M[p]; p=q) {
				for(l=1000000009,k=M[p],U[p]=0,j=1; j<=n; ++j) if(U[j]) {
					m=V[k][j]-R[k]-C[j];
					if(m<N[j]) N[j]=m,P[j]=p;
					if(l>N[j]) l=N[j],q=j;
				}
				for(j=0; j<=n; ++j) {
					if(U[j]) N[j]-=l;
					else R[M[j]]+=l,C[j]-=l;
				}
			}
			while(p) q=P[p],M[p]=M[q],p=q;
		}
		return -C[0];
	}
};

int main() {
	int t;
	scanf("%d", &t);

	for(int tc = 1; tc <= t; tc++) {
		int n;
		scanf("%d", &n);

		Hungarian h = Hungarian(n);

		for (int i = 1; i <= n; i++) {
			for (int j = 1; j <= n; j++) {
				scanf("%d", &h.V[i][j]);
			}
		}

		printf("Case %d: %d\n", tc, h.solve());
	}

	return 0;
}