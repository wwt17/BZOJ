#include <cstdio>
#include <cstdlib>
#define sizeN 9
#define sizeK 82
#define size 512
unsigned N,K,bound,n,i,j,k;
bool legal[size],Legal[size][size];
int sum1[size];
long long f[sizeN][size][sizeK],ans;
int main() {
	scanf("%d%d",&N,&K);
	bound=1<<N;
	for (i=0;i<bound;++i)
		legal[i]=!(i&i>>1),sum1[i]=sum1[i>>1]+(i&1);
	for (i=0;i<bound;++i) if (legal[i])
		for (j=0;j<bound;++j) if (legal[j])
			Legal[i][j]=!(i<<1&j)&&!(i&j)&&!(i>>1&j);
	for (i=0;i<bound;++i) if (legal[i]) f[0][i][sum1[i]]=1;
	for (n=1;n<N;++n)
		for (i=0;i<bound;++i) if (legal[i])
			for (k=sum1[i];k<=K;++k)
				for (j=0;j<bound;++j) if (legal[j])
					if (Legal[i][j]) f[n][i][k]+=f[n-1][j][k-sum1[i]];
	ans=0;
	for (i=0;i<bound;++i) ans+=f[N-1][i][K];
	printf("%I64d\n",ans);
	system("pause");
}
