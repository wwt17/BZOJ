// Ans=C(n+m,m)-C(n+m,m-1)
#include <cstdio>
const int P=20100403;
int n,m;
int main(){
	scanf("%d%d",&n,&m);
	long long a=1;
	for(int i=1;i<=m;i++) (a*=i)%=P;
	long long ans=1;
	for(int s=P-2;s;s>>=1,a=a*a%P)
		if(s&1) (ans*=a)%=P;
	for(int i=n+2;i<=n+m;i++) (ans*=i)%=P;
	printf("%d\n",ans*(n-m+1)%P);
}
