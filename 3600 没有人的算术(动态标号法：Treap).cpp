#include <cstdio>
#include <cstdlib>
#include <algorithm>
using namespace std;
typedef unsigned long long ll;
const ll inf=1ULL<<63;
const int N=100005,M=500005;

int n,m;

struct node{
	int key;
	node *l,*r;
	node *a,*b;
	ll val;
} V[M],*newnode=V,*root;

void rebuild(node *cur,ll beg,ll end){
	if(!cur) return;
	cur->val=beg+end>>1;
	rebuild(cur->l,beg,cur->val);
	rebuild(cur->r,cur->val,end);
}

node* insert(node *&cur,ll beg,ll end,node *x){
	if(!cur){
		cur=x;
		cur->key=rand();
		cur->val=beg+end>>1;
		return cur;
	}
	if(cur!=V&&(x->a->val<cur->a->val||x->a==cur->a&&x->b->val<cur->b->val)){
		node *ret=insert(cur->l,beg,cur->val,x);
		if(cur->l->key>cur->key){
			node *x=cur->l,*y=cur;
			y->l=x->r;
			x->r=y;
			rebuild(cur=x,beg,end);
		}
		return ret;
	}
	else
	if(cur==V||(x->a->val>cur->a->val||x->a==cur->a&&x->b->val>cur->b->val)){
		node *ret=insert(cur->r,cur->val,end,x);
		if(cur->r->key>cur->key){
			node *x=cur->r,*y=cur;
			y->r=x->l;
			x->l=y;
			rebuild(cur=x,beg,end);
		}
		return ret;
	}
	else
		return cur;
}

node *a[N];
int t[N*4];

inline int update(int l,int r){
	return a[l]->val>=a[r]->val?l:r;
}
void build(int cur,int beg,int end){
	if(end-beg==1){
		t[cur]=end;
		return;
	}
	int mid=beg+end>>1;
	build(cur<<1,beg,mid);
	build(cur<<1|1,mid,end);
	t[cur]=update(t[cur<<1],t[cur<<1|1]);
}
void modify(int cur,int beg,int end,int loc){
	if(end-beg==1) return;
	int mid=beg+end>>1;
	if(loc<=mid)
		modify(cur<<1,beg,mid,loc);
	else
		modify(cur<<1|1,mid,end,loc);
	t[cur]=update(t[cur<<1],t[cur<<1|1]);
}
int query(int cur,int beg,int end,int L,int R){
	if(beg>=L&&end<=R) return t[cur];
	int mid=beg+end>>1;
	if(R<=mid) return query(cur<<1,beg,mid,L,R);
	if(L>=mid) return query(cur<<1|1,mid,end,L,R);
	return update(query(cur<<1,beg,mid,L,R),query(cur<<1|1,mid,end,L,R));
}

int main(){
	scanf("%d%d",&n,&m);
	node *zero=newnode++;
	insert(root,0,inf,zero);
	for(int i=1;i<=n;i++) a[i]=root;
	build(1,0,n);
	while(m--){
		char c=getchar();
		if(c=='C'){
			int l,r,k; scanf("%d%d%d",&l,&r,&k);
			newnode->a=a[l];
			newnode->b=a[r];
			a[k]=newnode++;
			a[k]=insert(root,0,inf,a[k]);
			modify(1,0,n,k);
		}
		else
		if(c=='Q'){
			int l,r; scanf("%d%d",&l,&r); l--;
			printf("%d\n",query(1,0,n,l,r));
		}
		else
			m++;
	}
}
