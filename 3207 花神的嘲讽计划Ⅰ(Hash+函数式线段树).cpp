#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;
const int N=100001,M=100001,K=20,P=5000011;

int n,m,k,R,a[N],b[N],c[N];
int *h[P];
struct tree{
	tree *l,*r; int sum;
	tree():l(NULL),r(NULL),sum(0){
	}
} *f[N];
int num;
tree* insert(tree* root,int begin,int end){
	tree* ret=root?new tree(*root):new tree;
	ret->sum++;
	if(end-begin>1){
		int mid=(begin+end)/2;
		if(num<mid)
			ret->l=insert(ret->l,begin,mid);
		else
			ret->r=insert(ret->r,mid,end);
	}
	return ret;
}
bool found(tree* A,tree* B,int begin,int end){
	int suma=A?A->sum:0,sumb=B?B->sum:0;
	if(sumb-suma==0) return false;
	if(end-begin>1){
		int mid=(begin+end)/2;
		if(num<mid)
			return found(A?A->l:NULL,B?B->l:NULL,begin,mid);
		else
			return found(A?A->r:NULL,B?B->r:NULL,mid,end);
	}
	return true;
}

int main(){
	long long u,high=1; int v;
	#define mov(x) u=(u*n+(x)-1)%P
	scanf("%d%d%d",&n,&m,&k);
	for(int j=0;j<k-1;j++) high=high*n%P;
	for(int i=1;i<=n;i++) scanf("%d",a+i);
	u=0;
	for(int i=1;i<k;i++) mov(a[i]);
	for(int i=k,j=1;i<=n;i++,j++){
		mov(a[i]);
		for(v=u;h[v]&&memcmp(h[v],a+j,k*sizeof(int));++v==P?v=0:0);
		if(!h[v]) h[v]=a+j;
		c[j-1]=b[j]=v;
		u=((u-high*(a[j]-1))%P+P)%P;
	}
	sort(c,c+n);
	R=unique(c,c+n)-c;
	for(int i=1;i<=n-k+1;i++){
		num=lower_bound(c,c+n,b[i])-c;
		f[i]=insert(f[i-1],0,R);
	}
	while(m--){
		static int l,r,tmp[K];
		scanf("%d%d",&l,&r);
		u=0;
		for(int j=0;j<k;j++){
			scanf("%d",tmp+j);
			mov(tmp[j]);
		}
		for(v=u;h[v]&&memcmp(h[v],tmp,k*sizeof(int));++v==P?v=0:0);
		if(!h[v]){ puts("Yes"); continue; }
		num=lower_bound(c,c+n,v)-c;
		puts(found(f[l-1],f[r-k+1],0,R)?"No":"Yes");
	}
}
