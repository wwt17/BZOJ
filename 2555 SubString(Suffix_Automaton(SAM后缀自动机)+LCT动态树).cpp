#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;

const int N=600006;

struct node *null;
struct node{
	node *fa,*go[26];
	int val;
	node *l,*r,*pa;
	int a,delta;
	void init(){
		l=r=pa=null;
	}
	bool istop(){
		return pa==null||pa->l!=this&&pa->r!=this;
	}
	void update(){
	}
	void add(int d){
		if(this==null) return;
		a+=d;
		delta+=d;
	}
	void down(){
		if(delta){
			l->add(delta);
			r->add(delta);
			delta=0;
		}
	}
	void correct(){
		if(!istop()) pa->correct(); down();
	}
} memnull[1],root[N*2],*newnode=root+1,*last=root;

void zig(node *x){
	node *y=x->pa,*z=y->pa;
	if(y==z->l) z->l=x; else
	if(y==z->r) z->r=x;
	x->pa=z;
	y->l=x->r;
	x->r->pa=y;
	x->r=y;
	y->pa=x;
	y->update();
}
void zag(node *x){
	node *y=x->pa,*z=y->pa;
	if(y==z->l) z->l=x; else
	if(y==z->r) z->r=x;
	x->pa=z;
	y->r=x->l;
	x->l->pa=y;
	x->l=y;
	y->pa=x;
	y->update();
}
void splay(node *x){
	x->correct();
	while(!x->istop()){
		node *y=x->pa;
		if(y->istop())
			if(x==y->l) zig(x); else zag(x);
		else
			if(y==y->pa->l)
				if(x==y->l)
					zig(y),zig(x);
				else
					zag(x),zig(x);
			else
				if(x==y->r)
					zag(y),zag(x);
				else
					zig(x),zag(x);
	}
	x->update();
}
node *access(node *x){
	node *y=null;
	while(x!=null){
		splay(x);
		x->r=y;
		x->update();
		y=x;
		x=x->pa;
	}
	return y;
}
void changefa(node *u,node *v){
	if(u->fa) access(u->fa);
	splay(u);
	u->fa=u->pa=v;
}
void extend(int c){
	node *p=last,*np=newnode++;
	np->init();
	np->val=p->val+1;
	for(;p&&p->go[c]==NULL;p=p->fa)
		p->go[c]=np;
	if(!p)
		changefa(np,root);
	else{
		node *q=p->go[c];
		if(q->val==p->val+1)
			changefa(np,q);
		else{
			splay(q);
			node *nq=newnode++;
			nq->init();
			for(int x=0;x<26;x++) nq->go[x]=q->go[x];
			nq->a=q->a;
			changefa(nq,q->fa);
			nq->val=p->val+1;
			changefa(np,nq);
			changefa(q,nq);
			for(;p&&p->go[c]==q;p=p->fa)
				p->go[c]=nq;
		}
	}
	access(np)->add(1);
	last=np;
}

char s[3000005];

int mask;
void decode(){
	int w=mask;
	int len=strlen(s);
	for(int j=0;j<len;j++){
		w=(w*131+j)%len;
		swap(s[j],s[w]);
	}
}

int main(){
	null=memnull;
	null->init();
	root->init();
	int q; scanf("%d",&q);
	scanf("%s",s);
	for(char *i=s;*i;i++) extend(*i-'A');
	while(q--){
		static char type[10]; scanf("%s%s",type,s);
		decode();
		if(type[0]=='A'){
			for(char *i=s;*i;i++) extend(*i-'A');
		}
		else{
			int res=0;
			node *p=root;
			for(char *i=s;*i&&p;i++) p=p->go[*i-'A'];
			if(!p)
				puts("0");
			else{
				splay(p);
				printf("%d\n",res=p->a);
			}
			mask^=res;
		}
	}
}
