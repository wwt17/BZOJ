#include <cstdio>
const int N=100001,Q=N+300001;
int n,m,q,X,ord[N];
struct tree{
	tree *l,*r; int cnt;
	tree():l(NULL),r(NULL),cnt(0){
	}
} *t[N];
tree *insert(tree *cur,int begin,int end){
	tree *ret=cur?new tree(*cur):new tree;
	ret->cnt++;
	if(end-begin==1) return ret;
	int mid=(begin+end)/2;
	if(X<mid) ret->l=insert(ret->l,begin,mid);
	else ret->r=insert(ret->r,mid,end);
	return ret;
}
struct node{
	int w,l,r; node *belong,*son,*next;
	int query(int k){
		tree *a=t[l],*b=t[r];
		if(k>r-l) return 0;
		int begin=1,end=n+1;
		while(end-begin>1){
			int mid=(begin+end)/2,tmp=(b&&b->l?b->l->cnt:0)-(a&&a->l?a->l->cnt:0);
			if(k<=tmp){
				end=mid;
				if(a) a=a->l;
				if(b) b=b->l;
			}
			else{
				k-=tmp;
				begin=mid;
				if(a) a=a->r;
				if(b) b=b->r;
			}
		}
		return begin;
	}
	void init(){
		scanf("%d",&w);
		belong=this;
	}
	void build(){
		static int len=0;
		l=len;
		for(node *v=son;v;v=v->next)
			v->build();
		r=++len;
		X=w;
		t[r]=insert(t[r-1],1,n+1);
	}
	node *get(){
		if(belong==this) return this;
		return belong=belong->get();
	}
} V[N];
void merge(node *u,node *v){
	node *x=u->get(),*y=v->get();
	if(x!=y){
		x->belong=y;
		x->next=y->son;
		y->son=x;
	}
}
struct query{
	bool type; int x,y;
	void read(){
		loop:
		switch(getchar()){
			case 'B': type=1; break;
			case 'Q': type=0; break;
			default: goto loop;
		}
		scanf("%d%d",&x,&y);
		if(type)
			merge(V+x,V+y);
	}
	void work(){
		if(type){
			node *u=V[x].get(),*v=V[y].get();
			if(u!=v){
				u->belong=v;
				v->l=u->l;
			}
		}
		else{
			printf("%d\n",ord[V[x].get()->query(y)]);
		}
	}
} s[Q];
int main(){
	scanf("%d%d",&n,&m);
	ord[0]=-1;
	V->belong=V;
	for(int i=1;i<=n;i++) V[i].init(),ord[V[i].w]=i;
	for(int i=0;i<m;i++){
		s[i].type=1;
		scanf("%d%d",&s[i].x,&s[i].y);
		merge(V+s[i].x,V+s[i].y);
	}
	scanf("%d",&q);
	for(int i=m;i<m+q;i++)
		s[i].read();
	for(int i=1;i<=n;i++) if(V[i].belong==V+i)
		V[i].build();
	for(int i=1;i<=n;i++) V[i].belong=V+i,V[i].l=V[i].r-1;
	for(int i=0;i<m+q;i++)
		s[i].work();
}
