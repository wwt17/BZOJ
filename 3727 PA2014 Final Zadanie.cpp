#include <cstdio>

const int N=300005;
int n;
long long ans;
struct node;
struct edge{
	node *ed;
	edge *next;
} E[N<<1],*newE=E;
struct node{
	edge *son;
	long long s,a;
	int b;
	node *pa;
	void dfs(){
		for(edge *e=son;e;e=e->next) if(e->ed!=pa){
			e->ed->pa=this;
			e->ed->dfs();
			ans+=b-e->ed->b;
		}
	}
	void dfs2(){
		a=s;
		for(edge *e=son;e;e=e->next) if(e->ed!=pa){
			e->ed->s=(ans+b-e->ed->b)/2;
			e->ed->dfs2();
			a-=e->ed->s;
		}
	}
} V[N];

int main(){
	scanf("%d",&n);
	for(int i=1;i<n;i++){
		int x,y; scanf("%d%d",&x,&y);
		*newE=(edge){V+y,V[x].son},V[x].son=newE++;
		*newE=(edge){V+x,V[y].son},V[y].son=newE++;
	}
	for(int i=1;i<=n;i++) scanf("%d",&V[i].b);
	V[1].dfs();
	ans=(2*V[1].b-ans)/(n-1);
	V[1].s=ans;
	V[1].dfs2();
	for(int i=1;i<n;i++) printf("%lld ",V[i].a); printf("%lld\n",V[n].a);
}
