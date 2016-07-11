#include <cstdio>
const int N=101,P=10000019;
int m,n,a,b,map[N][N];
long long sum[N][N],sum2[N][N];
bool h[P];
inline int gc(){
	loop:
	switch(getchar()){
		case '0': return 0; break;
		case '1': return 1; break;
		default: goto loop;
	}
}
int main(){
	scanf("%d%d%d%d",&m,&n,&a,&b);
	int i,j;
	long long w1=1,w2=1;
	for(j=1;j<=b;j++) w1=w1*2LL%P;
	for(i=1;i<=a;i++) w2=w2*w1%P;
	for(i=1;i<=m;i++){
		for(j=1;j<=n;j++) map[i][j]=gc();
		for(j=1;j<b;j++) sum[i][j]=(sum[i][j-1]*2LL+map[i][j])%P;
		for(;j<=n;j++)
			sum[i][j]=(sum[i][j-1]*2LL-map[i][j-b]*w1+map[i][j])%P;
	}
	for(i=1;i<a;i++)
		for(j=b;j<=n;j++)
			sum2[i][j]=(sum2[i-1][j]*w1+sum[i][j])%P;
	for(;i<=m;i++)
		for(j=b;j<=n;j++){
			sum2[i][j]=(sum2[i-1][j]*w1-sum[i-a][j]*w2+sum[i][j])%P;
			h[(sum2[i][j]%P+P)%P]=1;
		}
	int q; scanf("%d",&q);
	while(q--){
		long long s=0;
		for(i=1;i<=a;i++)
			for(j=1;j<=b;j++)
				s=(s*2LL+gc())%P;
		putchar('0'|h[s]);
		putchar('\n');
	}
	scanf("\n");
}
