#include <cstdio>
const int N=305;
int n,q,mo,C[N][N],cnt[N],sum[N],f[N][N];
int main(){
	int T; scanf("%d",&T);
	while(T--){
		scanf("%d%d%d",&n,&q,&mo);
		for(int i=1;i<=n;i++) cnt[i]=0;
		while(q--){
			int x; scanf("%*d%d",&x);
			cnt[x]++;
		}
		bool ok=true;
		sum[n]=0;
		for(int i=n-1;i>=0;i--){
			sum[i]=sum[i+1]+cnt[i+1];
			if(sum[i]>n-i) ok=false;
		}
		if(!ok){
			puts("NO");
			continue;
		}
		for(int i=0;i<=n;i++)
			for(int j=0;j<=i;j++)
				C[i][j]=j?(C[i-1][j]+C[i-1][j-1])%mo:1;
		for(int j=0;j<=n;j++) f[n][j]=0;
		f[n][0]=1;
		for(int i=n-1;i>=0;i--){
			for(int j=0;j<=n;j++) f[i][j]=0;
			for(int j=0;j<=n-i-sum[i];j++)
				for(int k=0;k<=j;k++)
					f[i][j]=(f[i][j]+1LL*f[i+1][j-k]*C[j][k])%mo;
		}
		printf("YES %d\n",f[0][n-sum[0]]);
	}
}
