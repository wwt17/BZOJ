#include <cstdio>
int main() {
	long long N;
	scanf("%lld",&N);
	int ans=0;
	while (N^1) { ++ans; N&1?N=N*3+1:N>>=1; }
	printf("%d\n",ans);
	scanf("%d");
}
