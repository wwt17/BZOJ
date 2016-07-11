//f[i][j]=min{f[i-1][k]+C*abs(j-k)}+(j-height[i])^2
//min1[i][j]=min{f[i][k]+C*-k} (k<=j)
//min2[i][j]=min{f[i][k]+C*k} (k>=j)
//f[i][j]=min(min1[i][j]+C*j,min2[i][j+1]-C*j)+(j-height[i])^2
//#include <stdio.h>
#define M 100
#define INF 1000000000
inline int min(const int x,const int y){int m=(y-x)>>31;return y&m|x&~m;}
#define sqr(x) (x)*(x)
int N,C,i,j,height_i,f[M+1],min1[M+1],min2[M+2];
int main(){
	freopen("in.txt","r",stdin);
	freopen("out.txt","w",stdout);
	scanf("%u%u",&N,&C);
	min1[0]=min2[M+1]=INF;
	for(j=1;j<=M;++j) min1[j]=-C*j,min2[j]=C*j;
	for(i=1;i<=N;++i){
		scanf("%u",&height_i);
		for(j=1;j<height_i;++j) f[j]=INF;
		for(;j<=M;++j)
			f[j]=min(min1[j]+C*j,min2[j]-C*j)+sqr(j-height_i);
		for(j=1;j<=M;++j) min1[j]=min(min1[j-1],f[j]-C*j);
		for(j=M;j   ;--j) min2[j]=min(min2[j+1],f[j]+C*j);
	}
	int Ans=INF;
	for(j=1;j<=M;++j) Ans=min(Ans,f[j]);
	printf("%d\n",Ans);
}
