#include <cstdio>
#include <algorithm>
#include <queue>
using namespace std;
const int N=305,M=N*N,inf=0x7FFFFFFF;
typedef int data;
int n,m,newE=2; data Ans=0,Flow;
struct node;
struct edge{
	int next; node *ed; data cap;
} E[M*2+2];
struct node{
	int depth,son;
	node():son(0){}
} S[2],*T=S+1,V[N];//define nodes
inline void addedge(node *u,node *v,const int c1,const int c2=0){
	E[newE].next=u->son,E[newE].ed=v,E[newE].cap=c1,u->son=newE++;
	E[newE].next=v->son,E[newE].ed=u,E[newE].cap=c2,v->son=newE++;
}
bool layered(){
	//clear
	for(int i=1;i<=n;++i) V[i].depth=0; T->depth=0;
	queue<node*> q; node *u,*v;
	for(q.push(S),S->depth=1;!q.empty();q.pop())
		for(int e=(u=q.front())->son;e;e=E[e].next)
			if(E[e].cap&&!(v=E[e].ed)->depth){
				q.push(v),v->depth=u->depth+1;
				if(v==T) return true;
			}
	return false;
}
data flow(node* x,int F){
	if(x==T) return F;
	data left=F,Flow; node* y;
	for(int e=x->son;e&&left;e=E[e].next)
		if(E[e].cap&&x->depth+1==(y=E[e].ed)->depth&&(Flow=flow(y,min(left,E[e].cap))))
			E[e].cap-=Flow,E[e^1].cap+=Flow,left-=Flow;
	if(!(F-=left)) x->depth=0;
	return F;
}
int main(){
	scanf("%d%d",&n,&m);
	for(int i=1;i<=n;i++){
		int x; scanf("%d",&x);
		if(x) addedge(S,V+i,1);
		else  addedge(V+i,T,1);
	}
	for(int i=0;i<m;i++){
		int x,y; scanf("%d%d",&x,&y);
		addedge(V+x,V+y,1,1);
	}
	//calc flow
	while(layered())
		while(Flow=flow(S,inf))
			Ans+=Flow;
	printf("%d\n",Ans);
	scanf("\n");
}
