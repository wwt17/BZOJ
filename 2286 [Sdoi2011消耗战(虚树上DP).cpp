#include <cstdio>
#include <algorithm>
using namespace std;
typedef long long ll;

const int N=250005,logN=18,inf=100005;
const ll linf=1e18;
int n,logn,m;
struct node;
struct edge{
	node *ed;
	edge *next;
	int w;
} E[N<<1],*newE=E;
struct node{
	edge *son;
	node *pa[logN];
	int mi[logN];
	int depth,dfn;
	node *head,*next;
	bool flag;
	void dfs(){
		static int len=0;
		dfn=++len;
		for(int j=1;j<logn;j++){
			pa[j]=pa[j-1]->pa[j-1];
			mi[j]=min(mi[j-1],pa[j-1]->mi[j-1]);
		}
		for(edge *e=son;e;e=e->next) if(e->ed!=pa[0]){
			e->ed->pa[0]=this;
			e->ed->mi[0]=e->w;
			e->ed->depth=depth+1;
			e->ed->dfs();
		}
	}
	int query(node *fa){
		node *u=this;
		int ans=inf;
		for(int j=logn-1;j>=0;j--) if(u->pa[j]->depth<=fa->depth)
			ans=min(ans,u->mi[j]),u=u->pa[j];
		return ans;
	}
	ll dp(){
		if(flag) return linf;
		ll ans=0;
		for(node *v=head;v;v=v->next)
			ans+=min((ll)v->query(this),v->dp());
		return ans;
	}
} V[N],*seq[N*2];

node *lca(node *u,node *v){
	if(u->depth>v->depth){
		for(int j=logn-1;j>=0;j--) if(u->pa[j]->depth>=v->depth) u=u->pa[j];
	}
	else{
		for(int j=logn-1;j>=0;j--) if(v->pa[j]->depth>=u->depth) v=v->pa[j];
	}
	if(u==v) return u;
	for(int j=logn-1;j>=0;j--) if(u->pa[j]!=v->pa[j]) u=u->pa[j],v=v->pa[j];
	return u->pa[0];
}

bool cmpdfn(node *u,node *v){
	return u->dfn<v->dfn;
}

int main(){
	scanf("%d",&n);
	for(logn=0;(1<<logn)<=n;logn++);
	for(int i=1;i<n;i++){
		int u,v,w; scanf("%d%d%d",&u,&v,&w);
		*newE=(edge){V+v,V[u].son,w},V[u].son=newE++;
		*newE=(edge){V+u,V[v].son,w},V[v].son=newE++;
	}
	V[1].pa[0]=V;
	V[1].mi[0]=inf;
	for(int j=0;j<logn;j++) V->pa[j]=V,V->mi[j]=inf;
	V[1].depth=1;
	V[1].dfs();
	int q; scanf("%d",&q);
	while(q--){
		scanf("%d",&m);
		seq[0]=V+1;
		for(int i=1;i<=m;i++){
			int x; scanf("%d",&x);
			seq[i]=V+x;
			seq[i]->flag=true;
		}
		m++;
		sort(seq,seq+m,cmpdfn);
		int mm=m;
		for(int i=0;i+1<m;i++)
			seq[mm++]=lca(seq[i],seq[i+1]);
		m=mm;
		sort(seq,seq+m,cmpdfn);
		m=unique(seq,seq+m)-seq;
		for(int i=1;i<m;i++){
			node *fa=lca(seq[i-1],seq[i]);
			seq[i]->next=fa->head;
			fa->head=seq[i];
		}
		printf("%lld\n",V[1].dp());
		for(int i=0;i<m;i++) seq[i]->head=NULL,seq[i]->flag=false;
	}
}
