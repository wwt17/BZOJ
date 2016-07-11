#include <cstdio>
const int N=500005,M=205,P=1005;
int n,m,q;
int cnt[M][M][P],sum[M][M][P];
void work1(){
	for(int i=1;i<=n;i++)
		for(int j=1;j<=m;j++){
			for(int k=0;k<P;k++)
				cnt[i][j][k]=cnt[i-1][j][k]+cnt[i][j-1][k]-cnt[i-1][j-1][k],
				sum[i][j][k]=sum[i-1][j][k]+sum[i][j-1][k]-sum[i-1][j-1][k];
			int p; scanf("%d",&p);
			for(int k=0;k<=p;k++)
				cnt[i][j][k]++,sum[i][j][k]+=p;
		}
	while(q--){
		int x0,y0,x1,y1,h;
		scanf("%d%d%d%d%d",&x0,&y0,&x1,&y1,&h);
		x0--,y0--;
		int l=0,r=P;
		while(r-l>1){
			int mid=l+r>>1;
			if(sum[x0][y0][mid]-sum[x1][y0][mid]-sum[x0][y1][mid]+sum[x1][y1][mid]>=h)
				l=mid;
			else
				r=mid;
		}
		if(l==0)
			puts("Poor QLW");
		else
			printf("%d\n",cnt[x0][y0][l]-cnt[x1][y0][l]-cnt[x0][y1][l]+cnt[x1][y1][l]
			-(sum[x0][y0][l]-sum[x1][y0][l]-sum[x0][y1][l]+sum[x1][y1][l]-h)/l);
	}
}
struct tree{
	tree *l,*r;
	int cnt,sum;
} null[N*11],*newtree=null+1,*f[N];
int X;
tree* insert(tree *cur,int beg,int end){
	tree *ret=newtree++;
	if(cur!=null) *ret=*cur;
	else ret->l=ret->r=null;
	ret->cnt++;
	ret->sum+=X;
	if(end-beg==1) return ret;
	int mid=beg+end>>1;
	if(X<mid)
		ret->l=insert(ret->l,beg,mid);
	else
		ret->r=insert(ret->r,mid,end);
	return ret;
}
void work2(){
	null->l=null->r=null;
	f[0]=null;
	for(int i=1;i<=m;i++){
		scanf("%d",&X);
		f[i]=insert(f[i-1],0,P);
	}
	while(q--){
		int l,r,h;
		scanf("%*d%d%*d%d%d",&l,&r,&h);
		l--;
		if(f[r]->sum-f[l]->sum<h){
			puts("Poor QLW");
			continue;
		}
		int beg=0,end=P;
		tree *x=f[l],*y=f[r];
		int tot=0;
		while(end-beg>1){
			int mid=beg+end>>1;
			if(h>y->r->sum-x->r->sum){
				h-=y->r->sum-x->r->sum;
				tot+=y->r->cnt-x->r->cnt;
				end=mid;
				x=x->l;
				y=y->l;
			}
			else{
				beg=mid;
				x=x->r;
				y=y->r;
			}
		}
		tot+=y->cnt-x->cnt-(y->sum-x->sum-h)/beg;
		printf("%d\n",tot);
	}
}
int main(){
	scanf("%d%d%d",&n,&m,&q);
	if(n>1)
		work1();
	else
		work2();
}
