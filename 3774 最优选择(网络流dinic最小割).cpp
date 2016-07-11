#include <cstdio>
#include <queue>
#include <algorithm>
using namespace std;
const int inf=(int)1e8;
const int N=55,M=6*N*N;
int n,m,ans;
struct node;
struct edge{
	node *ed;
	edge *next;
	int cap;
} E[M<<1],*newE=E;
struct node{
	edge *son;
	int d;
} S[2],*T=S+1,a[N][N],b[N][N];
void addedge(node *u,node *v,int cap0=inf,int cap1=0){
	*newE=(edge){v,u->son,cap0},u->son=newE++;
	*newE=(edge){u,v->son,cap1},v->son=newE++;
}
bool build(){
	for(int i=0;i<n;i++)
		for(int j=0;j<m;j++)
			a[i][j].d=b[i][j].d=0;
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
	for(int i=0;i<n;i++)
		for(int j=0;j<m;j++){
			int x; scanf("%d",&x);
			if(i+j&1)
				addedge(&a[i][j],T,x);
			else
				addedge(S,&a[i][j],x);
		}
	for(int i=0;i<n;i++)
		for(int j=0;j<m;j++){
			int x; scanf("%d",&x);
			ans+=x;
			if(i+j&1)
				addedge(&b[i][j],&a[i][j],x);
			else
				addedge(&a[i][j],&b[i][j],x);
		}
	for(int i=0;i<n;i++)
		for(int j=0;j<m;j++)
			if(i+j&1){
				if(i) addedge(&a[i-1][j],&b[i][j]);
				if(j) addedge(&a[i][j-1],&b[i][j]);
				if(i+1<n) addedge(&a[i+1][j],&b[i][j]);
				if(j+1<m) addedge(&a[i][j+1],&b[i][j]);
			}
			else{
				if(i) addedge(&b[i][j],&a[i-1][j]);
				if(j) addedge(&b[i][j],&a[i][j-1]);
				if(i+1<n) addedge(&b[i][j],&a[i+1][j]);
				if(j+1<m) addedge(&b[i][j],&a[i][j+1]);
			}
	while(build()){
		int f;
		while(f=flow(S,inf))
			ans-=f;
	}
	printf("%d\n",ans);
}
