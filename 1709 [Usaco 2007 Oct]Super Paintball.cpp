#include <cstdio>
#include <cstdlib>
#define size 102
int N,K,i,j,k,s[size][size],f[size][size],g[size][size];
int main() {
	scanf("%d%d\n",&N,&K);
	for (k=K;k;--k) {
		scanf("%d%d",&i,&j);
		++s[i][j];
	}
	for (i=1;i<=N;++i) {
		for (j=1;j<=N;++j)
			f[i][j]=f[i][j-1]+s[i][j];
		for (j=1;j<=N;++j)
			g[i][j]+=f[i][N];
	}
	for (j=1;j<=N;++j) {
		for (i=1;i<=N;++i)
			f[i][j]=f[i-1][j]+s[i][j];
		for (i=1;i<=N;++i)
			g[i][j]+=f[N][j];
	}
	for (i=1;i<=N;++i) {
		for (j=1;j<=N;++j)
			f[i][j]=f[i-1][j+1]+s[i][j];
		for (j=1;j<=i;++j)
			g[i-j+1][j]+=f[i][1];
	}
	for (j=2;j<=N;++j)
		for (i=j;i<=N;++i)
			g[i][N-i+j]+=f[N][j];
	for (i=1;i<=N;++i) {
		for (j=1;j<=N;++j)
			f[i][j]=f[i-1][j-1]+s[i][j];
		for (j=N-i+1;j<=N;++j)
			g[i+j-N][j]+=f[i][N];
	}
	for (j=1;j<N;++j)
		for (i=N-j+1;i<=N;++i)
			g[i][i-N+j]+=f[N][j];
	int ans=0;
	for (i=1;i<=N;++i)
		for (j=1;j<=N;++j)
			if (g[i][j]-s[i][j]*3==K) ++ans;
	printf("%d\n",ans);
	system("pause");
}
