#include <cstdio>
#define sizeN 2001
#define sizeM 2001
inline int min(const int a,const int b){return a<b?a:b;}
#define min(a,b,c) min(min(a,b),c)
inline void maxi(int &a,const int b){a<b?a=b:0;}
int N,M,i,j;
bool a[2][sizeM],Flag,flag,tmp;
int f[2][sizeM],h[sizeM],l[sizeM],r[sizeM],Ans,ans;
int main(){
	scanf("%d%d",&N,&M);
	for (i=1,Flag=1;i<=N;++i,Flag^=1){
		for (j=1,flag=Flag;j<=M;++j,flag^=1){
			(tmp=(a[Flag][j]=(getchar(),getchar()-'0')^flag)==a[!Flag][j])?++h[j]:h[j]=1;
			maxi(Ans,f[Flag][j]=(tmp&&a[Flag][j]==a[Flag][j-1]?min(f[Flag][j-1],f[!Flag][j-1],f[!Flag][j])+1:1));
		}
		for (j=1;j<=M;++j)
			for (l[j]=j;l[j]>1&&a[Flag][l[j]-1]==a[Flag][j]&&h[l[j]-1]>=h[j];l[j]=l[l[j]-1]);
		for (j=M;j>=1;--j)
			for (r[j]=j;r[j]<M&&a[Flag][r[j]+1]==a[Flag][j]&&h[r[j]+1]>=h[j];r[j]=r[r[j]+1]);
		for (j=1;j<=M;++j) maxi(ans,h[j]*(r[j]-l[j]+1));
	}
	printf("%d\n%d\n",Ans*Ans,ans);
}
