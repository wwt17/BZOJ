#include <cstdio>
#include <algorithm>
inline void read(unsigned &a){
	char c;for (c=getchar();c<'0'||'9'<c;c=getchar()); a=c-'0';
	for (c=getchar();'0'<=c&&c<='9';c=getchar()) a=a*10+(c-'0');
}
#define read2(a,b) (read(a),read(b))
inline void write(unsigned a){
	if (a>9) write(a/10); putchar('0'+a%10);
}
#define writeln(a) (write(a),putchar('\n'))

struct node *null;inline void nullinit();
inline void print();
struct node{
	node *l,*r,*pa; bool rev;
	void clear(){ l=r=pa=null; rev=0; }
	inline bool istop(){ return this==null||pa==null||pa->l!=this&&pa->r!=this; }
	inline void reverse(){ rev^=1;std::swap(l,r); }
	void down(){ if(rev) rev=0,l->reverse(),r->reverse(); }
	void correct(){ if(!istop()) pa->correct(); down(); }
	node* top(){
		splay();
		node* x=this;
		while(x->l!=null) x=x->l,x->down();
		return x;
	}
	node* access(){
		node *x=this,*y=null;
		while(x!=null)
			x->splay(),x->r=y,y=x,x=x->pa;
		return y;
	}
	#define x this
	inline void zig(){
		node *y=x->pa,*z=y->pa;
		x->pa=z; z->l==y?z->l=x:z->r==y?z->r=x:0;
		x->r->pa=y; y->l=x->r;
		x->r=y; y->pa=x;
	}
	inline void zag(){
		node *y=x->pa,*z=y->pa;
		x->pa=z; z->l==y?z->l=x:z->r==y?z->r=x:0;
		x->l->pa=y; y->r=x->l;
		x->l=y; y->pa=x;
	}
	void splay(){
		correct();
		node *y,*z;
		while(!istop()){
			y=x->pa;z=y->pa;
			if(y->istop()) y->l==x?zig():zag(); else
				if(z->l==y) y->l==x?(y->zig(),x->zig()):(x->zag(),x->zig());
				       else y->r==x?(y->zag(),x->zag()):(x->zig(),x->zag());
		}
	}
	#undef x
} V[10001];
bool Connected(node* x,node* y){
	return x->access()->top()==y->access()->top();
}
void Link(node* x,node* y){
	x->access(); x->splay(); x->reverse(); x->pa=y;
}
void Cut(node* x,node* y){
	x->access(); y->splay(); if(y->pa==x){ y->pa=null;return; }
	y->access(); x->splay(); x->pa=null;
}
inline void nullinit(){ null->l=null->r=null->pa=null; }
	
int main(){
	null=V;nullinit();
	unsigned n,m,u,v; read2(n,m); char c;
	for(int i=1;i<=n;++i) V[i].clear();
	while(m--) switch(c=getchar(),read2(u,v),c){
		case 'C':Link(V+u,V+v);break;
		case 'D':Cut(V+u,V+v);break;
		default :puts(Connected(V+u,V+v)?"Yes":"No");
	}
}
