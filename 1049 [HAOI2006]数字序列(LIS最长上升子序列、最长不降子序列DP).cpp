#include <cstdio>
#include <algorithm>
using namespace std;
typedef long long ll;
const int N=35005,inf=(int)1e9;
const ll linf=(ll)1e18;
int n,m,a[N],cnt[N],head[N],last[N];
ll f[N];
bool cmp(int i,int j){
	return a[i]<a[j];
}
int main(){
	scanf("%d",&n);
	n+=2;
	for(int i=2;i<n;i++){
		scanf("%d",&a[i]);
		a[i]-=i;
	}
	a[1]=-inf;
	a[n]=inf;
	m=1;
	head[0]=1;
	for(int i=2;i<=n;i++){
		int t=upper_bound(head,head+m,i,cmp)-head;
		if(t==m) m++;
		last[i]=head[t];
		head[t]=i;
		f[i]=linf;
		ll sum0=0,sum1=0;
		for(int j=head[t-1],k=i-1,now=0,best=0;j&&a[j]<=a[i];j=last[j]){
			for(;k>j;k--){
				if(a[k]>=a[i]){
					sum1+=a[k];
					now--;
				}
				else{
					sum0+=a[k];
					now++;
				}
				best=min(best,now);
			}
			f[i]=min(f[i],f[j]+sum1-sum0+now*ll(a[j])+best*ll(a[i]-a[j]));
		}
	}
	ll ans=linf;
	for(int j=head[m-1];j;j=last[j]) ans=min(ans,f[j]);
	printf("%d\n%lld\n",n-1-(m-1),ans);
}
