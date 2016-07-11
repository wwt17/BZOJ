#include <cstdio>
#include <algorithm>
using namespace std;
const int N=305;
typedef long long ll;
const ll inf=1e13;
int n,m,k;
ll f[N][N][2][2][2][2];
bool done[N][N][2][2][2][2];

ll calc(int n,int m,int u,int d,int l,int r){
	if(u&&d&&l&&r) return inf;
	if(n>m) swap(n,m),swap(u,l),swap(d,r);
	if(u>d) swap(u,d);
	if(l>r) swap(l,r);
	ll &ans=f[n][m][u][d][l][r];
	if(done[n][m][u][d][l][r]) return ans;
	done[n][m][u][d][l][r]=true;
	ans=1LL*(n*m-k)*(n*m-k);
	for(int i=1;i<n;i++)
		ans=min(ans,calc(i,m,u,1,l,r)+calc(n-i,m,1,d,l,r));
	for(int j=1;j<m;j++)
		ans=min(ans,calc(n,j,u,d,l,1)+calc(n,m-j,u,d,1,r));
	return ans;
}

int main(){
	scanf("%d%d%d",&n,&m,&k);
	printf("%lld\n",calc(n,m,0,0,0,0));
}
