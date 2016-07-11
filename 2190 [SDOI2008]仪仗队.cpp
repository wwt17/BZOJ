#include <cstdio>
#include <cstdlib>
#define size 40000
int N,i,j,k,prime[size],cnt,p[size],phi[size],ans;
int main() {
	scanf("%d",&N);
	if (N<=1) { printf("0\n"); return 0; }
	p[1]=phi[1]=1;
	for (i=1;i<N;++i) {
		if (!p[i]) {
			prime[cnt++]=p[i]=i;
			phi[i]=i-1;
		}
		for (j=0;j<cnt&&(k=prime[j]*i)<=N;++j) {
			p[k]=prime[j];
			if (prime[j]==p[i]) { phi[k]=prime[j]*phi[i]; break; }
			phi[k]=(prime[j]-1)*phi[i];
		}
		ans+=phi[i];
	}
	printf("%d\n",(ans<<1)+1);
	system("pause");
}
