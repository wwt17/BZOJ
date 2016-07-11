#include <cstdio>
#include <algorithm>
using namespace std;

const int N=200005,M=N;

struct query{
	int l,r,ans;
} q[N],*ord[N];
inline bool cmp(const query *a,const query *b){
	return a->r<b->r;
}

int n,m,base,a[N],t[1<<19];

int main(){
	scanf("%d%d",&n,&m);
	for(base=1;base<n;base<<=1);
	for(int i=1;i<=n;i++) scanf("%d",a+i);
	for(int i=0;i<m;i++) scanf("%d%d",&q[i].l,&q[i].r),ord[i]=q+i;
	sort(ord,ord+n,cmp);
	for(int i=1,j=0;i<=n;i++){
		if(a[i]<n){
			int x=base+a[i];
			t[x]=i;
			while(x>>=1) t[x]=min(t[x<<1],t[x<<1|1]);
		}
		for(;j<m&&ord[j]->r==i;j++){
			int x=1,k=i;
			while(x<base){
				if(ord[j]->l>min(k,t[x<<1]))
					x=x<<1;
				else{
					k=min(k,t[x<<1]);
					x=x<<1|1;
				}
			}
			ord[j]->ans=x-base;
		}
	}
	for(int i=0;i<m;i++) printf("%d\n",q[i].ans);
}
