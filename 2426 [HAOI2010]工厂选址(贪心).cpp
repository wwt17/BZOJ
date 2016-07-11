#include <cstdio>
#include <algorithm>
using namespace std;
const int N=55,M=50005;
int n,m,b,i,res,a[M],h[N],c[N][M],ord[M];
bool cmp(const int x,const int y){
	return c[i][x]<c[i][y];
}
int main(){
	scanf("%d%d%d%d",&m,&b,&h[0],&n);
	int left_=-b;
	for(i=1;i<=m;i++) scanf("%d",&a[i]),left_+=a[i];
	for(i=1;i<=n;i++) scanf("%d",&h[i]);
	int ans_=0,res=2e9,num=0;
	for(i=0;i<=n;i++){
		for(int j=1;j<=m;j++) scanf("%d",&c[i][j]);
		if(i==0){
			ans_=h[0];
			for(int j=1;j<=m;j++) ans_+=a[j]*c[0][j];
			continue;
		}
		int ans=ans_+h[i];
		for(int j=1;j<=m;j++) c[i][j]-=c[0][j],ord[j]=j;
		sort(ord+1,ord+m+1,cmp);
		int left=left_;
		for(int j=1;j<=m&&left;j++){
			int x=ord[j],d=min(left,a[x]);
			ans+=d*c[i][x];
			left-=d;
		}
		if(ans<res) res=ans,num=i;
	}
	printf("%d\n%d\n",num,res);
}
