#include <cstdio>
#include <algorithm>
using namespace std;
typedef long long ll;
const int N=72;
const ll inf=1e18;
inline void mini(ll &a,const ll b){
	if(b<a) a=b;
}
int n,W;
struct node{
	int a,b,c;
} a[N];
bool cmp(const node &x,const node &y){
	return x.a<y.a;
}
ll sum[N],f[N][N][N];
int main(){
	scanf("%d%d",&n,&W);
	for(int i=1;i<=n;i++) scanf("%d",&a[i].a);
	for(int i=1;i<=n;i++) scanf("%d",&a[i].b);
	for(int i=1;i<=n;i++) scanf("%d",&a[i].c);
	sort(a+1,a+n+1,cmp);
	for(int i=1;i<=n;i++) sum[i]=sum[i-1]+a[i].c;
	for(int i=n;i>=1;i--)
		for(int j=i;j<=n;j++){
			int kk=i;
			for(int k=i;k<=j;k++) if(a[k].b<a[kk].b) kk=k;
			for(int t=0;t<=n;t++){
				f[i][j][t]=inf;
				for(int k=i;k<=j;k++){
					mini(f[i][j][t],f[i][k-1][t]+f[k+1][j][t]+W+(sum[j]-sum[i-1]-a[k].c));
					if(a[k].b>a[t].b)
					mini(f[i][j][t],f[i][k-1][k]+f[k+1][j][k]+(sum[j]-sum[i-1]-a[k].c));
				}
			}
		}
	printf("%lld\n",f[1][n][0]+sum[n]);
}
