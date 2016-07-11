#include <cstdio>
#include <cstdlib>
#include <queue>
using namespace std;
#define size 1000
#define inf 0x7fffffff
int N,M,i,j,W;
struct node;
struct edge {
	int w;
	node* link;
	edge* next;
	edge(node* Link,edge* Next) {
		w=W,link=Link,next=Next;
	}
} *e;
struct node {
	int dist;
	edge* son;
	bool inq;
	node() {
		dist=inf;
		son=NULL;
		inq=false;
	}
	void add(node* Link) {
		e=new edge(Link,son);
		son=e;
	}
} *V[size][size][2],*S=new node,*T=new node;
inline void input() { scanf("%d",&W); }
inline void link(node* a,node* b) {
	a->add(b); b->add(a);
}
inline bool relaxed(int &a,int b) {
	if (a>b) { a=b; return true; }
	return false;
}
void spc(int k) {
	int ans=inf;
	while (k--)
		input(),ans>W?ans=W:0;
	printf("%d\n",ans);
	system("pause");
	exit(0);
}
int main() {
	scanf("%d%d",&N,&M);
	if (N==1) spc(M);
	if (M==1) spc(N);
	for (i=1;i<N;++i)
		for (j=1;j<M;++j)
			V[i][j][0]=new node,
			V[i][j][1]=new node;
	
	for (j=1;j<M;++j)
		input(),V[1][j][1]->add(T);
	for (i=1;i<N-1;++i)
		for (j=1;j<M;++j)
			input(),link(V[i][j][0],V[i+1][j][1]);
	for (j=1;j<M;++j)
		input(),S->add(V[i][j][0]);
	
	for (i=1;i<N;++i) {
		input(),S->add(V[i][1][0]);
		for (j=1;j<M-1;++j)
			input(),link(V[i][j][1],V[i][j+1][0]);
		input(),V[i][j][1]->add(T);
	}
	
	for (i=1;i<N;++i)
		for (j=1;j<M;++j)
			input(),link(V[i][j][0],V[i][j][1]);
	//SPFA
	queue<node*> q;
	node *X,*Y;
	for (S->dist=0,S->inq=true,q.push(S);!q.empty();X->inq=false,q.pop())
		for (e=(X=q.front())->son;e;e=e->next)
			if (relaxed((Y=e->link)->dist,X->dist+e->w)&&!Y->inq)
				Y->inq=true,q.push(Y);
	printf("%d\n",T->dist);
	system("pause");
}
