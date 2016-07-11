#include <cstdio>
#include <algorithm>
int main() {
	int N;
	scanf("%d",&N);
	int i,j,c[N+2],t,sum=0;
	c[0]=0;
	for (i=1;i<=N;++i) {
		scanf("%d",&c[i]);
		c[i]+=c[i-1];
	}
	if (c[N]&1) {
		printf("0\n");
		system("pause");
		return 0;
	}
	for (i=1;i<=N;++i) {
		t=(c[i]+(c[N]>>1))%c[N];
		if (c[j=std::lower_bound(c,c+N+1,t)-c]==t)
			++sum;
	}
	printf("sum=%d\n",sum);
	sum>>=1;
	printf("%d\n",(sum*(sum-1))>>1);
	system("pause");
}
