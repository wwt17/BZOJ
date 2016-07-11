#include <cstdio>
#include <algorithm>
using namespace std;

const int N=300005,logN=19;
int n;
struct node;
struct edge{
	node *ed;
	edge *next;
} E[N<<1],*newE=E;
struct node{
	node *pa[logN];
	edge *son;
	int size,dfn,depth;
	node *fa;
	node *Son,*Next;
	node *best;
	int dist;
	int ans;
	node *anc(int x){
		node *v=this;
		for(int j=0;x>>j;j++)
			if(x>>j&1)
				v=v->pa[j];
		return v;
	}
	void dfs(){
		static int len=0;
		dfn=++len;
		size=1;
		for(int j=1;j<logN;j++) pa[j]=pa[j-1]->pa[j-1];
		for(edge *e=son;e;e=e->next){
			node *v=e->ed;
			if(v==*pa) continue;
			*v->pa=this;
			v->depth=depth+1;
			v->dfs();
			size+=v->size;
		}
	}
	void Dfs1(){
		for(node *v=Son;v;v=v->Next){
			v->Dfs1();
			int d=v->dist+(v->depth-depth);
			if(d<dist||d==dist&&v->best<best){
				best=v->best;
				dist=d;
			}
		}
	}
	void Dfs2(){
		for(node *v=Son;v;v=v->Next){
			int d=dist+(v->depth-depth);
			if(d<v->dist||d==v->dist&&best<v->best){
				v->best=best;
				v->dist=d;
			}
			v->Dfs2();
		}
	}
	void Dfs(int);
} V[N];
void node::Dfs(int tmp){
	best->ans+=tmp;
	for(node *v=Son;v;v=v->Next){
		int len=v->depth-depth;
		int d=dist-v->dist+len;
		if(d&1) d/=2;
		else
			if(best<v->best)
				d=d/2-1;
			else
				d=d/2;
		if(d==len) d--;
		node *x=v->anc(d);
		best->ans-=x->size;
		v->Dfs(x->size);
	}
}
node *lca(node *u,node *v){
	if(u->depth>v->depth)
		u=u->anc(u->depth-v->depth);
	else
		v=v->anc(v->depth-u->depth);
	if(u==v) return u;
	for(int j=logN-1;j>=0;j--)
		if(u->pa[j]!=v->pa[j])
			u=u->pa[j],v=v->pa[j];
	return u->pa[0];
}
int m;
node *tmp[N],**top,*seq[N*2];
bool cmpdfn(node *u,node *v){
	return u->dfn<v->dfn;
}

int main(){
	scanf("%d",&n);
	for(int i=1;i<n;i++){
		int x,y;
		scanf("%d%d",&x,&y);
		*newE=(edge){V+y,V[x].son},V[x].son=newE++;
		*newE=(edge){V+x,V[y].son},V[y].son=newE++;
	}
	for(int j=0;j<logN;j++) V->pa[j]=V;
	V[1].pa[0]=V;
	V[1].dfs();
	int q; scanf("%d",&q);
	while(q--){
		scanf("%d",&m);
		int k=m;
		for(int i=0;i<m;i++){
			int x; scanf("%d",&x);
			seq[i]=V+x;
			tmp[i]=seq[i];
		}
		sort(seq,seq+m,cmpdfn);
		for(int i=0;i<m-1;i++)
			seq[m+i]=lca(seq[i],seq[i+1]);
		m=m*2-1;
		sort(seq,seq+m,cmpdfn);
		m=unique(seq,seq+m)-seq;
		for(int i=0;i<m;i++) seq[i]->Son=seq[i]->Next=NULL,seq[i]->best=NULL,seq[i]->dist=N;
		for(int i=0;i<k;i++) tmp[i]->best=tmp[i],tmp[i]->dist=0,tmp[i]->ans=0;
		seq[0]->fa=NULL;
		for(int i=1;i<m;i++){
			seq[i]->fa=lca(seq[i-1],seq[i]);
			seq[i]->Next=seq[i]->fa->Son;
			seq[i]->fa->Son=seq[i];
		}
		seq[0]->Dfs1();
		seq[0]->Dfs2();
		seq[0]->Dfs(n);
		for(int i=0;i<k;i++) printf("%d ",tmp[i]->ans);
		puts("");
	}
}
