#include <cstdio>
#include <algorithm>
using namespace std;
typedef long long ll;

const int N=50000;

int n,m,mu[1+N],smu[1+N],sum[N+1];

void init(){
	mu[1]=1;
	for(int i=1;i<=N;i++)
		for(int j=i*2;j<=N;j+=i)
			mu[j]-=mu[i];
	for(int i=1;i<=N;i++) smu[i]=smu[i-1]+mu[i];
	for(int i=1;i<=N;i++){
		for(int l=0,r;l<i;l=r){
			r=i/(i/(l+1));
			sum[i]+=(r-l)*(i/r);
		}
	}
}

int main(){
	init();
	int T; scanf("%d",&T);
	while(T--){
		scanf("%d%d",&n,&m);
		ll ans=0;
		for(int l=0,r;l<n&&l<m;l=r){
			r=min(n/(n/(l+1)),m/(m/(l+1)));
			ans+=ll(smu[r]-smu[l])*sum[n/r]*sum[m/r];
		}
		printf("%lld\n",ans);
	}
}
