#include <cstdio>
#include <vector>
using namespace std;
typedef long long ll;

const int N=100005;

int n,len;

struct node *null;
struct node{
	node *l,*r,*pa;
	int w,size;
	ll a,delta,sum;
	void init(){
		l=r=pa=null;
	}
	void update(){
		size=l->size+r->size+w;
		sum=l->sum+r->sum+a;
	}
	void add(ll d){
		delta+=d;
		sum+=size*d;
		a+=d*w;
	}
	void down(){
		l->add(delta);
		r->add(delta);
		delta=0;
	}
	void correct(){
		if(this==null) return;
		pa->correct();
		down();
	}
	void print(int tab);
} nullmem,*root,V[N][2],*seq[N*2];

void node::print(int tab=0){
	if(this==null) return;
	l->print(tab+1);
	for(int i=0;i<tab;i++) printf("  ");
	printf(" V[%d][%d].a=%I64d,size=%d,sum=%I64d",(this-V[0])/2,(this-V[0])%2,a,size,sum);
	if(delta) printf(",delta=%I64d",delta);
	puts("");
	r->print(tab+1);
}

void zig(node *x){
	node *y=x->pa,*z=y->pa;
	if(y==z->l) z->l=x; else z->r=x;
	x->pa=z;
	y->l=x->r;
	x->r->pa=y;
	x->r=y;
	y->pa=x;
	y->update();
}

void zag(node *x){
	node *y=x->pa,*z=y->pa;
	if(y==z->l) z->l=x; else z->r=x;
	x->pa=z;
	y->r=x->l;
	x->l->pa=y;
	x->l=y;
	y->pa=x;
	y->update();
}

void splay(node *x,node *&goal=root){
	node *top=goal->pa;
	x->correct();
	while(x->pa!=top){
		node *y=x->pa,*z=y->pa;
		if(z==top)
			if(x==y->l) zig(x); else zag(x);
		else
			if(y==z->l)
				if(x==y->l){
					zig(y);
					zig(x);
				}
				else{
					zag(x);
					zig(x);
				}
			else
				if(x==y->r){
					zag(y);
					zag(x);
				}
				else{
					zig(x);
					zag(x);
				}
	}
	x->update();
	goal=x;
}

node *pred(node *x){
	if(x->l==null){
		for(;x->pa->l==x;x=x->pa);
		x=x->pa;
	}
	else{
		x=x->l;
		for(;x->r!=null;x=x->r);
	}
	return x;
}
node *succ(node *x){
	if(x->r==null){
		for(;x->pa->r==x;x=x->pa);
		x=x->pa;
	}
	else{
		x=x->r;
		for(;x->l!=null;x=x->l);
	}
	return x;
}

node *build(node* *beg,node* *end){
	if(beg==end) return null;
	node* *mid=beg+(end-beg>>1);
	(*mid)->l=build(beg,mid);
	(*mid)->r=build(mid+1,end);
	(*mid)->l->pa=*mid;
	(*mid)->r->pa=*mid;
	(*mid)->update();
	return *mid;
}

vector<int> son[N];
int w[N];

void dfs(int u){
	V[u][0].init(); V[u][0].w= 1; V[u][0].a= w[u];
	V[u][1].init(); V[u][1].w=-1; V[u][1].a=-w[u];
	seq[len++]=V[u];
	for(vector<int>::iterator e=son[u].begin();e!=son[u].end();e++)
		dfs(*e);
	seq[len++]=V[u]+1;
}

int main(){
	null=&nullmem;
	null->init();
	V[0][0].init();
	V[0][1].init();
	scanf("%d",&n);
	for(int i=2;i<=n;i++){
		int fa; scanf("%d",&fa);
		son[fa].push_back(i);
	}
	for(int i=1;i<=n;i++) scanf("%d",&w[i]);
	seq[len++]=V[0];
	dfs(1);
	seq[len++]=V[0]+1;
	root=build(seq,seq+len);
	int m; scanf("%d",&m);
	while(m--){
		char c=getchar();
		if(c=='Q'){
			int u; scanf("%d",&u);
			splay(succ(V[u]));
			printf("%lld\n",root->l->sum);
		}
		else
		if(c=='C'){
			int u,v; scanf("%d%d",&u,&v);
			splay(pred(V[u]));
			splay(succ(V[u]+1),root->r);
			root->update();
			node *tmp=root->r->l;
			tmp->pa=null;
			root->r->l=null;
			root->r->update();
			root->update();
			splay(V[v]);
			splay(succ(V[v]),root->r);
			tmp->pa=root->r;
			root->r->l=tmp;
			root->r->update();
			root->update();
		}
		else
		if(c=='F'){
			int u,c; scanf("%d%d",&u,&c);
			splay(pred(V[u]));
			splay(succ(V[u]+1),root->r);
			root->update();
			root->r->l->add(c);
			root->r->update();
			root->update();
		}
		else
			m++;
	}
}
