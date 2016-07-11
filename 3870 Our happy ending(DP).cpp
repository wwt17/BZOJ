#include <cstdio>
const int N=21,K=21,mo=(int)1e9+7;

int n,k,L,f[N][1<<K];

inline void inc(int &a,const int b){
	if((a+=b)>=mo) a-=mo;
}

int Main(){
	scanf("%d%d%d",&n,&k,&L);
	long long w=0;
	if(L>k) w=L-k,L=k; k++;
	f[0][1]=1;
	for(int i=1;i<=n;i++){
		for(int j=0;j<1<<k;j++) f[i][j]=0;
		for(int j=0;j<1<<k;j++) if(f[i-1][j]){
			for(int t=0;t<=L;t++)
				inc(f[i][(j|j<<t)&(1<<k)-1],f[i-1][j]);
			inc(f[i][j],f[i-1][j]*w%mo);
		}
	}
	k--;
	int ans=0;
	for(int j=1<<k;j<1<<k+1;j++)
		inc(ans,f[n][j]);
	return ans;
}

int main(){
	int T; scanf("%d",&T);
	while(T--) printf("%d\n",Main());
}
