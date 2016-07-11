//Ans=M^N-(M-1)^(N-1)*M
#include <cstdio>
#include <cstdlib>
#define P 100003
long long Power(int x,long long y) {
	long long Ret=1,sum=x;
	while (y) {
		if (y&1) Ret=Ret*sum%P;
		y>>=1;
		sum=sum*sum%P;
	}
	return Ret;
}
int main() {
	int M;
	long long N;
	scanf("%d%lld",&M,&N);
	printf("%d\n",(Power(M,N)-Power(M-1,N-1)*M%P+P)%P);
	system("pause");
}
