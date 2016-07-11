#include <cstdio>
#include <cstdlib>
#define size 1001
int N,Q,i,A,B,L,s=0;
struct node;
struct edge {
	int len;
	node* link;
	edge* next;
} *e;
struct node {
	node* fth;
	edge* son;
	int dis;
	void add(node* Link,int Len) {
		e=new edge;
		*e=(edge){ Len, Link, son };
		son=e;
	}
	void DFS(node* father,int dist) {
		fth=father,dis=dist;
		for (edge* e=son;e;e=e->next)
			if (e->link!=fth)
				e->link->DFS(this,dist+e->len);
	}
	bool vis;
} V[size];
node* LCA(node* a,node* b) {
	node* i=a;
	for (;i;i=i->fth) i->vis=true;
	node* j=b;
	for (;j;j=j->fth) if (j->vis) {
		for (i=a;i;i=i->fth) i->vis=false;
		return j;
	}
}
int main() {
	scanf("%d%d",&N,&Q);
	for (i=1;i<N;++i) {
		scanf("%d%d%d",&A,&B,&L);
		V[A].add(&V[B],L);
		V[B].add(&V[A],L);
	}
	V[1].DFS(NULL,0);
	while (Q--) {
		scanf("%d%d",&A,&B);
		printf("%d\n",V[A].dis+V[B].dis-(LCA(&V[A],&V[B])->dis<<1));
	}
	//system("pause");
}
