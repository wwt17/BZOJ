#include <cstdio>
#include <cstdlib>
#include <vector>
#include <queue>
#include <functional>
using namespace std;
typedef long long ll;
const int N=3005,M=70005;

int n,m;

struct node;
struct edge{
	node *ed;
	edge *next;
	int w;
} E[M],*newE=E;
struct node{
	edge *son;
	bool vis;
	int cnt;
	bool extended;
	vector<node*> out;
} V[N];

typedef pair<ll,node*> data;

priority_queue<data,vector<data>,greater<data> > q;

void extend(ll tim,node *u){
	if(u==V+n){
		printf("%lld\n",tim);
		exit(0);
	}
	if(u->extended) return;
	u->extended=true;
	for(edge *e=u->son;e;e=e->next)
		q.push(data(tim+e->w,e->ed));
	for(vector<node*>::iterator it=u->out.begin();it!=u->out.end();it++){
		node *v=*it;
		if(!--v->cnt&&v->vis)
			extend(tim,v);
	}
}

int main(){
	scanf("%d%d",&n,&m);
	for(int i=0;i<m;i++){
		int u,v,w; scanf("%d%d%d",&u,&v,&w);
		*newE=(edge){V+v,V[u].son,w},V[u].son=newE++;
	}
	for(int i=1;i<=n;i++){
		scanf("%d",&V[i].cnt);
		for(int j=0;j<V[i].cnt;j++){
			int x; scanf("%d",&x);
			V[x].out.push_back(V+i);
		}
	}
	q.push(data(0,V+1));
	while(!q.empty()){
		ll tim=q.top().first;
		node *u=q.top().second;
		q.pop();
		if(u->vis) continue;
		u->vis=true;
		if(!u->cnt)
			extend(tim,u);
	}
}
