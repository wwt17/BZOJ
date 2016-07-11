#include <cstdio>
#include <algorithm>
#include <queue>
using namespace std;
typedef long long ll;
typedef pair<ll,ll> data;
typedef pair<int,int> pii;
#define fi first
#define se second
const int B=15,K=100005;
const ll mo=(int)1e9+7;
ll n;
int k,b,len[B],tot;
data val[B][K],num[K];

bool cmpse(const data &a,const data &b){
	return a.se>b.se;
}

struct cmp{
	bool operator () (const pii a,const pii b) const{
		return
			min(mo,num[a.fi].se)*min(mo,num[a.se].se)<
			min(mo,num[b.fi].se)*min(mo,num[b.se].se);
	}
};

priority_queue<pii,vector<pii>,cmp> q;

void getbase(){
	for(ll w=1;w<n;w*=10) b++;
}
ll calc(ll n){
	ll ans=1;
	for(;n;n/=10) ans*=n%10;
	return ans;
}
int main(){
	scanf("%lld%d",&n,&k); n++;
	getbase();
	len[0]=1;
	val[0][0]=data(1,1);
	for(int j=1;j<=b;j++){
		for(int i=0;i<len[j-1];i++)
			for(int c=0;c<10;c++)
				val[j][len[j]++]=data(val[j-1][i].fi*c,val[j-1][i].se);
		sort(val[j],val[j]+len[j]);
		int l=0;
		for(int i=0,ii=i;i<len[j];i=ii){
			data tmp(val[j][i].fi,0);
			for(;val[j][i].fi==val[j][ii].fi;ii++)
				tmp.se+=val[j][ii].se;
			val[j][l++]=tmp;
		}
		len[j]=l;
	}
	tot=len[b];
	for(int i=0;i<tot;i++) num[i]=data(val[b][i].fi,0);
	ll j=0,l=0,r=n;
	for(;r>=10;j++,l/=10,r/=10){
		for(ll c=l+1;c<10;c++){
			for(int i=0;i<len[j];i++)
				lower_bound(num,num+tot,data(c*val[j][i].fi,0))->se+=val[j][i].se;
		}
		ll v=calc(r/10);
		for(ll c=r%10-1;c>=0;c--){
			for(int i=0;i<len[j];i++)
				lower_bound(num,num+tot,data(v*c*val[j][i].fi,0))->se+=val[j][i].se;
		}
	}
	for(ll c=l+1;c<r;c++){
		for(int i=0;i<len[j];i++)
			lower_bound(num,num+tot,data(c*val[j][i].fi,0))->se+=val[j][i].se;
	}
	for(int i=0;i<tot;i++) if(num[i].fi<1||num[i].fi>=n) num[i].se=0;
	sort(num,num+tot,cmpse);
	for(int i=0;i<tot;i++) q.push(pii(i,0));
	int ans=0;
	while(k--&&!q.empty()){
		pii cur=q.top(); q.pop();
		ans=(ans+(num[cur.fi].se%mo)*(num[cur.se].se%mo))%mo;
		if(cur.se+1<tot)
			q.push(pii(cur.fi,cur.se+1));
	}
	printf("%d\n",ans);
}
