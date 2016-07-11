#include <cstdio>
#include <cstring>
#define P 1000000000
int main() {
	int N;
	scanf("%d",&N);
	int i,sum,f[N+1];
	memset(f,0,sizeof(f));
	f[0]=1;
	for (sum=1;sum<=N;sum<<=1)
		for (i=sum;i<=N;++i)
			f[i]=(f[i]+f[i-sum])%P;
	printf("%d\n",f[N]);
	scanf("%d");
}
