/*
http://taorunz.logdown.com/posts/193397-bzoj3157
Si=sigma(1<=k<=n){ k^i * m^k }
 (m-1)Si
=m*Si-Si
=sigma(1<=k<=n){ k^i * m^(k+1) } -sigma(1<=k<=n){ k^i * m^k }
=sigma(1<=k<=n+1){ (k-1)^i * m^k } -sigma(1<=k<=n){ k^i * m^k }
=n^i*m^(n+1) +sigma(1<=k<=n){ m^k *( (k-1)^i-k^i ) }
=n^i*m^(n+1) +sigma(1<=k<=n){ m^k * sigma(0<=j<i){ C(i,j)*(-1)^(i-j)*k^j } }
=n^i*m^(n+1) +sigma(0<=j<i){ C(i,j)*(-1)^(i-j) *sigma(1<=k<=n){ k^j*m^k } }
=n^i*m^(n+1) +sigma(0<=j<i){ C(i,j)*(-1)^(i-j) *Sj }
O(m^2)
*/
#include <cstdio>

typedef long long ll;

const int M=1005,p=int(1e9+7);

int n,m,x;

ll C[M][M],S[M];

inline ll power(ll a,ll b){
	ll ans=1;
	for(;b;b>>=1,a=a*a%p)
		if(b&1) ans=ans*a%p;
	return ans;
}

int main(){
	scanf("%d%d",&n,&m);
	if(m==1){
		printf("%d\n",int(ll(n+1)*n/2%p));
		return 0;
	}
	x=power(m-1,p-2);
	S[0]=(power(m,n)-1)*x%p*m%p;
	C[0][0]=1;
	for(int i=1;i<=m;i++){
		S[i]=power(n,i)*power(m,n+1)%p;
		C[i][0]=1;
		for(int j=1;j<=i;j++) C[i][j]=(C[i-1][j]+C[i-1][j-1])%p;
		ll y=-1;
		for(int j=i-1;j>=0;j--){
			S[i]=(S[i]+C[i][j]*y*S[j])%p;
			y*=-1;
		}
		S[i]=S[i]*x%p;
	}
	printf("%d\n",int((S[m]+p)%p));
}
