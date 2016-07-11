#include <cstdio>

const int N=1010,K=1010,mo=10007;

#define calc(n) ((n)*((n)-1)>>1)

inline void inc(int &a,const int b){
	a=(a+b)%mo;
}

int n,m,k,i,j,inv[K],f[K][N];
bool deg[N];

int main(){
	scanf("%d%d%d",&n,&m,&k);
	while(m--){
		int x,y; scanf("%d%d",&x,&y);
		deg[x]^=1;
		deg[y]^=1;
	}
	j=0;
	for(i=1;i<=n;i++) j+=deg[i];
	if(j&1) return puts("0"),0;
	f[0][j]=1;
	for(i=0;i<=k;i++){
		for(j=0;j<=n;j+=2){
			if(i>=2) inc(f[i][j],mo-(calc(n)-(i-2))%mo*(i-1)%mo*f[i-2][j]%mo);
			if(j>=2) inc(f[i+1][j-2],calc(j)%mo*f[i][j]);
			if(n-j>=2) inc(f[i+1][j+2],calc(n-j)%mo*f[i][j]);
			inc(f[i+1][j],j*(n-j)%mo*f[i][j]);
		}
	}
	int ans=f[k][0];
	inv[1]=1;
	for(i=2;i<=k;i++) inv[i]=(mo-mo/i)*inv[mo%i]%mo,ans=ans*inv[i]%mo;
	printf("%d\n",ans);
}
