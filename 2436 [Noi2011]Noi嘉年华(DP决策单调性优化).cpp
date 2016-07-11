#include <cstdio>
#include <algorithm>
using namespace std;
const int N=205,inf=N*5;
int n,m,ord[N*2],*top=ord,num[N*2][N*2],pre[N*2][N],suc[N*2][N],ans[N*2][N*2],res[N];
struct data{
	int st,en;
} a[N];
bool cmp(const data &a,const data &b){
	return a.en<b.en;
}
bool maxi(int &a,const int b){
	return b>=a?(a=b,true):false;
}
int main(){
	scanf("%d",&n);
	*top++=0;
	for(int i=0;i<n;i++){
		scanf("%d%d",&a[i].st,&a[i].en),a[i].en+=a[i].st;
		*top++=a[i].st;
		*top++=a[i].en;
	}
	sort(ord,top);
	top=unique(ord,top);
	m=top-ord;
	for(int i=0;i<n;i++){
		a[i].st=lower_bound(ord,top,a[i].st)-ord;
		a[i].en=lower_bound(ord,top,a[i].en)-ord;
	}
	for(int i=0;i<=m;i++)
		for(int j=i+1;j<=m;j++){
			num[i][j]=0;
			for(int k=0;k<n;k++) if(a[k].st>=i&&a[k].en<=j) num[i][j]++;
		}
	for(int j=1;j<=n;j++) pre[0][j]=-inf;
	for(int i=1;i<=m;i++)
		for(int j=0;j<=n;j++){
			pre[i][j]=pre[i-1][j];
			for(int k=0;k<i;k++){
				maxi(pre[i][j],pre[k][j]+num[k][i]);
				if(j>=num[k][i])
				maxi(pre[i][j],pre[k][j-num[k][i]]);
			}
		}
	for(int j=1;j<=n;j++) suc[m-1][j]=-inf;
	for(int i=m-2;i>=0;i--)
		for(int j=0;j<=n;j++){
			suc[i][j]=suc[i+1][j];
			for(int k=m-1;k>i;k--){
				maxi(suc[i][j],suc[k][j]+num[i][k]);
				if(j>=num[i][k])
				maxi(suc[i][j],suc[k][j-num[i][k]]);
			}
		}
	int ans1=0;
	for(int i=0;i<m;i++)
		for(int j=i+1;j<m;j++){
			ans[i][j]=-inf;
			for(int x=0,y=n;x<=n;x++){
				maxi(ans[i][j],min(x+y+num[i][j],pre[i][x]+suc[j][y]));
				for(;y>0&&maxi(ans[i][j],min(x+(y-1)+num[i][j],pre[i][x]+suc[j][y-1]));y--);
			}
			maxi(ans1,ans[i][j]);
			for(int k=0;k<n;k++) if(i<=a[k].st&&j>=a[k].en) maxi(res[k],ans[i][j]);
		}
	printf("%d\n",ans1);
	for(int k=0;k<n;k++) printf("%d\n",res[k]);
}
