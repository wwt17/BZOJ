/*
注意：门不能当空地走过去 
*/
#include <cstdio>
#include <queue>
#include <algorithm>
using namespace std;
const int inf=(int)1e8;
const int N=22,M=N*4*N*N+N*N*N*4+N*N;
int n,m,tim,cnt;
char a[N][N];
int dist[N][N];
struct node;
struct edge{
	node *ed;
	edge *next;
	int cap;
} E[M<<1],*newE;
struct node{
	edge *son;
	int d;
} S[2],*T=S+1,V[N*N][N][N];
void addedge(node *u,node *v,int cap0=inf,int cap1=0){
	*newE=(edge){v,u->son,cap0},u->son=newE++;
	*newE=(edge){u,v->son,cap1},v->son=newE++;
}
bool build(){
	for(int i=1;i<=n;i++)
		for(int j=1;j<=m;j++)
			if(a[i][j]=='.')
				V[0][i][j].d=0;
			else
			if(a[i][j]=='D')
				for(int t=0;t<=tim;t++)
					V[t][i][j].d=0;
	S->d=T->d=0;
	queue<node*> q;
	q.push(S);
	S->d=1;
	while(!q.empty()){
		node *u=q.front(); q.pop();
		for(edge *e=u->son;e;e=e->next) if(e->cap){
			node *v=e->ed;
			if(v->d) continue;
			v->d=u->d+1;
			q.push(v);
			if(v==T) return 1;
		}
	}
	return 0;
}
int flow(node *u,int left){
	if(u==T) return left;
	int tmp=left;
	for(edge *e=u->son;e&&left;e=e->next) if(e->cap&&e->ed->d==u->d+1){
		int t=flow(e->ed,min(left,e->cap));
		left-=t;
		e->cap-=t;
		E[e-E^1].cap+=t;
	}
	if(left==tmp) u->d=0;
	return tmp-left;
}
int main(){
	scanf("%d%d",&n,&m);
	for(int i=1;i<=n;i++)
		scanf("%s",a[i]+1);
	int l=-1,r=n*m+1;
	while(r-l>1){
		tim=r-(r-l)/2;
		newE=E;
		cnt=0;
		for(int i=1;i<=n;i++)
			for(int j=1;j<=m;j++)
				if(a[i][j]=='.')
					V[0][i][j].son=NULL;
				else
				if(a[i][j]=='D'){
					for(int t=0;t<=tim;t++)
						V[t][i][j].son=NULL;
				}
		S->son=T->son=NULL;
		for(int i=1;i<=n;i++)
			for(int j=1;j<=m;j++)
			if(a[i][j]=='D'){
				for(int t=0;t<=tim;t++){
					addedge(&V[t][i][j],T,1);
					if(t<tim)
						addedge(&V[t][i][j],&V[t+1][i][j]);
				}
			}
			else if(a[i][j]=='.'){
				cnt++;
				addedge(S,&V[0][i][j],1);
				for(int x=1;x<=n;x++)
					for(int y=1;y<=m;y++)
						dist[x][y]=a[x][y]=='X'?0:n*m+1;
				static int q[N*N][2];
				int head=0,tail=0;
				dist[i][j]=0;
				q[tail][0]=i;
				q[tail][1]=j;
				tail++;
				while(head<tail){
					if(dist[q[tail][0]=q[head][0]-1][q[tail][1]=q[head][1]]==n*m+1){
						dist[q[tail][0]][q[tail][1]]=dist[q[head][0]][q[head][1]]+1;
						if(a[q[tail][0]][q[tail][1]]!='D') tail++;
					}
					if(dist[q[tail][0]=q[head][0]+1][q[tail][1]=q[head][1]]==n*m+1){
						dist[q[tail][0]][q[tail][1]]=dist[q[head][0]][q[head][1]]+1;
						if(a[q[tail][0]][q[tail][1]]!='D') tail++;
					}
					if(dist[q[tail][0]=q[head][0]][q[tail][1]=q[head][1]-1]==n*m+1){
						dist[q[tail][0]][q[tail][1]]=dist[q[head][0]][q[head][1]]+1;
						if(a[q[tail][0]][q[tail][1]]!='D') tail++;
					}
					if(dist[q[tail][0]=q[head][0]][q[tail][1]=q[head][1]+1]==n*m+1){
						dist[q[tail][0]][q[tail][1]]=dist[q[head][0]][q[head][1]]+1;
						if(a[q[tail][0]][q[tail][1]]!='D') tail++;
					}
					head++;
				}
				for(int x=1;x<=n;x++)
					for(int y=1;y<=m;y++)
						if(a[x][y]=='D'&&dist[x][y]<=tim)
							addedge(&V[0][i][j],&V[dist[x][y]][x][y],1);
			}
		int ans=cnt;
		while(build()){
			int f;
			while(f=flow(S,inf))
				ans-=f;
		}
		if(ans)
			l=tim;
		else
			r=tim;
	}
	if(r<n*m+1)
		printf("%d\n",r);
	else
		puts("impossible");
}
