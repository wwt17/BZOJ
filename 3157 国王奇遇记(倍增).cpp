/*
 sigma(a<=i<b){ i^m * M^i }
=sigma(0<=i<b-a){ (i+a)^m * M^(i+a) }
=sigma(0<=j<=m) C(m,j)*a^(m-j)* M^a* sigma(0<=i<b-a) i^j*M^i
O(M^2logN+MlogN)
*/
#include <cstdio>

typedef long long ll;

const int logN=30,M=205,p=int(1e9+7);

int n,m;

ll C[M][M],f[logN][M];

int main(){
	scanf("%d%d",&n,&m);
	n++;
	for(int i=0;i<=m;i++){
		C[i][0]=1;
		for(int j=1;j<=i;j++)
			C[i][j]=(C[i-1][j-1]+C[i-1][j])%p;
	}
	f[0][0]=1;
	int a=1;
	ll c=m;
	for(int k=1;n>>k;k++){
		for(int i=0;i<=m;i++){
			f[k][i]=f[k-1][i];
			ll x=1;
			for(int j=i;j>=0;j--){
				f[k][i]=(f[k][i]+C[i][j]*x%p*c%p*f[k-1][j])%p;
				x=x*a%p;
			}
		}
		a<<=1;
		c=c*c%p;
	}
	ll ans=0;
	for(int k=0;n>>k;k++) if(n>>k&1){
		int a=n>>k+1<<k+1;
		ll x=1,now=0;
		for(int j=m;j>=0;j--){
			now=(now+C[m][j]*x%p*f[k][j])%p;
			x=x*a%p;
		}
		for(ll x=m;a;a>>=1,x=x*x%p)
			if(a&1) now=now*x%p;
		ans=(ans+now)%p;
	}
	printf("%d\n",int(ans));
}
