#include <cstdio>
#include <algorithm>
using namespace std;

const int N=(int)3e5+5,logN=20;

int n,top,a[N],s[N];

struct tree{
	tree *l,*r;
	int sum;
} mem[N*logN*2],*newtree=mem;

tree *root[N];

tree* insert(tree *last,int loc,int beg=0,int end=n){
	tree *cur=newtree++;
	if(last) *cur=*last;
	if(end-beg>1){
		int mid=beg+end>>1;
		if(loc<=mid)
			cur->l=insert(cur->l,loc,beg,mid);
		else
			cur->r=insert(cur->r,loc,mid,end);
	}
	cur->sum++;
	return cur;
}

int query(tree *cur,int L,int R,int beg=0,int end=n){
	if(!cur||end<=L||beg>=R) return 0;
	if(beg>=L&&end<=R) return cur->sum;
	int mid=beg+end>>1;
	return query(cur->l,L,R,beg,mid)+query(cur->r,L,R,mid,end);
}

int main(){
	int m,type; scanf("%d%d%d",&n,&m,&type);
	for(int i=1;i<=n;i++) scanf("%d",&a[i]);
	for(int i=1;i<=n;i++){
		root[i]=root[i-1];
		for(;top>=1&&a[s[top]]<a[i];top--){
			root[i]=insert(root[i],s[top]);
		}
		if(top>=1){
			root[i]=insert(root[i],s[top]);
		}
		if(a[s[top]]==a[i]) top--;
		s[++top]=i;
	}
	int ans=0;
	while(m--){
		int l,r; scanf("%d%d",&l,&r);
		if(type){
			l=(l+ans-1)%n+1,r=(r+ans-1)%n+1;
			if(l>r) swap(l,r);
		}
		l--;
		printf("%d\n",ans=query(root[r],l,r)-query(root[l],l,r));
	}
}
