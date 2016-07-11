#include <cstdio>
#include <queue>
#include <functional>
using namespace std;

const int N=100005,M=N;

int n,m;

struct node;
struct edge{
	node *ed;
	edge *next;
} E[M],*newE;
struct node{
	edge *son;
	int deg;
} V[N];
int len;
node *seq[N];
priority_queue<node*> q;

void Main(){
	scanf("%d%d",&n,&m);
	newE=E;
	for(int i=1;i<=n;i++) V[i].son=NULL,V[i].deg=0;
	while(m--){
		int x,y; scanf("%d%d",&x,&y);
		*newE=(edge){V+x,V[y].son},V[y].son=newE++;
		V[x].deg++;
	}
	for(int i=1;i<=n;i++) if(V[i].deg==0) q.push(V+i);
	for(int i=n;i>=1;i--){
		if(q.empty()){
			puts("Impossible!");
			return;
		}
		seq[i]=q.top(); q.pop();
		for(edge *e=seq[i]->son;e;e=e->next) if(!--e->ed->deg)
			q.push(e->ed);
	}
	for(int i=1;i<=n;i++) printf("%d ",seq[i]-V);
	puts("");
}

int main(){
	int T; scanf("%d",&T);
	while(T--)
		Main();
}
