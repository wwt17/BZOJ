#include <cstdio>

const int N=9;

inline void maxi(int &a,const int b){
	if(b>a) a=b;
}

int n,m;

int w[1<<N][N][2];
int f[1<<(N+1)][1<<(N+1)];
int lg[1<<N];

int main(){
	scanf("%d%d",&n,&m); n--;
	for(int flag=1;flag>=0;flag--)
		for(int i=0;i<1<<n;i++)
			for(int j=n-1;j>=0;j--) scanf("%d",&w[i][j][flag]);
	for(int i=2;i<1<<n;i++) lg[i]=lg[i>>1]+1;
	for(int i=0;i<1<<n;i++){
		int loc=1<<n|i;
		for(int j=(1<<n)-2;j>=0;j--){
			int lowbit=~j&-~j;
			f[loc][j|0<<n]=f[loc][j^lowbit|0<<n]+w[i][lg[lowbit]][0];
		}
		for(int j=1;j<1<<n;j++){
			int lowbit=j&-j;
			f[loc][j|1<<n]=f[loc][j^lowbit|1<<n]+w[i][lg[lowbit]][1];
		}
	}
	for(int i=(1<<n)-1;i>=1;i--){
		int lev=lg[i];
		for(int j=0;j<1<<lev;j++)
			for(int flag=0;flag<=1;flag++){
				int jj=j|flag<<lev;
				for(int k0=0;k0<=1<<(n-lev-1);k0++)
					for(int k1=0;k1<=1<<(n-lev-1);k1++)
						maxi(f[i][j|(k0+k1)<<lev],f[i<<1|0][jj|k0<<(lev+1)]+f[i<<1|1][jj|k1<<(lev+1)]);
			}
	}
	int ans=0;
	for(int k=0;k<=m;k++) maxi(ans,f[1][k]);
	printf("%d\n",ans);
}
