#include <cstdio>
#include <algorithm>
using namespace std;
const int N=105,M=1005;
const double eps=1e-9,beps=1e-6;
double inf;
int n,m;

struct node;
struct edge{
	node *ed;
	edge *next;
	double w,cap;
} E[M<<1],*newE=E;
struct node{
	edge *son;
	int depth;
} V[N],*S,*T;

void addedge(node *u,node *v,double c){
	*newE=(edge){v,u->son,c,c},u->son=newE++;
	*newE=(edge){u,v->son,0,0},v->son=newE++;
}

bool layer(){
	static node *q[N];
	int head=0,tail=0;
	for(int i=1;i<=n;i++) V[i].depth=0;
	T->depth=0;
	S->depth=1;
	q[tail++]=S;
	while(head<tail){
		node *u=q[head++];
		for(edge *e=u->son;e;e=e->next) if(e->cap>eps&&!e->ed->depth){
			e->ed->depth=u->depth+1;
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
	for(edge *e=u->son;e&&left>eps;e=e->next) if(e->cap>eps&&e->ed->depth==u->depth+1){
		double f=flow(e->ed,min(left,e->cap));
		left-=f;
		e->cap-=f;
		E[e-E^1].cap+=f;
	}
	if(F-left<eps) u->depth=0;
	return F-left;
}

double maxflow(){
	double ans=0,f;
	while(layer())
		while((f=flow(S,inf))>eps)
			ans+=f;
	return ans;
}

int main(){
	int p;
	scanf("%d%d%d",&n,&m,&p);
	S=V+1;
	T=V+n;
	inf=beps;
	for(int i=0;i<m;i++){
		int x,y; double z; scanf("%d%d%lf",&x,&y,&z);
		addedge(V+x,V+y,z);
		inf+=z;
	}
	double l=0,r=inf;
	double res=maxflow();
	printf("%d\n",int(res+beps));
	while(r-l>beps){
		double mid=(l+r)/2;
		for(edge *e=E;e<newE;e++)
			e->cap=min(e->w,mid);
		if(maxflow()>=res-eps)
			r=mid;
		else
			l=mid;
	}
	printf("%lf\n",l*p);
}
