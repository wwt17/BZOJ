#include <cstdio>
#include <cstdlib>
const int N=100001,M=200001;
int n,m;
struct node;
struct edge{
	node *ed; edge *next;
} E[M<<1],*newE=E+2;
unsigned w[M];
struct node{
	edge *son; bool vis;
	void DFS(edge *pre){
		vis=true;
		for(edge *e=son;e;e=e->next) if(!e->ed->vis)
			e->ed->DFS(e);
		unsigned t=0;
		for(edge *e=son;e;e=e->next) t^=w[(e-E)>>1];
		w[(pre-E)>>1]^=t;
	}
} V[N];
int main(){
	scanf("%d%d",&n,&m);
	for(int i=1;i<=m;i++){
		int a,b; w[i]=rand()<<16|rand(); scanf("%d%d",&a,&b);
		*newE=(edge){V+b,V[a].son},V[a].son=newE++;
		*newE=(edge){V+a,V[b].son},V[b].son=newE++;
	}
	for(int i=1;i<=n;i++) if(!V[i].vis) V[i].DFS(E);
	int k,c,num[4]; scanf("%d",&k);
	while(k--){
		scanf("%d",&c);
		for(int i=0;i<c;i++) scanf("%d",num+i);
		for(int j=1;j<1<<c;j++){
			unsigned t=0;
			for(int i=0;i<c;i++) if(j&1<<i) t^=w[num[i]];
			if(!t){ puts("Disconnected"); goto end; }
		}
		puts("Connected");
		end:;
	}
}
