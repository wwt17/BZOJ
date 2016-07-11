#include <cstdio>
#include <algorithm>
#include <list>
using namespace std;
const int N=45,M=N*N*N*5;
int p,q,r,d;
typedef int data;
const data inf=0x7FFFFFFF;
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
} S[2],*T=S+1,V[N][N][N];
inline void addedge(node *u,node *v,const data c1=inf,const data c2=0){
	E[newE].next=u->son,E[newE].ed=v,E[newE].cap=c1,u->son=newE++;
	E[newE].next=v->son,E[newE].ed=u,E[newE].cap=c2,v->son=newE++;
}
bool layer(){
	for(int x=1;x<=p;x++)
		for(int y=1;y<=q;y++)
			for(int z=0;z<=r;z++)
				V[x][y][z].depth=0;
	T->depth=0;
	list<node*> q; node *u,*v;
	for(q.push_back(S),S->depth=1;!q.empty();q.pop_front())
		for(int e=(u=q.front())->son;e;e=E[e].next)
			if(E[e].cap&&!(v=E[e].ed)->depth){
				q.push_back(v),v->depth=u->depth+1;
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
	read3(p,q,r);
	read(d);
	for(int z=1;z<=r;z++)
		for(int x=1;x<=p;x++)
			for(int y=1;y<=q;y++){
				int v; read(v);
				addedge(&V[x][y][z-1],&V[x][y][z],v);
				if(z>=d){
					if(x>1) addedge(&V[x][y][z],&V[x-1][y][z-d]);
					if(x<p) addedge(&V[x][y][z],&V[x+1][y][z-d]);
					if(y>1) addedge(&V[x][y][z],&V[x][y-1][z-d]);
					if(y<q) addedge(&V[x][y][z],&V[x][y+1][z-d]);
				}
			}
	for(int x=1;x<=p;x++)
		for(int y=1;y<=q;y++){
			addedge(S,&V[x][y][0]);
			addedge(&V[x][y][r],T);
		}
	data ans=0;
	while(layer()){
		data f;
		while(f=flow(S,inf))
			ans+=f;
	}
	printf("%d\n",ans);
}
