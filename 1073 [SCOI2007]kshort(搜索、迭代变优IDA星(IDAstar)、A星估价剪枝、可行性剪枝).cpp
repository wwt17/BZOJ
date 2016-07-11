#include <cstdio>
#include <algorithm>
#include <queue>
using namespace std;
const int N=55,inf=(int)1e9+7;
int n,m,k,s,t,cnt,limit,nlim,tim;
struct node{
	pair<node*,int> next[2][N];
	int deg[2];
	int g,vis;
	bool inq;
} V[N];
queue<node*> q;
void calcg(){
	for(int i=1;i<=n;i++) V[i].g=inf;
	q.push(V+t);
	V[t].g=0;
	V[t].inq=1;
	while(!q.empty()){
		node *u=q.front(); q.pop(); u->inq=0;
		for(int e=0;e<u->deg[1];e++){
			node *v=u->next[1][e].first;
			if(u->g+u->next[1][e].second<v->g){
				v->g=u->g+u->next[1][e].second;
				if(!v->inq){
					v->inq=1;
					q.push(v);
				}
			}
		}
	}
}
int cntres;
node *res[N];
bool dfs(node *u,int f){
	if(u->inq) return 0;
	if(f+u->g>limit){
		nlim=min(nlim,f+u->g);
		return 0;
	}
	if(u==V+t){
		if(f+u->g==limit&&++cnt==k){
			res[cntres++]=u;
			return 1;
		}
		return 0;
	}
	u->inq=1;
	u->vis=++tim;
	q.push(u);
	while(!q.empty()){
		node *x=q.front(); q.pop();
		for(int e=0;e<x->deg[0];e++){
			node *y=x->next[0][e].first;
			if(y->vis!=tim&&!y->inq){
				y->vis=tim;
				if(y==V+t) break;
				q.push(y);
			}
		}
	}
	for(;!q.empty();q.pop());
	if(V[t].vis!=tim) return u->inq=0,0;
	for(int e=0;e<u->deg[0];e++)
		if(dfs(u->next[0][e].first,f+u->next[0][e].second))
			return u->inq=0,res[cntres++]=u,1;
	u->inq=0;
	return 0;
}
int main(){
	scanf("%d%d%d%d%d",&n,&m,&k,&s,&t);
	for(int i=0;i<m;i++){
		int u,v,l; scanf("%d%d%d",&u,&v,&l);
		V[u].next[0][V[u].deg[0]++]=make_pair(V+v,l);
		V[v].next[1][V[v].deg[1]++]=make_pair(V+u,l);
	}
	for(int i=1;i<=n;i++){
		sort(V[i].next[0],V[i].next[0]+V[i].deg[0]);
		sort(V[i].next[1],V[i].next[1]+V[i].deg[1]);
	}
	calcg();
	limit=V[s].g;
	while(limit<inf){
		nlim=inf;
		if(dfs(V+s,0)){
			for(int i=cntres-1;i>0;i--) printf("%d-",res[i]-V); printf("%d\n",res[0]-V);
			return 0;
		}
		limit=nlim;
	}
	puts("No");
}
