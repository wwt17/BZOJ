#include <cstdio>
#include <algorithm>
using namespace std;
typedef long long ll;
typedef pair<int,int> pii;
const int N=500005,K=6;
int n,k,C[K+1][K+1];
ll f[K+1];
int a[N][K],st[K+1][(1<<K)+1];
pii val[N];

ll work(int s){
	ll ans=0;
	for(int i=0;i<n;i++){
		val[i]=pii(0,0);
		for(int j=0;j<K;j++) if(s>>j&1)
			val[i].first=(ll(val[i].first)*2333+a[i][j])%1000000007,
			val[i].second=(ll(val[i].second)*234567+a[i][j])%999999991;
	}
	sort(val,val+n);
	for(int l=0,r=l;l<n;l=r){
		for(;r<n&&val[l]==val[r];r++);
		ans+=ll(r-l)*(r-l);
	}
	return ans;
}

int main(){
	scanf("%d%d",&n,&k);
	for(int i=0;i<n;i++)
		for(int j=0;j<K;j++)
			scanf("%d",&a[i][j]);
	for(int s=0;s<1<<K;s++){
		int cnt=0;
		for(int j=0;j<K;j++) cnt+=s>>j&1;
		st[cnt][++*st[cnt]]=s;
	}
	for(int i=0;i<=K;i++)
		for(int j=0;j<=i;j++)
			C[i][j]=j?C[i-1][j]+C[i-1][j-1]:1;
	for(int i=K;i>=k;i--){
		f[i]=0;
		for(int j=1;j<=*st[i];j++)
			f[i]+=work(st[i][j]);
		for(int j=i+1;j<=K;j++)
			f[i]-=C[j][i]*f[j];
	}
	printf("%lld\n",(f[k]-(k==6?n:0))/2);
}
