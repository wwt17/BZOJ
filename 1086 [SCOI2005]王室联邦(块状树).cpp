#include <cstdio>

const int N=1005;

int n,B;

struct node;
struct edge{
	node *ed;
	edge *next;
} E[N<<1],*newE=E;
int tot;
struct node{
	edge *son;
	int belong;
} V[N],*root[N],*stack[N];
int top;

void dfs(node *u,node *from=NULL){
	int bot=top;
	for(edge *e=u->son;e;e=e->next){
		node *v=e->ed;
		if(v==from) continue;
		dfs(v,u);
		if(top-bot>=B){
			root[++tot]=u;
			while(top>bot) stack[top--]->belong=tot;
		}
	}
	stack[++top]=u;
}

int main(){
	scanf("%d%d",&n,&B);
	if(n<B) return puts("0"),0;
	for(int i=1;i<n;i++){
		int x,y; scanf("%d%d",&x,&y);
		*newE=(edge){V+y,V[x].son},V[x].son=newE++;
		*newE=(edge){V+x,V[y].son},V[y].son=newE++;
	}
	dfs(V+1);
	if(!tot) root[++tot]=V+1;
	while(top>0) stack[top--]->belong=tot;
	printf("%d\n",tot);
	for(int i=1;i<=n;i++) printf("%d%c",V[i].belong," \n"[i==n]);
	for(int i=1;i<=tot;i++) printf("%d%c",root[i]-V," \n"[i==tot]);
}
