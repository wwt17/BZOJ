#include <cstdio>
#include <algorithm>
using namespace std;
const int N=50005,T=N*4;
int n,m,base;
struct tree{
	tree *l,*r; int add; long long sum;
	tree():l(NULL),r(NULL),add(0),sum(0){
	}
} *t[T];
int L,R;
void insert(tree* &x,int begin,int end){
	if(!x) x=new tree;
	if(L<=begin&&end-1<=R){
		x->add++;
		x->sum+=end-begin;
		return;
	}
	int mid=(begin+end)/2;
	if(L<mid)
		insert(x->l,begin,mid);
	if(mid<=R)
		insert(x->r,mid,end);
	x->sum+=min(R,end-1)-max(L,begin)+1;
}
long long query(tree* &x,int begin,int end){
	if(!x) return 0;
	if(L<=begin&&end-1<=R)
		return x->sum;
	int mid=(begin+end)/2;
	return
		 (L<mid?query(x->l,begin,mid):0)
		+(mid<=R?query(x->r,mid,end):0)
		+(long long)(min(R,end-1)-max(L,begin)+1)*x->add;
}
void insert(int c){
	int x=1,l=1,r=n+1;
	while(true){
		insert(t[x],1,n+1);
		if(r-l==1) return;
		int mid=(l+r)/2;
		if(c<mid){
			x=x<<1;
			r=mid;
		}
		else{
			x=x<<1|1;
			l=mid;
		}
	}
}
int query(long long k){
	int x=1,l=1,r=n+1;
	while(r-l>1){
		int mid=(l+r)/2;
		long long sum=query(t[x<<1|1],1,n+1);
		if(k>sum){
			k-=sum;
			x=x<<1;
			r=mid;
		}
		else{
			x=x<<1|1;
			l=mid;
		}
	}
	return l;
}
int main(){
	scanf("%d%d",&n,&m);
	while(m--){
		int type,c; scanf("%d%d%d%d",&type,&L,&R,&c);
		if(type==1)
			insert(c);
		else
			printf("%d\n",query(c));
	}
}
