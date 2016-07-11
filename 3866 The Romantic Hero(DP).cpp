#include <cstdio>
const int N=(int)1e3+5,M=1024,mo=(int)1e9+7;

int n;
int a[N],f[N][M],g[N][M][2];

inline void inc(int &a,const int b){
	if((a+=b)>=mo) a-=mo;
}

int Main(){
	scanf("%d",&n);
	for(int i=1;i<=n;i++) scanf("%d",&a[i]);
	f[0][0]=1;
	for(int i=1;i<=n;i++){
		for(int j=0;j<M;j++) f[i][j]=f[i-1][j];
		for(int j=0;j<M;j++) inc(f[i][j^a[i]],f[i-1][j]);
	}
	g[n+1][M-1][0]=1;
	for(int i=n;i>=1;i--){
		for(int j=0;j<M;j++) g[i][j][0]=(g[i+1][j][0]+g[i+1][j][1])%mo,g[i][j][1]=0;
		for(int j=0;j<M;j++) inc(g[i][j&a[i]][1],(g[i+1][j][0]+g[i+1][j][1])%mo);
	}
	int ans=0;
	for(int i=0;i<=n;i++){
		for(int j=0;j<M;j++){
			ans=(ans+1LL*(f[i][j]+(j==0?mo-1:0))*g[i+1][j][1])%mo;
		}
	}
	return ans;
}

int main(){
	int T;
	scanf("%d",&T);
	while(T--) printf("%d\n",Main());
}
