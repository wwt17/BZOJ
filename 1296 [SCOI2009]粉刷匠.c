/*
f[t][i][j]=max{
	f[t-1][i][k]+sum[i][j]-sum[i][k],
	f[t-1][i][k]+j-k-sum[i][j]+sum[i][k]}
*/
inline int max(const int x,const int y){int m=(x-y)>>31;return y&m|x&~m;}
inline int min(const int x,const int y){int m=(y-x)>>31;return y&m|x&~m;}
int N,M,T,t,i,j,k,f[2501][51],sum[51],max1[2501][51],max2[2501][51];
int main(){
	scanf("%u%u%u",&N,&M,&T);
	for(i=1;i<=N;++i){
		scanf("\n");
		for(j=1;j<=M;++j) sum[j]=sum[j-1]+(getchar()=='1');
		int tt=min(i*M,T);
		for(t=1;t<=tt;++t){
			f[t][0]=max1[t][0]=max2[t][0]=f[t][M];
			for(j=1;j<=M;++j){
				f[t][j]=max(f[t][j-1],max(max1[t-1][j-1]+sum[j],max2[t-1][j-1]+j-sum[j]));
				max1[t][j]=max(max1[t][j-1],f[t][j]-sum[j]);
				max2[t][j]=max(max2[t][j-1],f[t][j]-j+sum[j]);
			}
		}
	}
	printf("%u\n",f[T][M]);
}
