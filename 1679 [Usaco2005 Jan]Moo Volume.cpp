#include <cstdio>
#include <algorithm>
int main() {
	int N,i;
	scanf("%d",&N);
	long long a[N+1],sum=0,ans=0;
	for (i=1;i<=N;++i) scanf("%I64d",&a[i]);
	std::sort(a+1,a+N+1);
	for (i=1;i<=N;++i) {
		sum+=a[i];
		ans+=a[i]*i-sum;
	}
	printf("%I64d\n",ans*2);
	system("pause");
}
