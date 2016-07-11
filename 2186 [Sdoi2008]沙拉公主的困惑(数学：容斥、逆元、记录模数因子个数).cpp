#include <cstdio>
typedef long long ll;
const int N=10000005,T=10000;
int t,mo,n,q[T][2],prime[N/2],p[N],f[N],b[N],c[N];
ll power(ll a,ll b){
	ll ans=1;
	for(;b;b>>=1,a=a*a%mo)
		if(b&1) ans=ans*a%mo;
	return ans;
}
void init(){
	for(int i=2;i<=n;i++){
		if(!p[i]) p[i]=prime[++*prime]=i;
		for(int j=1;j<=*prime&&prime[j]<=p[i]&&i*prime[j]<=n;j++)
			p[i*prime[j]]=prime[j];
	}
	f[0]=1;
	for(int i=1;i<=n;i++) f[i]=f[i-1]*ll(p[i]==i?i-1:i)%mo;
	for(int i=1;i<=n;i++)
		if(i%mo) b[i]=i,c[i]=0; else b[i]=b[i/mo],c[i]=c[i/mo]+1;
	b[0]=1;
	c[0]=0;
	for(int i=1;i<=n;i++) b[i]=(ll)b[i]*b[i-1]%mo,c[i]+=c[i-1];
}
int main(){
	scanf("%d%d",&t,&mo);
	for(int i=0;i<t;i++){
		scanf("%d%d",&q[i][0],&q[i][1]);
		if(q[i][0]>n) n=q[i][0];
	}
	init();
	for(int i=0;i<t;i++)
		printf("%d\n",c[q[i][0]]-c[q[i][1]]?0:int(f[q[i][1]]*power(b[q[i][1]],mo-2)%mo*b[q[i][0]]%mo));
}
