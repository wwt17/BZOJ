#include <cstdio>
#include <cstring>
#include <algorithm>
#define Sizeb 21
int N;
struct ST *null;
struct ST{
	int size,sum;
	ST *l,*r;
	ST(){}
	ST(ST* _l,ST* _r,int _size,int _sum):
		l(_l),r(_r),size(_size),sum(_sum){}
	ST* insert(int,int);
	void init(){ ST(this,this,0,0); }
};
struct node *Base;
struct edge{
	node* ed;
	edge* next;
	edge(node* _ed,edge* _next):ed(_ed),next(_next){}
};
struct node{
	edge* son;
	int w;
	ST *st;
	int depth;
	node* up[Sizeb];
	node():son(NULL),st(NULL){memset(up,0,sizeof(up));}
	void addedge(node* ed){
		edge* e=new edge(ed,son);
		son=e;
	}
	void correct(node* fa,int Depth);
	void Correct(int Size);
};

ST* ST::insert(int w,int Size){
	if (Size<=1) return new ST(l,r,Size,sum+1);
	return w<=Size>>1
		?new ST(l->insert(w,Size>>1),r,Size,sum+1)
		:new ST(l,r->insert(w-(Size>>1),Size-(Size>>1)),Size,sum+1);
}
void node::correct(node* fa,int Depth){
	depth=Depth;
	st=fa->st->insert(w,N);
	up[0]=fa;
	for (int b=1;b<Sizeb&&up[b-1];++b) up[b]=up[b-1]->up[b-1];
	for (edge* e=son;e;e=e->next) if (e->ed!=fa) e->ed->correct(this,Depth+1);
}
void node::Correct(int Size){
	st=null=new ST; null->l=null->r=null; null->size=null->sum=0;
	memset(up,0,sizeof(up));
	for (edge* e=son;e;e=e->next) e->ed->correct(this,1);
}

node* LCA(node* u,node* v){
	node *x=u,*y=v; int i;
	for (i=Sizeb-1;i>=0;--i){
		if (x->depth-(1<<i)>=y->depth) x=x->up[i];
		if (y->depth-(1<<i)>=x->depth) y=y->up[i];
	}
	if (x==y) return x;
	for (i=Sizeb-1;x&&y&&i>=0;--i) if (x->up[i]!=y->up[i])
		x=x->up[i],y=y->up[i];
	return x->up[0];
}
int query(node* u,node* v,int k){
	node* w=LCA(u,v);
	ST *ust=u->st,*vst=v->st,*wst=w->st,*wwst=w->up[0]->st;
	int Size=N,mid,ans=0;
	while (Size>1)
		if (k<=(mid=(ust->l->sum-wwst->l->sum)+(vst->l->sum-wst->l->sum)))
			   ust=ust->l,vst=vst->l,wst=wst->l,wwst=wwst->l,Size>>=1;
		else ust=ust->r,vst=vst->r,wst=wst->r,wwst=wwst->r,ans+=Size>>1,Size-=Size>>1,k-=mid;
	return ans+1;
}

inline bool cmp(const int *a,const int *b){ return *a<*b; }
int main(){
	int M;
	scanf("%d%d",&N,&M);
	node V[N+1]; Base=V;
	int i,*p[N+1],w[N+1];
	for (i=1;i<=N;++i) scanf("%d",p[i]=&V[i].w);
	std::sort(p+1,p+1+N,cmp);
	for (i=1;i<=N;++i) w[i]=*p[i],*p[i]=i;
	int u,v,k,ans=0;
	for (i=1;i<N;++i)
		scanf("%d%d",&u,&v),V[u].addedge(V+v),V[v].addedge(V+u);
	V[0].addedge(V+1);
	V[0].Correct(N);
	while (M--)
		scanf("%d%d%d",&u,&v,&k),
		printf("%d",ans=w[query(V+(u^ans),V+v,k)]),
		M?putchar('\n'):0;
}
