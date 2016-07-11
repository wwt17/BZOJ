#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;

const int N=256,M=23;

typedef long long ll;

int n,p,q,g[N][N],belong[N],num[N],size[N],sum[N],cnt,m;
ll c[N];
typedef pair<int,ll> data;
data ans,f[1<<M];

void update(data &a,data &b){
	if(b.first>a.first)
		a=b;
	else
	if(b.first==a.first)
		a.second+=b.second;
}

int get(int u){
	if(!belong[u]) return u;
	return belong[u]=get(belong[u]);
}

void dfs(int i,ll s,ll t,int cnt){
	if(i==m){
		f[s]=data(cnt,1);
		return;
	}
	dfs(i+1,s,t,cnt);
	t|=c[i];
	if(!(t&1LL<<i))
		dfs(i+1,s|1LL<<i,t,cnt+sum[i]);
}
void dfs2(int i,ll s,ll t,int cnt){
	if(i==n){
		data now=f[(1LL<<m)-1&~t];
		now.first+=cnt;
		update(ans,now);
		return;
	}
	dfs2(i+1,s,t,cnt);
	t|=c[i];
	if(!(t&1LL<<i))
		dfs2(i+1,s|1LL<<i,t,cnt+sum[i]);
}

int main(){
	scanf("%d%d%d",&n,&p,&q);
	for(int i=1;i<=n;i++) size[i]=1;
	for(int i=0;i<p;i++){
		static int a,b; scanf("%d%d",&a,&b);
		int x=get(a),y=get(b);
		if(x!=y){
			belong[x]=y;
			size[y]+=size[x];
		}
	}
	for(int i=1;i<=n;i++) if(!belong[i]){
		num[i]=cnt;
		sum[cnt++]=size[i];
	}
	n=cnt;
	for(int i=0;i<q;i++){
		static int a,b; scanf("%d%d",&a,&b);
		int x=get(a),y=get(b);
		c[num[x]]|=1LL<<num[y];
		c[num[y]]|=1LL<<num[x];
	}
	ll best=1LL<<60;
	for(int i=1;i<=n;i++){
		ll now=((ll)i<<i)+(1LL<<n-i);
		if(now<best){
			best=now;
			m=i;
		}
	}
	for(ll s=0;s<1<<m;s++) f[s].first=-10000;
	dfs(0,0,0,0);
	for(int j=0;j<m;j++){
		for(int s=(1<<m)-1;s>=0;s--)
			if(s&1<<j)
				update(f[s],f[s-(1<<j)]);
	}
	dfs2(m,0,0,0);
	printf("%d %lld\n",ans.first,ans.second);
}
