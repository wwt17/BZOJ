#include <cstdio>
#include <cmath>
#include <algorithm>
using namespace std;
typedef double db;
inline db sqr(const db x){
	return x*x;
}
inline db fix(const db x){
	return abs(x)<1e-6?0:x;
}
const int N=100005,M=N,logN=17;
int n,m,q;
struct node;
struct edge{
	node *ed;
	edge *next;
} E[M<<1],*newE=E;
struct node{
	edge *son;
	node *pa[logN];
	db A,B,C,D,E,F,sA,sB,sC,sD,sE,sF;
	int num,depth;
	bool oncir;
	void read(){
		db x,y; scanf("%lf%lf",&x,&y);
		A=(sqr(x)-sqr(y))/2;
		B=x*y;
		C=2*x;
		D=2*y;
		E=1;
		F=(sqr(x)+sqr(y))/2;
	}
	void renew(){
		depth=pa[0]->depth+1;
		sA=A+pa[0]->sA;
		sB=B+pa[0]->sB;
		sC=C+pa[0]->sC;
		sD=D+pa[0]->sD;
		sE=E+pa[0]->sE;
		sF=F+pa[0]->sF;
	}
	void getcir();
	void dfs();
} V[N],*seq[N];
int cnt,now;
db tA[N],tB[N],tC[N],tD[N],tE[N],tF[N];
db calc(db A,db B,db C,db D,db E,db F){
	return F-(sqr(C)+sqr(D))/8/E-sqrt(sqr(A+(sqr(D)-sqr(C))/8/E)+sqr(B-C*D/4/E));
}
node* lca(node *u,node *v){
	for(int j=logN-1;j>=0;j--) if(u->pa[j]->depth>=v->depth) u=u->pa[j];
	for(int j=logN-1;j>=0;j--) if(v->pa[j]->depth>=u->depth) v=v->pa[j];
	if(u==v) return u;
	for(int j=logN-1;j>=0;j--) if(u->pa[j]!=v->pa[j]) u=u->pa[j],v=v->pa[j];
	return u->pa[0];
}
void node::getcir(){
	depth=pa[0]->depth+1;
	for(edge *e=son;e;e=e->next) if(e->ed!=pa[0]){
		if(e->ed->depth){
			if(e->ed->depth<depth){
				for(node *v=this;v!=e->ed;v=v->pa[0]) v->oncir=1,seq[++cnt]=v;
				e->ed->oncir=1;
				seq[++cnt]=e->ed;
			}
			continue;
		}
		e->ed->pa[0]=this;
		e->ed->getcir();
	}
}
void node::dfs(){
	for(int j=1;j<logN;j++) pa[j]=pa[j-1]->pa[j-1];
	renew();
	num=now;
	for(edge *e=son;e;e=e->next) if(e->ed!=pa[0]&&!e->ed->oncir){
		e->ed->pa[0]=this;
		e->ed->dfs();
	}
}
int main(){
	scanf("%d%d",&n,&m);
	for(int i=1;i<=n;i++) V[i].read();
	for(int i=0;i<m;i++){
		int u,v; scanf("%d%d",&u,&v);
		*newE=(edge){V+v,V[u].son},V[u].son=newE++;
		*newE=(edge){V+u,V[v].son},V[v].son=newE++;
	}
	if(m==n)
		V[1].pa[0]=V,V[1].getcir();
	else
		seq[++cnt]=V+1;
	for(int j=0;j<logN;j++) V->pa[j]=V;
	for(int i=1;i<=cnt;i++){
		now=i;
		for(int j=0;j<logN;j++) seq[i]->pa[j]=V;
		seq[i]->dfs();
		tA[i]=seq[i]->A+tA[i-1];
		tB[i]=seq[i]->B+tB[i-1];
		tC[i]=seq[i]->C+tC[i-1];
		tD[i]=seq[i]->D+tD[i-1];
		tE[i]=seq[i]->E+tE[i-1];
		tF[i]=seq[i]->F+tF[i-1];
	}
	scanf("%d",&q);
	while(q--){
		int s,t; scanf("%d%d",&s,&t);
		node *u=V+s,*v=V+t;
		db ans;
		if(u->num==v->num){
			node *w=lca(u,v);
			ans=calc(
				u->sA+v->sA-w->sA*2+w->A,
				u->sB+v->sB-w->sB*2+w->B,
				u->sC+v->sC-w->sC*2+w->C,
				u->sD+v->sD-w->sD*2+w->D,
				u->sE+v->sE-w->sE*2+w->E,
				u->sF+v->sF-w->sF*2+w->F);
		}
		else{
			if(u->num>v->num) swap(u,v);
			ans=min(
				calc(
				u->sA+v->sA-tA[u->num]+tA[v->num-1],
				u->sB+v->sB-tB[u->num]+tB[v->num-1],
				u->sC+v->sC-tC[u->num]+tC[v->num-1],
				u->sD+v->sD-tD[u->num]+tD[v->num-1],
				u->sE+v->sE-tE[u->num]+tE[v->num-1],
				u->sF+v->sF-tF[u->num]+tF[v->num-1]),
				calc(
				u->sA+v->sA+tA[u->num-1]-tA[v->num]+tA[cnt],
				u->sB+v->sB+tB[u->num-1]-tB[v->num]+tB[cnt],
				u->sC+v->sC+tC[u->num-1]-tC[v->num]+tC[cnt],
				u->sD+v->sD+tD[u->num-1]-tD[v->num]+tD[cnt],
				u->sE+v->sE+tE[u->num-1]-tE[v->num]+tE[cnt],
				u->sF+v->sF+tF[u->num-1]-tF[v->num]+tF[cnt])
			);
		}
		printf("%.2lf\n",fix(ans));
	}
}
