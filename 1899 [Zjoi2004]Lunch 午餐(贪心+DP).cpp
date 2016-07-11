/*
f[i][j]=max(f[i-1][j-a[i]],j+b[i])
f[i][j]=max(f[i-1][j],sum[i]-j+b[i])
*/
#include <cstdio>
#include <algorithm>
using namespace std;
const int N=205,T=205,inf=(int)1e9;
struct data{
	int a,b;
	bool operator < (const data &y) const{
		return b>y.b;
	}
} a[N];
int n,m,sum,f[N*N];
int main(){
	scanf("%d",&n);
	for(int i=1;i<=n;i++) scanf("%d%d",&a[i].a,&a[i].b);
	sort(a+1,a+n+1);
	m=n*T;
	for(int j=1;j<=m;j++) f[j]=inf;
	for(int i=1;i<=n;i++){
		sum+=a[i].a;
		for(int j=sum;j>=0;j--){
			f[j]=max(f[j],sum-j+a[i].b);
			if(j>=a[i].a) f[j]=min(f[j],max(f[j-a[i].a],j+a[i].b));
		}
	}
	int ans=inf;
	for(int j=0;j<=sum;j++) ans=min(ans,f[j]);
	printf("%d\n",ans);
	scanf("\n");
}
