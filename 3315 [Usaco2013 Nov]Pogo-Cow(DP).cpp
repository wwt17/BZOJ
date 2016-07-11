// f[i][j]=p[i]+max(x[k]-x[j]>=x[j]-x[i]){ f[j][k] }
#include <cstdio>
#include <algorithm>
using namespace std;
const int N=1001,inf=0x7fffffff;
struct data{
	int x,p;
	bool operator < (const data B)const{
		return x<B.x;
	}
} a[N];
int n,Ans,f[N][N],g[N][N];
int main(){
	scanf("%d",&n);
	for(int i=0;i<n;i++) scanf("%d%d",&a[i].x,&a[i].p);
	sort(a,a+n);
	a[n].x=inf;
	a[n].p=0;
	for(int i=n;i--;){
		f[i][i]=g[i][n]=a[i].p;
		for(int j=i+1,k=j;j<n;j++){
			for(;a[k].x<2*a[j].x-a[i].x;k++);
			f[i][j]=a[i].p+g[j][k];
		}
		for(int j=n;--j>i;)
			g[i][j]=max(g[i][j+1],f[i][j]);
		Ans=max(Ans,g[i][i+1]);
	}
	for(int i=n;i--;){
		f[i][i]=g[i][i]=a[i].p;
		for(int j=i+1,k=j;j<n;j++){
			for(;a[k].x<=2*a[j].x-a[i].x;k++);
			g[i][j]=max(g[i][j-1],f[i][j]=a[i].p+g[j][k-1]);
		}
		Ans=max(Ans,g[i][n-1]);
	}
	printf("%d\n",Ans);
}
