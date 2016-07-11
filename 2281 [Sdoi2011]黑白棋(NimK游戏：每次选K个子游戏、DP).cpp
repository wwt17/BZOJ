#include <cstdio>
const int N=10005,logN=14,mo=(int)1e9+7;
int n,m,d,f[logN][N],s[logN][N],fac[N],ifac[N];

long long C(int n,int m){
	return 1LL*fac[n]*ifac[n-m]%mo*ifac[m]%mo;
}

int main(){
	scanf("%d%d%d",&n,&m,&d);
	ifac[1]=1;
	for(int i=2;i<=n;i++) ifac[i]=1LL*(mo-mo/i)*ifac[mo%i]%mo;
	fac[0]=ifac[0]=1;
	for(int i=1;i<=n;i++) fac[i]=1LL*fac[i-1]*i%mo,ifac[i]=1LL*ifac[i-1]*ifac[i]%mo;
	n-=m; m/=2; d++;
	for(int k=0;k*d<=m&&k*d<=n;k++) f[0][k*d]=C(m,k*d);
	int i;
	for(i=1;n>>i;i++)
		for(int j=0;j<=n;j++)
			for(int k=0;k*d<=m&&j>=(k*d<<i);k++)
				f[i][j]=(f[i][j]+f[i-1][j-(k*d<<i)]*C(m,k*d))%mo;
	i--;
	int ans=0;
	for(int j=0;j<=n;j++)
		ans=(ans+f[i][j]*C(n-j+m,m))%mo;
	printf("%d\n",int((C(n+m*2,m*2)+mo-ans)%mo));
}
