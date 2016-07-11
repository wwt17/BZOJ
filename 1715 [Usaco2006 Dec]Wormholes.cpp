#include <cstdio>
#include <algorithm>
#include <queue>
int F,N,M,W,S,E,T,X,Y;
struct edge {
	int w,link;
	edge* next;
	edge(int _link,edge* _next):w(T),link(_link),next(_next) {}
};
struct node {
	edge* son;
	int dist,cnt;
	bool inq;
	void add(int b) {
		son=new edge(b,son);
	}
	void init() {
		son=NULL;
		dist=0;
		cnt=1;
		inq=true;
	}
} v[501];
inline bool relaxed(int &a,const int &b) {
	if (a>b) { a=b; return true; }
	return false;
}
int main() {
	for (scanf("%d",&F);F;--F) {
		scanf("%d%d%d",&N,&M,&W);
		for (X=1;X<=N;++X) v[X].init();
		while (M--) {
			scanf("%d%d%d",&S,&E,&T);
			v[S].add(E);
			v[E].add(S);
		}
		while (W--) {
			scanf("%d%d%d",&S,&E,&T);
			T=-T;
			v[S].add(E);
		}
		std::queue<int> q; int X,Y; edge* e;
		for (X=1;X<=N;++X) q.push(X);
		for (;!q.empty();v[X].inq=false,q.pop())
			for (e=v[X=q.front()].son;e;e=e->next)
				if (relaxed(v[Y=e->link].dist,v[X].dist+e->w)&&!v[Y].inq)
					if (++v[Y].cnt>N) { printf("YES\n"); goto end; } else
						v[Y].inq=true,q.push(Y);
		printf("NO\n");
		end: ;
	}
	system("pause");
}
