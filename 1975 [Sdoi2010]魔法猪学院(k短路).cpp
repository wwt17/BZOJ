#include <cstdio>
#include <algorithm>
#include <queue>
using namespace std;
typedef pair<int,int> pii;

const int N=5005,M=200005;

const double oo=1./0;

int n,m;
double tot;
struct node;
struct edge{
	node *ed;
	edge *next;
	double w;
} E[M],*newE=E;
struct node{
	edge *son;
	double g;
	bool inq;
} V[N],*q[N];
int head=0,tail=0;
struct Edge{
	node *u,*v;
	double w;
	void read(){
		int x,y; scanf("%d%d%lf",&x,&y,&w);
		u=V+x; v=V+y;
	}
} seq[M];
void addedge(node *u,node *v,double w){
	*newE=(edge){v,u->son,w},u->son=newE++;
}
struct data{
	node *u;
	double f;
};
bool operator < (const data &a,const data &b){
	return a.f+a.u->g>b.f+b.u->g;
}
priority_queue<data> s;

int main(){
	scanf("%d%d%lf",&n,&m,&tot);
	for(int i=0;i<m;i++){
		seq[i].read();
		addedge(seq[i].v,seq[i].u,seq[i].w);
	}
	for(int i=1;i<=n;i++) V[i].g=oo;
	V[n].g=0;
	V[n].inq=true;
	q[tail++]=V+n;
	while(head!=tail){
		node *u=q[head];
		u->inq=false;
		if(++head==N) head=0;
		for(edge *e=u->son;e;e=e->next){
			node *v=e->ed;
			if(u->g+e->w<v->g){
				v->g=u->g+e->w;
				if(!v->inq){
					v->inq=true;
					q[tail]=v;
					if(++tail==N) tail=0;
				}
			}
		}
	}
	newE=E;
	for(int i=1;i<=n;i++) V[i].son=NULL;
	for(int i=0;i<m;i++) addedge(seq[i].u,seq[i].v,seq[i].w);
	s.push((data){V+1,0});
	int ans=0;
	while(!s.empty()){
		node *u=s.top().u;
		double f=s.top().f;
		s.pop();
		if(u==V+n){
			if(tot<f) break;
			tot-=f;
			ans++;
			continue;
		}
		for(edge *e=u->son;e;e=e->next)
			s.push((data){e->ed,f+e->w});
	}
	printf("%d\n",ans);
}
