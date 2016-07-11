#include <cstdio>
#include <algorithm>
using namespace std;
typedef long long ll;
const int N=1005,mo=(int)1e9+7;

ll power(ll a,ll b){
	ll ans=1;
	for(;b;b>>=1,a=a*a%mo) if(b&1) ans=ans*a%mo;
	return ans;
}

int n,cnt[N],sum[N],f[N][N],g[N][N];

int main(){
	for(int Case=1;scanf("%d",&n),n;Case++){
		for(int i=1;i<=n;i++){
			scanf("%d",&cnt[i]);
			for(int j=0;j<cnt[i];j++) scanf("%*d");
			sum[i]=sum[i-1]+cnt[i];
		}
		f[0][0]=1;
		for(int i=1;i<=n;i++){
			for(int j=0;j<i;j++) g[0][j]=f[i-1][j];
			for(int k=1;k<=cnt[i];k++)
				for(int j=0;j<i;j++)
					g[k][j]=(g[k-1][j]+(!j?0:1LL*g[k-1][j-1]*(i-j)))%mo;
			for(int j=0;j<i;j++) f[i][j]=g[cnt[i]][j]; f[i][i]=0;
			
			for(int j=0;j<i;j++) g[0][j]=1LL*f[i-1][j]*max(0,sum[i-1]-j)%mo;
			for(int k=1;k<=cnt[i];k++)
				for(int j=0;j<i;j++)
					g[k][j]=(g[k-1][j]+(!j?0:1LL*g[k-1][j-1]*(i-j)))%mo;
			for(int j=0;j<i;j++) f[i][j+1]=(f[i][j+1]+g[cnt[i]][j])%mo;
		}
		int ans=1,c=0;
		for(int i=1;i<=n;i++) if(cnt[i]==0) ans=1LL*ans*(++c)%mo;
		ans=power(ans,mo-2);
		ans=1LL*ans*f[n][n]%mo;
		printf("Case #%d: %d\n",Case,ans);
	}
}
