#include <cstdio>
const int N=50005,M=100005;
const int W=63;
typedef long long type;
int n,m;
type Base[W];
void add(type x){
	for(int i=W-1;i>=0;i--) if(x>>i&1)
		if(Base[i]) x^=Base[i];
		else{
			Base[i]=x;
			return;
		}
}
struct node;
struct edge{
	node *ed;
	edge *next;
	type w;
} E[M<<1],*newE=E;
struct node{
	edge *son;
	type a; bool vis;
	void dfs(){
		vis=true;
		for(edge *e=son;e;e=e->next) if(!e->ed->vis){
			e->ed->a=a^e->w;
			e->ed->dfs();
		}
	}
} V[N];
int main(){
	scanf("%d%d",&n,&m);
	for(int i=0;i<m;i++){
		int u,v; type d; scanf("%d%d%lld",&u,&v,&d);
		*newE=(edge){V+v,V[u].son,d},V[u].son=newE++;
		*newE=(edge){V+u,V[v].son,d},V[v].son=newE++;
	}
	V[1].dfs();
	for(int i=0;i<m;i++)
		add(E[i<<1].w^E[i<<1].ed->a^E[i<<1|1].ed->a);
	for(int i=0;i<W;i++)
		for(int j=0;j<i;j++) if(Base[i]>>j&1)
			Base[i]^=Base[j];
	type ans=V[n].a;
	for(int i=W-1;i>=0;i--) if(!(ans>>i&1))
		ans^=Base[i];
	printf("%lld\n",ans);
}
