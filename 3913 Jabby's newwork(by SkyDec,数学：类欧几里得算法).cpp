#include <cstdio>
#include <cstring>
const int mo=(int)1e9+7,K=55,Lev=100;
typedef long long ll;

ll power(ll a,ll b){
	a%=mo;
	if((b%=mo-1)<0) b+=mo-1;
	ll ans=1;
	for(;b;b>>=1,a=a*a%mo)
		if(b&1) ans=ans*a%mo;
	return ans;
}

ll a[K][K],c[K][K];
ll f[Lev][K][K];
bool done[Lev][K][K];

void init(){
	for(int i=0;i<K;i++)
		for(int j=0;j<=i;j++)
			c[i][j]=j?(c[i-1][j]+c[i-1][j-1])%mo:1;
	static int b[K];
	b[0]=1;
	for(int i=1;i<K;i++){
		for(int j=0;j<i;j++)
			b[i]=(b[i]-1LL*c[i+1][j]*b[j]%mo+mo)%mo;
		b[i]=b[i]*power(i+1,-1)%mo;
	}
	int k=K-5;
	for(int i=0;i<=k;i++){
		ll inv=power(i+1,-1);
		for(int j=0;j<=i;j++)
			a[i][i+1-j]=inv*c[i+1][j]%mo*b[j]%mo;
		(++a[i][i])%=mo;
	}
}

ll calcf(int lev,ll A,ll B,ll C,ll N,int m,int k){
	if(N<0) return 0;
	ll &ans=f[lev][m][k];
	if(done[lev][m][k]) return ans;
	done[lev][m][k]=true;
	ans=0;
	if(A==0){
		ll w=1;
		for(int j=0;j<=k+1;j++,w=N%mo*w%mo) ans=(ans+a[k][j]*w)%mo;
		ans=ans*power(B/C,m)%mo;
		return ans;
	}
	if(A>=C){
		ll a=A/C,w=1;
		for(int i=0;i<=m;i++,w=w*a%mo)
			ans=(ans+c[m][i]*w%mo*calcf(lev+1,A-a*C,B,C,N,m-i,i+k))%mo;
		return ans;
	}
	if(B>=C){
		ll b=B/C,w=1;
		for(int i=0;i<=m;i++,w=w*b%mo)
			ans=(ans+c[m][i]*w%mo*calcf(lev+1,A,B-b*C,C,N,m-i,k))%mo;
		return ans;
	}
	ll M=(A*N+B)/C;
	ll w=1;
	for(int j=0;j<=k+1;j++,w=N%mo*w%mo) ans=(ans+a[k][j]*w)%mo;
	ans=ans*power(M,m)%mo;
	for(int i=1;i<=m;i++){
		for(int j=0;j<=k+1;j++)
			ans=(ans+mo-1LL*c[m][i]*a[k][j]%mo*calcf(lev+1,C,C-B-1,A,M-1,j,m-i)%mo)%mo;
	}
	return ans;
}

int main(){
	init();
	int k,l,r,a,b,c;
	scanf("%d%d%d%d%d%d",&k,&l,&r,&a,&b,&c);
	memset(done,0,sizeof(done));
	ll ans=calcf(0,a,b,c,r,k,0);
	memset(done,0,sizeof(done));
	ans=(ans+mo-calcf(0,a,b,c,l-1,k,0))%mo;
	printf("%d\n",int(ans));
}
