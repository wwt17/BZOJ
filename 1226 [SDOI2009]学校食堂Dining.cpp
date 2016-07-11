/*
f[i,j,k]表示前i个人全部完成，上一个人是i+j，且i+1到i+7的状态为k的方案数
若 k&1
f[i+1,j-1,k>>1]min=f[i][j][k]
设 (这次放的位置-i) 为 J (!(k&1<<J))
f[i,J,k|1<<(J-1)]min=f[i,j,k]+(T[i+j]^T[i+J])
Ans=min{f[N,j,0]}
*/
/*
f[i,j,k]表示前i个人全部完成，上一个人是i+j，且i+1到i+7的状态为k的方案数
若 k&1
f[i+1,j-1,k>>1]min=f[i][j][k]
设 (这次放的位置-i) 为 J (!(k&1<<J))
f[i,J,k|1<<(J-1)]min=f[i,j,k]+(T[i+j]^T[i+J])
Ans=min{f[N,j,0]}
*/
#include <cstdio>
#include <cstdlib>
#include <cstring>
#define sizeN 1010
#define sizeB 8
#define INF 0x3F3F3F3F
inline void mini(int &a,const int b){if(a>b)a=b;}
const int bound=1<<(sizeB+1);
int N,i,I,j,J,k,bnd,Ans,T[sizeN],B[sizeN];
typedef int data[bound];
data F[2][(sizeB+1)<<1],*f[2];
int main(){
	f[0]=F[0]+sizeB;
	f[1]=F[1]+sizeB;
	int C;
	scanf("%d",&C);
	while(C--){
		scanf("%d",&N);
		for(i=1;i<=N;++i) scanf("%d%d",T+i,B+i);
		memset(F[I],0x3F,sizeof(F[I]));
		f[I][0][0]=0;
		for(i=0;i<=N;++i,I^=1){
			memset(F[!I],0x3F,sizeof(F[!I]));
			for(k=0;k<bound;++k)
				for(j=-sizeB;j<=sizeB+1;++j) if(f[I][j][k]!=INF)
					if(k&1) mini(f[!I][j-1][k>>1],f[I][j][k]); else
						for(J=1,bnd=sizeB;J<=bnd;++J) if(!(k&1<<(J-1))){
							mini(bnd,J+B[i+J]);
							mini(f[I][J][k|1<<(J-1)],f[I][j][k]+(i+j?T[i+j]^T[i+J]:0));
						}
		}
		Ans=INF;
		for(j=-sizeB;j<=0;++j) mini(Ans,f[!I][j][0]);
		printf("%d\n",Ans);
	}
}
