//f[i,j]=f[i-1,j-1]+D[i]
//g[i,j]=max(f[i-1,j+1],g[i-1,j+1])
#include <cstdio>
#include <cstdlib>
#include <algorithm>
using namespace std;
#define inf 2147483647
int N,M,i,j,f[10001][501],g[10001][501],Di;
int main() {
	scanf("%d%d\n",&N,&M);
	for (j=1;j<=M;++j) f[0][j]=g[0][j]=-inf;
	for (i=1;i<=N;++i) {
		scanf("%d",&Di);
		for (j=1;j<=M;++j) f[i][j]=f[i-1][j-1]+Di;
		for (j=0;j<M;++j) g[i][j]=max(f[i-1][j+1],g[i-1][j+1]);
		f[i][0]=g[i][0]=max(g[i][0],g[i-1][0]);
		g[i][M]=-inf;
		//printf("f[%d]:",i); for (j=0;j<=M;++j) printf("%12d",f[i][j]); printf("\n");
		//printf("g[%d]:",i); for (j=0;j<=M;++j) printf("%12d",g[i][j]); printf("\n");
	}
	printf("%d\n",f[N][0]);
	//system("pause");
}
