#include <cstdio>
#include <cstring>
inline void maxi(int &a,const int b){if(a<b)a=b;}
inline int max(int a,int b){return a>b?a:b;}
#define max4(a,b,c,d) max(max(a,b),max(c,d))
int N,M,K,i,k,v0,v1,f[2][11][5],F;
// 0:00 1:01 2:10 3:11 4:All
int main(){
	scanf("%u%u%u",&N,&M,&K);
	memset(f[F],0x80,sizeof(f[F]));
	f[F][0][0]=0;
	if(M==1)
		for(i=1;i<=N;++i){
			F^=1;
			scanf("%d",&v0);
			memcpy(f[F],f[!F],sizeof(f[F]));
			for(k=0;k<=K;++k){
				if(k<1) continue;
				maxi(f[F][k][1],f[!F][k-1][0]);
			}
			for(k=0;k<=K;++k)
				f[F][k][1]+=v0;
			for(k=K;k>=0;--k)
				maxi(f[F][k][0],f[F][k][1]);
		}
	else
		for(i=1;i<=N;++i){
			F^=1;
			scanf("%d %d",&v0,&v1);
			memcpy(f[F],f[!F],sizeof(f[F]));
			for(k=0;k<=K;++k){
				if(k<1) continue;
				maxi(f[F][k][1],f[!F][k-1][0]);
				maxi(f[F][k][2],f[!F][k-1][0]);
				maxi(f[F][k][3],max(f[!F][k-1][1],f[!F][k-1][2]));
				maxi(f[F][k][4],f[!F][k-1][0]);
				if(k<2) continue;
				maxi(f[F][k][3],f[!F][k-2][0]);
			}
			for(k=0;k<=K;++k){
				f[F][k][1]+=v0;
				f[F][k][2]+=v1;
				f[F][k][3]+=v0+v1;
				f[F][k][4]+=v0+v1;
			}
			for(k=K;k>=0;--k){
				maxi(f[F][k][0],max4(f[F][k][1],f[F][k][2],f[F][k][3],f[F][k][4]));
				maxi(f[F][k][1],f[F][k][3]);
				maxi(f[F][k][2],f[F][k][3]);
			}
		}
	printf("%d\n",f[F][K][0]);
}
