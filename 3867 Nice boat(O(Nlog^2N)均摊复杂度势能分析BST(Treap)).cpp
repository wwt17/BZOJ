#include <cstdio>
#include <cstdlib>
#include <algorithm>
using namespace std;

const int N=100005;
int n;

int gcd(const int a,const int b){
	return b?gcd(b,a%b):a;
}

struct Treap{
	Treap *l,*r;
	int key;
	int val,ma;
	int len,size;
	void update(){
		size=len;
		ma=val;
		if(l){
			size+=l->size;
			ma=max(ma,l->ma);
		}
		if(r){
			size+=r->size;
			ma=max(ma,r->ma);
		}
	}
} mem[N],*unused[N],**top=unused;

#define SZ(x) ((x)?(x)->size:0)

void initmem(){
	for(int i=N-1;i>=0;i--) *top++=mem+i;
}

void delTreap(Treap* &cur){
	if(!cur) return;
	delTreap(cur->l);
	delTreap(cur->r);
	*top++=cur;
	cur=NULL;
}

Treap* newTreap(int val,int len=1){
	Treap *cur=*--top;
	cur->key=rand();
	cur->l=cur->r=NULL;
	cur->val=val;
	cur->len=len;
	cur->update();
	return cur;
}

Treap* merge(Treap* u,Treap* v){
	if(!u) return v;
	if(!v) return u;
	if(u->key>v->key){
		u->r=merge(u->r,v);
		u->update();
		return u;
	}
	else{
		v->l=merge(u,v->l);
		v->update();
		return v;
	}
}

typedef pair<Treap*,Treap*> ptt;

ptt split(Treap* cur,int k){
	if(!cur) return ptt(NULL,NULL);
	if(k<=SZ(cur->l)){
		ptt tmp=split(cur->l,k);
		cur->l=tmp.second;
		cur->update();
		return ptt(tmp.first,cur);
	}
	else
	if(k>=SZ(cur->l)+cur->len){
		ptt tmp=split(cur->r,k-(SZ(cur->l)+cur->len));
		cur->r=tmp.first;
		cur->update();
		return ptt(cur,tmp.second);
	}
	else{
		ptt tmp(newTreap(cur->val,k-SZ(cur->l)),newTreap(cur->val,SZ(cur->l)+cur->len-k));
		tmp.first->l=cur->l;
		cur->l=NULL;
		tmp.first->update();
		tmp.second->r=cur->r;
		cur->r=NULL;
		tmp.second->update();
		delTreap(cur);
		return tmp;
	}
}

void modify(Treap* cur,int x){
	if(!cur) return;
	if(cur->l&&cur->ma==cur->l->ma)
		modify(cur->l,x);
	else
	if(cur->r&&cur->ma==cur->r->ma)
		modify(cur->r,x);
	else
		cur->val=gcd(cur->val,x);
	cur->update();
}

void print(Treap* cur){
	if(!cur) return;
	print(cur->l);
	for(int i=0;i<cur->len;i++) printf("%d ",cur->val);
	print(cur->r);
}

Treap *root,*left,*right;

void Main(){
	scanf("%d",&n);
	for(int i=1;i<=n;i++){
		int x; scanf("%d",&x);
		root=merge(root,newTreap(x));
	}
	int q; scanf("%d",&q);
	while(q--){
		int type,l,r,x; scanf("%d%d%d%d",&type,&l,&r,&x); l--;
		ptt tmp=split(root,r);
		root=tmp.first;
		right=tmp.second;
		tmp=split(root,l);
		left=tmp.first;
		root=tmp.second;
		if(type==1){
			delTreap(root);
			root=newTreap(x,r-l);
		}
		else{
			if(x){
				while(root&&root->ma>x){
					modify(root,x);
				}
			}
		}
		root=merge(merge(left,root),right);
	}
	print(root),puts("");
	delTreap(root);
}

int main(){
	initmem();
	int T; scanf("%d",&T);
	while(T--) Main();
}
