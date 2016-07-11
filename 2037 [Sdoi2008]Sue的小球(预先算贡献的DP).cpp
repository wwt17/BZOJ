#include <cstdio>
#include <algorithm>
using namespace std;
typedef long long ll;
const ll inf=(ll)1e18;

const int N=1005;

int n,m,x0;
ll f[N][N][2];

struct data{
	int x,v;
} a[N];
int sum[N];
bool cmpx(const data &a,const data &b){
	return a.x<b.x;
}

void mini(ll &a,const ll &b){
	if(b<a) a=b;
}

int main(){
	scanf("%d%d",&n,&x0);
	ll ans=0;
	for(int i=1;i<=n;i++) scanf("%d",&a[i].x);
	for(int i=1;i<=n;i++){
		int y; scanf("%d",&y);
		ans+=y;
	}
	for(int i=1;i<=n;i++) scanf("%d",&a[i].v);
	a[++n]=(data){x0,0};
	sort(a+1,a+n+1,cmpx);
	m=lower_bound(a+1,a+n+1,(data){x0,0},cmpx)-a;
	for(int i=1;i<=n;i++) sum[i]=sum[i-1]+a[i].v;
	for(int i=1;i<=n;i++)
		for(int j=1;j<=n;j++)
			f[i][j][0]=f[i][j][1]=inf;
	f[m][m][0]=f[m][m][1]=0;
	for(int i=m;i>=1;i--)
		for(int j=m;j<=n;j++){
			ll w=sum[i-1]+sum[n]-sum[j];
			if(i>1)
				mini(f[i-1][j][0],f[i][j][0]+w*(a[i].x-a[i-1].x)),
				mini(f[i-1][j][0],f[i][j][1]+w*(a[j].x-a[i-1].x));
			if(j<n)
				mini(f[i][j+1][1],f[i][j][0]+w*(a[j+1].x-a[i].x)),
				mini(f[i][j+1][1],f[i][j][1]+w*(a[j+1].x-a[j].x));
		}
	printf("%.3lf\n",1e-3*(ans-min(f[1][n][0],f[1][n][1])));
}
