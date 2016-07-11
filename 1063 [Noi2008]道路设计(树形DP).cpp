#include <cstdio>
#include <algorithm>
using namespace std;
const int N=100005,M=N,logN=25;
int n,m,mo;
struct node;
struct edge{
	node *ed;
	edge *next;
} E[M<<1],*newE=E;
struct node{
	edge *son;
	node *pa,*belong;
	int g[3],f[logN][3];
	node* get(){
		return belong?(belong=belong->get()):this;
	}
	void dfs(){
		g[0]=0;
		g[1]=N;
		g[2]=N;
		for(edge *e=son;e;e=e->next) if(e->ed!=pa){
			node *v=e->ed;
			v->pa=this;
			v->dfs();
			int t0=min(min(1+v->g[0],1+v->g[1]),1+v->g[2]);
			int t1=min(v->g[0],v->g[1]);
			g[2]=min(max(g[2],t0),max(g[1],t1));
			g[1]=min(max(g[1],t0),max(g[0],t1));
			g[0]=max(g[0],t0);
		}
	}
	void work(){
		for(int j=0;j<=m;j++) f[j][0]=1;
		for(edge *e=son;e;e=e->next) if(e->ed!=pa){
			node *v=e->ed;
			v->work();
			for(int j=0;j<=m;j++){
				int t0=!j?0:(v->f[j-1][0]+v->f[j-1][1]+v->f[j-1][2])%mo;
				int t1=(v->f[j][0]+v->f[j][1])%mo;
				f[j][2]=(1LL*f[j][2]*t0+1LL*f[j][1]*t1)%mo;
				f[j][1]=(1LL*f[j][1]*t0+1LL*f[j][0]*t1)%mo;
				f[j][0]=1LL*f[j][0]*t0%mo;
			}
		}
	}
} V[N];
int main(){
	scanf("%d%d%d",&n,&m,&mo);
	if(m!=n-1) return printf("-1\n-1\n"),0;
	for(int i=0;i<m;i++){
		int a,b; scanf("%d%d",&a,&b);
		*newE=(edge){V+b,V[a].son},V[a].son=newE++;
		*newE=(edge){V+a,V[b].son},V[b].son=newE++;
		node *x=V[a].get(),*y=V[b].get();
		if(x==y) return printf("-1\n-1\n"),0;
		x->belong=y;
	}
	V[1].dfs();
	printf("%d\n",m=min(min(V[1].g[0],V[1].g[1]),V[1].g[2]));
	V[1].work();
	printf("%d\n",(V[1].f[m][0]+V[1].f[m][1]+V[1].f[m][2])%mo);
}
