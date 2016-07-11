#include <cstdio>
#include <queue>
#include <algorithm>
using namespace std;
const int N=1005,M=1005,inf=2100000000;
int n,m;
struct node;
struct edge{
	node *ed; int next; int cap;
} E[N*M*2<<1]; int newE=2;
struct node{
	int son; int depth;
} S[2],*T=S+1,crop[N],gether[M][2];
inline void addedge(node *u,node *v,int c){
	E[newE]=(edge){v,u->son,c},u->son=newE++;
	E[newE]=(edge){u,v->son,0},v->son=newE++;
}
bool build(){
	queue<node*> q;
	for(int i=1;i<=n;i++) crop[i].depth=0;
	for(int i=0;i<m;i++) gether[i][0].depth=gether[i][1].depth=0;
	T->depth=0;
	S->depth=1;
	q.push(S);
	while(!q.empty()){
		node *u=q.front(); q.pop();
		for(int e=u->son;e;e=E[e].next) if(E[e].cap){
			node *v=E[e].ed;
			if(!v->depth){
				v->depth=u->depth+1;
				if(v==T) return true;
				q.push(v);
			}
		}
	}
	return false;
}
int flow(node *u,int F){
	if(u==T) return F;
	int left=F;
	node *v;
	for(int e=u->son;e&&left;e=E[e].next) if(E[e].cap&&(v=E[e].ed)->depth==u->depth+1){
		int f=flow(v,min(left,E[e].cap));
		left-=f;
		E[e].cap-=f;
		E[e^1].cap+=f;
	}
	if(!(F-=left)) u->depth=0;
	return F;
}
int main(){
	scanf("%d",&n);
	int tot=0;
	for(int i=1;i<=n;i++){
		static int a; scanf("%d",&a);
		addedge(S,&crop[i],a);
		tot+=a;
	}
	for(int i=1;i<=n;i++){
		static int b; scanf("%d",&b);
		addedge(&crop[i],T,b);
		tot+=b;
	}
	scanf("%d",&m);
	for(int i=0;i<m;i++){
		static int k,c1,c2;
		scanf("%d",&k);
		scanf("%d%d",&c1,&c2);
		addedge(S,&gether[i][0],c1);
		addedge(&gether[i][1],T,c2);
		tot+=c1+c2;
		while(k--){
			static int j; scanf("%d",&j);
			addedge(&gether[i][0],&crop[j],inf);
			addedge(&crop[j],&gether[i][1],inf);
		}
	}
	int ans=tot;
	while(build()){
		int f;
		while(f=flow(S,inf))
			ans-=f;
	}
	printf("%d\n",ans);
}
