#include <cstdio>
#include <cstdlib>
#define P 100000000
#define size 4096
int main() {
	int M,N;
	scanf("%d%d\n",&M,&N);
	int bound=1<<N,i,j,f[2][bound],legal[bound],pool,R;
	bool t=0,g[2][bound];
	for (i=0;i<bound;++i)
		legal[i]=!(i&(i>>1));
	f[t][0]=1; g[t][0]=1;
	for (i=1;i<bound;++i) f[t][i]=0,g[t][i]=0;
	while (M--) {
		t^=1;
		pool=0;
		for (j=N;j;--j) {
			scanf("%d",&R);
			pool=(pool<<1)+!R;
		}
		for (i=0;i<bound;++i) if (g[t][i]=legal[i]&&!(i&pool)) {
			f[t][i]=0;
			for (j=0;j<bound;++j) if (g[!t][j]&&!(i&j))
				f[t][i]=(f[t][i]+f[!t][j])%P;
		}
	}
	int ans=0;
	for (i=0;i<bound;++i) if (legal[i]&&!(i&pool))
		ans=(ans+f[t][i])%P;
	printf("%d\n",ans);
	system("pause");
}
