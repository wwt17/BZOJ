#include <cstdio>
#include <cmath>
#include <algorithm>
using namespace std;
const int N=705,M=100005,M1=40005,N1=169;
const double oo=1e9,eps=1e-9;
int n,m,n1,m1,son[N],next[M],ed[M],x[M],y[M],head,tail,q[N],deg[N];
double dis[N],sx[N],sy[N];

struct node;
struct edge{
	node *ed;
	edge *next;
	double cap;
} E[(N1+M1)<<1],*newE=E;
struct node{
	edge *son;
	int dist;
} S[2],V[N1],*T=S+1;

void addedge(node *u,node *v,double c){
	*newE=(edge){v,u->son,c},u->son=newE++;
	*newE=(edge){u,v->son,0},v->son=newE++;
}

bool layer(){
	static node *q[N1];
	int head=0,tail=0;
	for(int i=1;i<=n1;i++) V[i].dist=0;
	T->dist=0;
	S->dist=1;
	q[tail++]=S;
	while(head<tail){
		node *u=q[head++];
		for(edge *e=u->son;e;e=e->next) if(e->cap>eps&&!e->ed->dist){
			e->ed->dist=u->dist+1;
			if(e->ed==T)
				return true;
			q[tail++]=e->ed;
		}
	}
	return false;
}

double flow(node *u,double F){
	if(u==T) return F;
	double left=F;
	for(edge *e=u->son;e&&left>eps;e=e->next) if(e->cap>eps&&e->ed->dist==u->dist+1){
		double f=flow(e->ed,min(left,e->cap));
		left-=f;
		e->cap-=f;
		E[e-E^1].cap+=f;
	}
	if(F-left<eps) u->dist=0;
	return F-left;
}

int main(){
	scanf("%d%d",&n,&m);
	for(int e=1;e<=m;e++){
		int u;
		scanf("%d%d%d%d",&u,&ed[e],&x[e],&y[e]);
		next[e]=son[u];
		son[u]=e;
		deg[ed[e]]++;
	}
	for(int i=1;i<=n;i++) if(!deg[i])
		q[tail++]=i;
	while(head<tail){
		int u=q[head++];
		for(int e=son[u];e;e=next[e]){
			int v=ed[e];
			if(!--deg[v])
				q[tail++]=v;
		}
	}
	scanf("%d%d",&m1,&n1);
	for(int t=1;t<=n1;t++){
		double danger=0;
		for(;;){
			for(int i=1;i<=n;i++) dis[i]=oo,sx[i]=sy[i]=oo;
			dis[n]=0;
			sx[n]=sy[n]=0;
			for(int i=0;i<tail;i++){
				int u=q[i];
				for(int e=son[u];e;e=next[e]){
					int v=ed[e];
					double val=dis[u]+x[e]-danger*y[e];
					if(val<dis[v]) dis[v]=val,sx[v]=sx[u]+x[e],sy[v]=sy[u]+y[e];
				}
			}
			if(dis[t]==oo){
				danger=oo;
				break;
			}
			double newdanger=sx[t]/sy[t];
			if(fabs(newdanger-danger)<1e-3) break;
			danger=newdanger;
		}
		if(t&1)
			addedge(S,V+t,danger);
		else
			addedge(V+t,T,danger);
	}
	while(m1--){
		int u,v; scanf("%d%d",&u,&v);
		addedge(V+u,V+v,oo);
	}
	double ans=0;
	while(layer()){
		double f;
		while((f=flow(S,oo))>eps)
			ans+=f;
	}
	if(ans>=oo)
		puts("-1");
	else
		printf("%.1lf\n",ans);
}
