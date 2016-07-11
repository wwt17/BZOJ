#include <cstdio>
typedef long long ll;
const int N=1005;
int n,m,gcd[N][N];
ll ans;

int main(){
	scanf("%d%d",&n,&m);
	if(n<m){ int t=n; n=m; m=t; }
	for(int i=1;i<=n;i++)
		gcd[i][0]=i;
	for(int j=1;j<=n;j++)
		for(int i=0;i<=n;i++)
			gcd[i][j]=gcd[j][i%j];
	for(int i=1;i<=n;i++)
		for(int j=1;j<=m;j++)
			ans-=(gcd[i][j]-1LL)*(n-i+1)*(m-j+1);
	ans*=2;
	for(int i=1;i<=n;i++)
		ans-=(gcd[i][0]-1LL)*(n-i+1)*(m+1);
	for(int j=1;j<=m;j++)
		ans-=(gcd[0][j]-1LL)*(n+1)*(m-j+1);
	ll t=1LL*(n+1)*(m+1);
	ans+=t*(t-1)*(t-2)/6;
	printf("%lld\n",ans);
}
