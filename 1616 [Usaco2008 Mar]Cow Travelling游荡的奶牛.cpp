#include <cstdio>
#include <cstdlib>
#define size 102
const int x[4]={-1,1,0,0},
					y[4]={0,0,-1,1};
int N,M,i,j,d,T,R,C;
long long f[2][size][size];
bool map[size][size],a;
char c;
int main() {
	scanf("%d%d%d\n",&N,&M,&T);
	for (i=1;i<=N;++i) {
		for (j=1;j<=M;++j) {
			scanf("%c",&c);
			map[i][j]=c=='.';
		}
		scanf("\n");
	}
	scanf("%d%d",&R,&C);
	a=0;
	f[a][R][C]=1;
	while (T--) {
		a^=1;
		for (i=1;i<=N;++i)
			for (j=1;j<=M;++j)
				if (map[i][j]) {
					f[a][i][j]=0;
					for (d=0;d<4;++d)
						f[a][i][j]+=f[!a][i+x[d]][j+y[d]];
				}
	}
	scanf("%d%d",&R,&C);
	printf("%lld\n",f[a][R][C]);
	system("pause");
}
