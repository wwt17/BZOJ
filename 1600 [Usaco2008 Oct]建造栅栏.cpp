#include <cstdio>
#include <cstring>
int main() {
	int N,i,j,k,bound,f[2501];
	scanf("%d",&N);
	memset(f,0,(1+N)*sizeof(f[0]));
	bound=(N+1)/2-1;
	f[0]=1;
	for (k=1;k<=4;++k)
		for (i=N;i>=0;--i) {
			f[i]=0;
			for (j=1;j<=bound;++j)
				if (i>=j) f[i]+=f[i-j]; else break;
		}
	printf("%d\n",f[N]);
}
