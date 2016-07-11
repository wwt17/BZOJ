#include <cstdio>
#include <algorithm>
#include <queue>
using namespace std;
const int N=100,M=N*N*3,inf=0x7FFFFFFF;
typedef int data;
inline void read(data &a){
	char c; bool f=false;
	while((c=getchar())<'0'||c>'9') if(c=='-') f^=1; a=c-'0';
	while((c=getchar())>='0'&&c<='9') a=a*10+c-'0'; if(f) a=-a;
}
#define read2(a,b) (read(a),read(b))
#define read3(a,b,c) (read2(a,b),read(c))
int n,m,newE=2; data Ans=0,Flow;
struct node;
struct edge{
	int next; node *ed; data cap;
} E[M*2+2];
struct node{
	int depth,son;
	node():son(0){}
} V[N][N],*S,*T;//define nodes
inline void addedge(node *u,node *v,const int c1,const int c2){
	E[newE].next=u->son,E[newE].ed=v,E[newE].cap=c1,u->son=newE++;
	E[newE].next=v->son,E[newE].ed=u,E[newE].cap=c2,v->son=newE++;
}
bool layered(){
	//clear
	for(int i=0;i<n;i++)
		for(int j=0;j<m;j++)
			V[i][j].depth=0;
	T->depth=0;
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
	//make graph
	read2(n,m);
	S=new node; T=new node;
	int flag;
	for(int i=0;i<n;i++)
		for(int j=0;j<m;j++){
			read(flag);
			switch(flag){
				case 1: addedge(S,&V[i][j],inf,0); break;
				case 2: addedge(&V[i][j],T,inf,0); break;
			}
			if(i) addedge(&V[i][j],&V[i-1][j],1,1);
			if(j) addedge(&V[i][j],&V[i][j-1],1,1);
		}
	//calc flow
	while(layered())
		while(Flow=flow(S,inf))
			Ans+=Flow;
	printf("%d\n",Ans);
	scanf("\n");
}
