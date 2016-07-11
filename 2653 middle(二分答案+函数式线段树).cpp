#include <cstdio>
#include <algorithm>
using namespace std;
const int N=20005,logN=15;
int n,L,R,a[N],ord[N];
struct data{
	int ls,rs,s;
};
data operator + (const data &l,const data &r){
	return (data){
		max(l.ls,l.s+r.ls),
		max(r.rs,r.s+l.rs),
		l.s+r.s
	};
}
bool cmp(const int i,const int j){
	return a[i]<a[j];
}
struct tree{
	tree *l,*r;
	data u;
} mem[2*N*logN],*newtree=mem;
tree *t[N];
tree *build(int beg,int end){
	tree *cur=newtree++;
	if(end-beg==1){
		cur->u=(data){1,1,1};
		return cur;
	}
	int mid=beg+end>>1;
	cur->l=build(beg,mid);
	cur->r=build(mid,end);
	cur->u=cur->l->u+cur->r->u;
	return cur;
}
tree *insert(tree *tmp,int beg,int end){
	tree *cur=newtree++;
	*cur=*tmp;
	if(end-beg==1){
		cur->u=(data){0,0,-1};
		return cur;
	}
	int mid=beg+end>>1;
	if(L<mid)
		cur->l=insert(cur->l,beg,mid);
	else
		cur->r=insert(cur->r,mid,end);
	cur->u=cur->l->u+cur->r->u;
	return cur;
}
data res;
void query(tree *cur,int beg,int end){
	if(R<=beg||L>=end) return;
	if(L<=beg&&R>=end){
		res=res+cur->u;
		return;
	}
	int mid=beg+end>>1;
	query(cur->l,beg,mid);
	query(cur->r,mid,end);
}
int main(){
	scanf("%d",&n);
	for(int i=0;i<n;i++) scanf("%d",&a[i]),ord[i]=i;
	sort(ord,ord+n,cmp);
	t[0]=build(0,n);
	for(int i=1;i<=n;i++)
		L=ord[i-1],t[i]=insert(t[i-1],0,n);
	int m; scanf("%d",&m);
	int ans=0;
	while(m--){
		static int q[4];
		for(int i=0;i<4;i++) scanf("%d",&q[i]),(q[i]+=ans)%=n;
		sort(q,q+4);
		q[2]++;
		q[3]++;
		int l=0,r=n;
		while(r-l>1){
			int mid=l+r>>1,now=0;
			L=q[0],R=q[1],res=(data){0,0,0},query(t[mid],0,n);
			now+=res.rs;
			L=q[1],R=q[2],res=(data){0,0,0},query(t[mid],0,n);
			now+=res.s;
			L=q[2],R=q[3],res=(data){0,0,0},query(t[mid],0,n);
			now+=res.ls;
			if(now>=0)
				l=mid;
			else
				r=mid;
		}
		printf("%d\n",ans=a[ord[l]]);
	}
}
