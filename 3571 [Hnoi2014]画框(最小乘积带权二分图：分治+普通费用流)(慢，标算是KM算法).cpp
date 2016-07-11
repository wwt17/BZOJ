#include <cstdio>
#include <algorithm>
#include <queue>
using namespace std;

typedef long long ll;

const int N=75,M=N*N*2;

const ll inf=1e15;

int n;

struct vec{
	int x,y;
	vec(ll _x=0,int _y=0):x(_x),y(_y){
	}
	vec rotate(){
		return vec(-y,x);
	}
	int val(){
		return x*y;
	}
};

bool operator == (const vec &a,const vec &b){
	return a.x==b.x&&a.y==b.y;
}

vec operator + (const vec &a,const vec &b){
	return vec(a.x+b.x,a.y+b.y);
}

vec operator - (const vec &a,const vec &b){
	return vec(a.x-b.x,a.y-b.y);
}

int dot(const vec &a,const vec &b){
	return a.x*b.x+a.y*b.y;
}

struct node;
struct edge{
	node *ed;
	edge *next;
	int cap,cost;
} E[M<<1],*newE;
struct node{
	edge *son;
	ll dist;
	bool inq;
	edge *pre;
} S[2],*T=S+1,a[N],b[N];

edge *seq[N][N];

vec w[N][N];

void addedge(node *u,node *v,int cap,int cost){
	*newE=(edge){v,u->son,cap,cost},u->son=newE++;
	*newE=(edge){u,v->son,0, -cost},v->son=newE++;
}

vec calc(vec d){
	newE=E;
	S->son=T->son=NULL;
	for(int i=1;i<=n;i++){
		a[i].son=b[i].son=NULL;
		addedge(S,&a[i],1,0);
		addedge(&b[i],T,1,0);
	}
	for(int i=1;i<=n;i++)
		for(int j=1;j<=n;j++){
			seq[i][j]=newE;
			addedge(&a[i],&b[j],1,dot(w[i][j],d));
		}
	for(;;){
		static queue<node*> q;
		T->dist=inf;
		for(int i=1;i<=n;i++) a[i].dist=b[i].dist=inf;
		S->dist=0;
		S->inq=true;
		q.push(S);
		while(!q.empty()){
			node *u=q.front(); q.pop();
			u->inq=false;
			for(edge *e=u->son;e;e=e->next) if(e->cap){
				node *v=e->ed;
				if(u->dist+e->cost<v->dist){
					v->dist=u->dist+e->cost;
					v->pre=e;
					if(!v->inq){
						v->inq=true;
						q.push(v);
					}
				}
			}
		}
		if(T->dist==inf) break;
		for(node *u=T;u!=S;u=E[(u->pre-E)^1].ed)
			u->pre->cap--,E[(u->pre-E)^1].cap++;
	}
	vec ans;
	for(int i=1;i<=n;i++)
		for(int j=1;j<=n;j++)
			if(!seq[i][j]->cap)
				ans=ans+w[i][j];
	return ans;
}
int work(vec l,vec r){
	vec mid=calc((r-l).rotate());
	if(mid==l||mid==r)
		return l.val();
	return min(work(l,mid),work(mid,r));
}
int Main(){
	scanf("%d",&n);
	for(int i=1;i<=n;i++)
		for(int j=1;j<=n;j++)
			scanf("%d",&w[i][j].x);
	for(int i=1;i<=n;i++)
		for(int j=1;j<=n;j++)
			scanf("%d",&w[i][j].y);
	vec l=calc(vec(1,0)),r=calc(vec(0,1));
	return min(work(l,r),r.val());
}

int main(){
	int T; scanf("%d",&T);
	while(T--)
		printf("%d\n",Main());
}
