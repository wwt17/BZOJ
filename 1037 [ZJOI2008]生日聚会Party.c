//http://hi.baidu.com/zeonsgtr/item/10ac450c1de691126c9048bd
#include <stdio.h>
#define size 152
#define sizeK 21
#define P 12345678
short N,M,K,i,j,k1,k2,Flag;
int f[size][size][sizeK][sizeK],ans;
inline void inc(int* a,const int b){*a=(*a+b)%P;}
int main(){
	scanf("%hd%hd%hd",&N,&M,&K);
	f[0][0][0][0]=1;
	for (i=0;i<=N;++i) for (j=0;j<=M;++j) if (abs(i-j)<=K)
		for (k1=0;k1<=K;++k1) for (k2=0;k2<=K;++k2) if (f[i][j][k1][k2]){
			if (k1<K) inc(&f[i+1][j][k1+1][k2?k2-1:0],f[i][j][k1][k2]);
			if (k2<K) inc(&f[i][j+1][k1?k1-1:0][k2+1],f[i][j][k1][k2]);
		}
	for (k1=0;k1<=K;++k1) for (k2=0;k2<=K;++k2) inc(&ans,f[N][M][k1][k2]);
	printf("%d\n",ans);
}
