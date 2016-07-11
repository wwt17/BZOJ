#include <cstdio>
typedef long long ll;
const int K=60,N=1005;
int k,n;
ll l,r,a[N];
int num,belong[K],b[K];
ll work(ll x){
	ll ans=0,t=num;
	if(x>>k) return 1LL<<t;
	for(int i=0;i<k;i++) b[i]=-1;
	for(int i=k-1;i>=0;i--)
		if(x>>i&1){
			if(b[belong[i]]==-1){
				t--;
				ans+=1LL<<t;
				b[belong[i]]=1;
			}
			else
			if(b[belong[i]]==0){
				ans+=1LL<<t;
				break;
			}
		}
		else{
			if(b[belong[i]]==-1){
				t--;
				b[belong[i]]=0;
			}
			else
			if(b[belong[i]]==1)
				break;
		}
	return ans;
}
int main(){
	scanf("%d%d%lld%lld",&n,&k,&l,&r);
	for(int j=0;j<k;j++) b[j]=-2;
	for(int i=1;i<=n;i++) scanf("%lld",a+i);
	for(int i=0;i<k;i++){
		int j;
		for(j=0;j<i;j++){
			bool ok=true;
			for(int t=1;t<=n;t++) if((a[t]>>i&1)!=(a[t]>>j&1)){
				ok=false;
				break;
			}
			if(ok) break;
		}
		belong[i]=j;
		if(i==j) num++;
	}
	printf("%lld\n",work(r+1)-work(l));
}
