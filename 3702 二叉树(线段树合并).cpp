#include <cstdio>
#include <algorithm>
using namespace std;
typedef long long ll;
int n,x;
ll s,m,tot;

struct tree{
	tree *l,*r;
	int cnt;
	tree():l(NULL),r(NULL),cnt(0){
	}
};
tree *build(int beg,int end){
	tree *ret=new tree;
	ret->cnt=1;
	if(end-beg==1) return ret;
	int mid=beg+end>>1;
	if(x<=mid)
		ret->l=build(beg,mid);
	else
		ret->r=build(mid,end);
	return ret;
}
tree *merge(tree *a,tree *b){
	if(!b){
		if(a) m+=a->cnt;
		return a;
	}
	if(!a){
		s+=m*b->cnt;
		return b;
	}
	a->l=merge(a->l,b->l);
	a->r=merge(a->r,b->r);
	a->cnt+=b->cnt;
	return a;
}

struct data{
	tree *t;
	ll inv;
	data(){
		scanf("%d",&x);
		if(x){
			t=build(0,n);
			inv=0;
			return;
		}
		data l,r;
		m=s=0;
		tot=(ll)l.t->cnt*r.t->cnt;
		t=merge(l.t,r.t);
		inv=l.inv+r.inv+min(s,tot-s);
	}
};

int main(){
	scanf("%d\n",&n);
	printf("%lld\n",data().inv);
}
