#include <cstdio>
#include <algorithm>
using namespace std;
const int N=200005,M=N*2+600005;
typedef bool data;
const data inf=true;
inline void read(int &a){
	char c; bool f=false;
	while((c=getchar())<'0'||c>'9') if(c=='-') f^=1; a=c-'0';
	while((c=getchar())>='0'&&c<='9') a=a*10+c-'0'; if(f) a=-a;
}
#define read2(a,b) (read(a),read(b))
#define read3(a,b,c) (read2(a,b),read(c))
int n,m,newE=2;
struct node;
struct edge{
	int next; node *ed; data cap;
} E[M*2+2];
struct node{
	int depth,son,mat,dfn,low; bool instack; node *belong;
	node():son(0){
	}
	void tarjan(){
		static node *stack[N*2+2],**top=stack;
		static int len=0;
		dfn=low=++len;
		*top++=this;
		instack=true;
		for(int e=son;e;e=E[e].next) if(E[e].cap){
			#define v E[e].ed
			if(!v->dfn){
				v->tarjan();
				low=min(low,v->low);
			}
			else
			if(v->instack)
				low=min(low,v->dfn);
			#undef v
		}
		if(dfn==low){
			do{
				node *v=*--top;
				v->instack=false;
				v->belong=this;
			} while(*top!=this);
		}
	}
} S[2],*T=S+1,V[N][2];
inline void addedge(node *u,node *v,const data c1=inf,const data c2=0){
	E[newE].next=u->son,E[newE].ed=v,E[newE].cap=c1,u->son=newE++;
	E[newE].next=v->son,E[newE].ed=u,E[newE].cap=c2,v->son=newE++;
}
bool layer(){
	static node *beg[N*2+5];
	node **head=beg,**tail=beg,*u,*v;
	for(int i=1;i<=n;i++){
		V[i][0].depth=0;
		V[i][1].depth=0;
		if(!V[i][0].mat){
			V[i][0].depth=1;
			*tail++=V[i];
		}
	}
	bool ok=false;
	while(head<tail)
		for(int e=(u=*head++)->son;e;e=E[e].next)
			if(E[e].cap&&!(v=E[e].ed)->depth){
				*tail++=v,v->depth=u->depth+1;
				if((v-V[0])&1&&!v->mat) ok=true;
			}
	return ok;
}
data flow(node *u){
	if(!u) return true;
	node *v;
	for(int e=u->son;e;e=E[e].next)
		if(E[e].cap&&u->depth+1==(v=E[e].ed)->depth){
			if(flow(E[v->mat].ed)){
				E[u->mat  ].cap^=1;
				E[u->mat^1].cap^=1;
				u->mat=e;
				v->mat=e^1;
				E[e  ].cap^=1;
				E[e^1].cap^=1;
				v->depth=0;
				return true;
			}
			v->depth=0;
		}
	return false;
}
int main(){
	read2(n,m);
	int u,v;
	for(int i=1;i<=m;i++){
		read2(u,v);
		addedge(V[u],V[v]+1);
	}
	while(true){
		layer();
		bool ok=false;
		for(int i=1;i<=n;i++) if(!V[i][0].mat) ok|=flow(V[i]);
		if(!ok) break;
	}
	for(int i=1;i<=n;i++){
		if(V[i][0].mat)
			addedge(S,V[i],0,1);
		else
			addedge(S,V[i],1,0);
		if(V[i][1].mat)
			addedge(V[i]+1,T,0,1);
		else
			addedge(V[i]+1,T,1,0);
	}
	if(!S->dfn) S->tarjan();
	if(!T->dfn) T->tarjan();
	for(int i=1;i<=m;i++)
		putchar(E[i<<1].ed->belong==E[i<<1|1].ed->belong?'0':E[i<<1].cap?'2':'1');
	puts("");
}
