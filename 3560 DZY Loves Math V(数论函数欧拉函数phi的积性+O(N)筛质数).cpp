#include <cstdio>
const int mo=(int)1e9+7;
const int N=(int)1e5+5,M=(int)1e7+5;
typedef long long ll;

int n,m,a[N],prime[M/2],p[M],f[M];

ll power(ll a,ll b){
	ll ans=1;
	for(;b;b>>=1,a=a*a%mo)
		if(b&1) ans=ans*a%mo;
	return ans;
}

void init(){
	for(int i=2;i<=m;i++){
		if(!p[i]) p[i]=prime[++*prime]=i,f[i]=1;
		for(int j=1;j<=*prime&&i*prime[j]<=m&&prime[j]<=p[i];j++)
			p[i*prime[j]]=prime[j];
	}
}

int main(){
	scanf("%d",&n);
	for(int i=0;i<n;i++){
		scanf("%d",&a[i]);
		if(a[i]>m) m=a[i];
	}
	init();
	for(int i=0;i<n;i++){
		while(a[i]>1){
			int x=a[i],t=p[x];
			while(x%t==0) x/=t;
			f[t]=f[t]*(a[i]/x*(ll)t%mo-1)%mo*power(t-1,mo-2)%mo;
			a[i]=x;
		}
	}
	ll ans=1;
	for(int j=1;j<=*prime;j++){
		int t=prime[j];
		ans=ans*(power(t,mo-2)*(t-1)%mo*(f[t]-1)%mo+1)%mo;
	}
	printf("%d\n",int((ans+mo)%mo));
}
