#include <cstdio>
#include <queue>
using namespace std;
const int N=1005,M=N;
int n,m;
struct node;
struct edge{
	node *ed;
	edge *next;
} E[M<<1],*newE=E;
struct node{
	edge *son;
	int deg,dist;
	bool inq;
} V[N];
int path[N][N];
queue<node*> q;
void dfs(int i,int j,int k){
	if(path[i][k]) return;
	path[i][k]=j;
	for(edge *e=V[k].son;e;e=e->next)
		if(e->ed->dist==V[k].dist+1)
			dfs(i,j,e->ed-V);
}
double f[N][N];
double dp(int i,int j){
	double &ans=f[i][j];
	if(ans!=-1) return ans;
	if(i==j) return ans=0;
	i=path[i][j];
	if(i==j) return ans=1;
	i=path[i][j];
	if(i==j) return ans=1;
	ans=dp(i,j);
	for(edge *e=V[j].son;e;e=e->next){
		int k=e->ed-V;
		ans+=dp(i,k);
	}
	return ans=1+ans/(1+V[j].deg);
}
bool g[N];
int main(){
	scanf("%d%d",&n,&m);
	int s,t; scanf("%d%d",&s,&t);
	for(int i=0;i<m;i++){
		int x,y; scanf("%d%d",&x,&y);
		*newE=(edge){V+y,V[x].son},V[x].son=newE++; V[x].deg++;
		*newE=(edge){V+x,V[y].son},V[y].son=newE++; V[y].deg++;
	}
	for(int i=1;i<=n;i++){
		for(int j=1;j<=n;j++) V[j].dist=M,f[i][j]=-1;
		q.push(V+i);
		V[i].dist=0;
		V[i].inq=1;
		while(!q.empty()){
			node *u=q.front(); q.pop(); u->inq=0;
			for(edge *e=u->son;e;e=e->next){
				node *v=e->ed;
				if(u->dist+1<v->dist){
					v->dist=u->dist+1;
					if(!v->inq){
						v->inq=1;
						q.push(v);
					}
				}
			}
		}
		path[i][i]=i;
		for(int j=1;j<=n;j++) g[j]=0;
		for(edge *e=V[i].son;e;e=e->next) g[e->ed-V]=1;
		for(int j=1;j<=n;j++) if(g[j]) dfs(i,j,j);
	}
	printf("%.3lf\n",dp(s,t));
}
