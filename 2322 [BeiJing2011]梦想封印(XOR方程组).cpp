#include <cstdio>
#include <set>
using namespace std;
const int N=5005,M=20000,Q=20005,B=62;
typedef long long ll;

int cnt;
ll base[B];
set<ll> s,s2;
int n,m,q,dis[Q];
ll ans[Q];

bool add(ll x){
	for(int i=B-1;i>=0;i--) if(x>>i&1)
		if(base[i]) x^=base[i];
		else{
			for(int j=i-1;j>=0;j--) if(x>>j&1) x^=base[j];
			base[i]=x;
			for(int j=B-1;j>i;j--) if(base[j]>>i&1) base[j]^=x;
			cnt++;
			s2.clear();
			for(set<ll>::iterator it=s.begin();it!=s.end();it++){
				ll y=*it;
				if(y>>i&1) y^=x;
				s2.insert(y);
			}
			s.swap(s2);
			return true;
		}
	return false;
}

struct node;
struct edge{
	node *ed;
	edge *next;
	ll w;
	bool exist;
} E[M<<1],*newE=E;
struct node{
	edge *son;
	ll w;
	bool vis;
	void dfs(){
		vis=true;
		ll x=w;
		for(int i=B-1;i>=0;i--) if(x>>i&1)
			if(base[i]) x^=base[i];
		s.insert(x);
		for(edge *e=son;e;e=e->next) if(e->exist)
			if(e->ed->vis)
				add(w^e->w^e->ed->w);
			else{
				e->ed->w=w^e->w;
				e->ed->dfs();
			}
	}
} V[N];

int main(){
	scanf("%d%d%d",&n,&m,&q);
	for(int i=0;i<m;i++){
		static int a,b; static ll w;
		scanf("%d%d%I64d",&a,&b,&w);
		*newE=(edge){V+b,V[a].son,w,true},V[a].son=newE++;
		*newE=(edge){V+a,V[b].son,w,true},V[b].son=newE++;
	}
	for(int i=0;i<q;i++){
		scanf("%d",&dis[i]);
		dis[i]--;
		E[dis[i]<<1  ].exist=false;
		E[dis[i]<<1|1].exist=false;
	}
	V[1].dfs();
	ans[q]=(ll)s.size()<<cnt;
	for(int i=q-1;i>=0;i--){
		edge *e=E+(dis[i]<<1);
		e[0].exist=true;
		e[1].exist=true;
		if(e[1].ed->vis&&e[0].ed->vis)
			add(e[1].ed->w^e->w^e[0].ed->w);
		if(e[1].ed->vis&&!e[0].ed->vis){
			e[0].ed->w=e[1].ed->w^e[0].w;
			e[0].ed->dfs();
		}
		if(e[0].ed->vis&&!e[1].ed->vis){
			e[1].ed->w=e[0].ed->w^e[1].w;
			e[1].ed->dfs();
		}
		ans[i]=(ll)s.size()<<cnt;
	}
	for(int i=0;i<=q;i++) printf("%I64d\n",ans[i]-1);
	scanf("\n");
}
