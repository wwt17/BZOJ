#include <cstdio>
#include <algorithm>
using namespace std;

const int N=52,maxT=N,Day=N+maxT,sizeV=Day*N,sizeE=Day*N*N,inf=maxT;
int n,m,t;
struct node;
struct edge{
	node *ed;
	edge *next;
	int cap;
} E[sizeE<<1],*newE=E;
int labtim;
struct node{
	edge *son;
	int lab,labtim;
} S[2],*T=S+1;
bool layer(){
	static node *q[sizeV];
	int head=0,tail=0;
	labtim++;
	q[tail++]=S;
	S->labtim=labtim;
	S->lab=0;
	while(head!=tail){
		node *u=q[head++];
		for(edge *e=u->son;e;e=e->next) if(e->cap){
			node *v=e->ed;
			if(v->labtim==labtim) continue;
			v->labtim=labtim;
			v->lab=u->lab+1;
			if(v==T)
				return true;
			q[tail++]=v;
		}
	}
	return false;
}

int flow(node *u,int F){
	if(u==T) return F;
	int left=F;
	for(edge *e=u->son;e&&left;e=e->next) if(e->cap){
		node *v=e->ed;
		if(v->labtim!=labtim||v->lab!=u->lab+1) continue;
		int f=flow(v,min(left,e->cap));
		e->cap-=f;
		E[e-E^1].cap+=f;
		left-=f;
	}
	if(left==F) u->labtim=0;
	return F-left;
}

int maxflow(){
	int ans=0,f;
	while(layer())
		while(f=flow(S,inf))
			ans+=f;
	return ans;
}

void addedge(node *u,node *v,int cap0=inf,int cap1=0){
	*newE=(edge){v,u->son,cap0},u->son=newE++;
	*newE=(edge){u,v->son,cap1},v->son=newE++;
}

node V[Day][N];
int g[N][N];

int main(){
	scanf("%d%d%d",&n,&m,&t);
	while(m--){
		int x,y,z; scanf("%d%d%d",&x,&y,&z);
		g[x][y]=z;
	}
	for(int i=1;i<=n;i++) g[i][i]=t;
	addedge(S,&V[0][1],t);
	int ans=0;
	for(int day=1;;day++){
		for(int i=1;i<=n;i++)
			for(int j=1;j<=n;j++) if(g[i][j])
				addedge(&V[day-1][i],&V[day][j],g[i][j]);
		addedge(&V[day][n],T,t);
		if((ans+=maxflow())==t){
			printf("%d\n",day);
			break;
		}
	}
}
