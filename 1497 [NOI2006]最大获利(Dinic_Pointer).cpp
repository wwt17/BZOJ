#include <cstdio>
#include <queue>
#define inf 0x7FFFFFFF
typedef int data;
inline int min(const int a,const int b){return a<b?a:b;}
inline void read(int &a){
	char c;
	for (c=getchar();c<'0'||'9'<c;c=getchar()); a=c-'0';
	for (c=getchar();'0'<=c&&c<='9';c=getchar()) a=a*10+(c-'0');
}
#define read2(a,b) (read(a),read(b))
#define read3(a,b,c) (read2(a,b),read(c))
int N,M;
struct node;
struct edge{
	edge *next,*oppo;
	node* ed;
	data cap;
} E[/*sizeedge*/310000],*Es=E;
struct node{
	int depth;
	edge* son;
	node():son(NULL){}
	edge* add_edge(node* To,data C){
		*Es=(edge){son,NULL,To,C}; return son=Es++;
	}
} *S,*T,sta[5001],cus[50001];//define nodes
inline void addedge(node* u,node* v,const int c1,const int c2){
	edge* e1=u->add_edge(v,c1);
	edge* e2=v->add_edge(u,c2);
	e1->oppo=e2;
	e2->oppo=e1;
}
#define addedge(u,v,c) addedge(u,v,c,0)
bool layered(){
	//clear
	for (int i=1;i<=N;++i) sta[i].depth=0;
	for (int i=1;i<=M;++i) cus[i].depth=0;
	T->depth=0;
	std::queue<node*> q; node *x,*y;
	for (q.push(S),S->depth=1;!q.empty();q.pop())
		for (edge* e=(x=q.front())->son;e;e=e->next)
			if (e->cap&&!(y=e->ed)->depth){
				q.push(y),y->depth=x->depth+1;
				if (y==T) return true;
			}
	return false;
}
data flow(node* x,int F){
	if (x==T) return F;
	data left=F,Flow; node* y;
	for (edge* e=x->son;e&&left;e=e->next)
		if (e->cap&&x->depth+1==(y=e->ed)->depth&&(Flow=flow(y,min(left,e->cap))))
			e->cap-=Flow,e->oppo->cap+=Flow,left-=Flow;
	if (!(F-=left)) x->depth=0;
	return F;
}
int main(){
	//make graph
	int tot=0,Pi,Ai,Bi,Ci,i;
	read2(N,M);
	S=new node,T=new node;
	for (i=1;i<=N;++i){
		read(Pi);
		addedge(S,sta+i,Pi);
	}
	for (i=1;i<=M;++i){
		read3(Ai,Bi,Ci);
		addedge(sta+Ai,cus+i,inf);
		addedge(sta+Bi,cus+i,inf);
		addedge(cus+i,T,Ci);
		tot+=Ci;
	}
	//calc flow
	data Ans=0,Flow;
	while (layered())
		while (Flow=flow(S,inf))
			Ans+=Flow;
	printf("%d\n",tot-Ans);
	scanf("%d");
}
