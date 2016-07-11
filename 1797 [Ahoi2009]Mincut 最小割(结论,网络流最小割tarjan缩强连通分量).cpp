#include <cstdio>
#include <queue>
#include <algorithm>
using namespace std;
const int N=4005,M=60005,inf=100000000;
int n,m;
inline int getint(){
	bool s=false;
	char c; while((c=getchar())<'0'||c>'9') if(c=='-') s^=1;
	int a=c-'0'; while((c=getchar())>='0'&&c<='9') a=a*10+c-'0';
	return s?-a:a;
}
struct node;
struct edge{
	node *ed;
	edge *next;
	int cap;
} E[M<<1];
struct node{
	edge *son;
	int depth,low,dfn; bool instack;
	node *belong;
	void tarjan(){
		static node *stack[N],**top=stack;
		static int num=0;
		low=dfn=++num;
		instack=true;
		*top++=this;
		for(edge *e=son;e;e=e->next) if(e->cap)
			if(!e->ed->dfn){
				e->ed->tarjan();
				low=min(low,e->ed->low);
			}
			else{
				if(e->ed->instack)
					low=min(low,e->ed->dfn);
			}
		if(low==dfn){
			do{
				top--;
				node *v=*top;
				v->instack=false;
				v->belong=this;
			} while(*top!=this);
		}
	}
} *S,*T,V[N];
bool layer(){
	queue<node*> q;
	for(int i=1;i<=n;i++) V[i].depth=0;
	S->depth=1;
	q.push(S);
	while(!q.empty()){
		node *u=q.front(); q.pop();
		for(edge *e=u->son;e;e=e->next) if(e->cap&&!e->ed->depth){
			e->ed->depth=u->depth+1;
			if(e->ed==T) return true;
			q.push(e->ed);
		}
	}
	return false;
}
int flow(node *u,int F){
	if(u==T) return F;
	int left=F;
	for(edge *e=u->son;left&&e;e=e->next) if(e->cap&&e->ed->depth==u->depth+1){
		int f=flow(e->ed,min(left,e->cap));
		left-=f;
		e->cap-=f;
		E[(e-E)^1].cap+=f;
	}
	if(left==F) u->depth=0;
	return F-left;
}
int main(){
	n=getint(),m=getint(),S=V+getint(),T=V+getint();
	for(int i=0;i<m;i++){
		node *u=V+getint(),*v=V+getint();
		int c=getint();
		E[i<<1  ]=(edge){v,u->son,c},u->son=E+(i<<1);
		E[i<<1|1]=(edge){u,v->son,0},v->son=E+(i<<1|1);
	}
	while(layer())
		while(flow(S,inf));
	for(int i=1;i<=n;i++) if(!V[i].belong)
		V[i].tarjan();
	for(int i=0;i<m;i++){
		node *x=E[i<<1|1].ed->belong,*y=E[i<<1].ed->belong;
		if(E[i<<1].cap||x==y) puts("0 0");
		else printf("1 %d\n",x==S->belong&&y==T->belong);
	}
	scanf("\n");
}
