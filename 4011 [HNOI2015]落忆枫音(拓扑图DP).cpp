#include <cstdio>
#include <vector>
using namespace std;

typedef long long ll;

const int N=100005,M=200005,mo=1000000007;

int inv[M+100];

int n,m,x,y;

struct node;
struct edge{
	node *ed;
	edge *next;
} E[M<<1],*newE=E;
struct node{
	edge *pre,*suc;
	int ind;
	int deg;
	int flag;
	ll f;
	void dfs(int f){
		if(flag&f) return;
		flag|=f;
		for(edge *e=suc;e;e=e->next)
			e->ed->dfs(f);
	}
	void dp(){
		if(deg) return;
		f=f*inv[ind]%mo;
		for(edge *e=suc;e;e=e->next){
			(e->ed->f+=f)%=mo;
			e->ed->deg--;
			e->ed->dp();
		}
	}
} V[N];

void addedge(node *u,node *v){
	*newE=(edge){v,u->suc},u->suc=newE++;
	*newE=(edge){u,v->pre},v->pre=newE++;
	v->ind++;
}

int calc(){
	ll ans=1;
	for(int i=1;i<=n;i++) ans=ans*V[i].ind%mo;
	return ans;
}

int Main(){
	scanf("%d%d%d%d",&n,&m,&x,&y);
	inv[1]=1;
	for(int i=2;i<=m+5;i++) inv[i]=ll(mo-mo/i)*inv[mo%i]%mo;
	while(m--){
		int u,v; scanf("%d%d",&u,&v);
		addedge(V+u,V+v);
	}
	V[1].ind++;
	V[y].dfs(1);
	if(V[x].flag!=1){
		addedge(V+x,V+y);
		return calc();
	}
	if(x==y||y==1)
		return calc();
	V[y].ind++;
	int ans=calc();
	for(int i=1;i<=n;i++){
		V[i].deg=0;
		for(edge *e=V[i].pre;e;e=e->next) if(e->ed->flag&1)
			V[i].deg++;
	}
	V[y].f=1;
	V[y].dp();
	ans=ans*(1LL-V[x].f)%mo;
	return (ans+mo)%mo;
}
int main(){
	printf("%d\n",Main());
}
