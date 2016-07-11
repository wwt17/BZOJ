#include <stdio.h>
#include <math.h>
#include <queue>
#include <functional>
using namespace std;
#define float double
#define size 1001
inline float sqr(int x) { return x*x; }
int n,k;
struct node {
	int x,y;
	node* f;
	void init() {
		scanf("%d%d",&x,&y);
		f=this;
	}
	node* belong() {
		if (f==this) return this;
		return f=f->belong();
	}
} V[size];
struct edge {
	int u,v;
	float dist;
	friend bool operator < (const edge &x,const edge &y)
		{ return x.dist>y.dist; }
	void link()
		{ dist=sqrt(sqr(V[u].x-V[v].x)+sqr(V[u].y-V[v].y)); }
	int merge() {
		if (V[u].belong()==V[v].belong()) return 0;
		V[v].f->f=V[u].f; return 1;
	}
}E;
int main() {
	freopen("agroup.in","r",stdin);
	freopen("agroup.out","w",stdout);
	scanf("%d%d\n",&n,&k);
	priority_queue<edge> s;
	for (E.v=1;E.v<=n;++E.v) {
		V[E.v].init();
		for (E.u=1;E.u<E.v;++E.u)
			E.link(),s.push(E);
	}
	while (!(E=s.top()).merge()) s.pop();
	for (n;n>k;n-=(E=s.top()).merge(),s.pop());
	printf("%.2f\n",E.dist);
	//system("pause");
}
