#include <cstdio>
#include <algorithm>
using namespace std;

const int N=105;

int n,m,k,size,bnd[N],F;

template<class real,int N,int M>
void Main(){
	int base=M+5;
	static real ans,f[2][N][3][(M+5)*2];
	f[F][1][0][-2+base]=1;
	f[F][1][1][-1+base]=2;
	f[F][1][2][ 0+base]=1;
	bnd[1]=1;
	for(int i=2;i<=n;i++,F^=1){
		bnd[i]=min(i,n-i+1);
		int size=min(M,i*(i+1));
		for(int j=1;j<=bnd[i];j++)
			for(int s=-size+base;s<=size+base;s++)
				for(int k=0;k<=2;k++)
					f[!F][j][k][s]=0;
		for(int j=1;j<=bnd[i-1];j++)
			for(int s=-size+base;s<=size+base;s++){
				f[!F][j+1][0][s-2*i]+=f[F][j][0][s]*(j+1);
				f[!F][j][0][s]+=f[F][j][0][s]*(j*2);
				f[!F][j-1][0][s+2*i]+=f[F][j][0][s]*(j-1);
				f[!F][j+1][1][s-i]+=f[F][j][0][s]*2;
				f[!F][j][1][s+i]+=f[F][j][0][s]*2;
				
				f[!F][j+1][1][s-2*i]+=f[F][j][1][s]*j;
				f[!F][j][1][s]+=f[F][j][1][s]*(j*2-1);
				f[!F][j-1][1][s+2*i]+=f[F][j][1][s]*(j-1);
				f[!F][j+1][2][s-i]+=f[F][j][1][s];
				f[!F][j][2][s+i]+=f[F][j][1][s];
				
				f[!F][j+1][2][s-2*i]+=f[F][j][2][s]*(j-1);
				f[!F][j][2][s]+=f[F][j][2][s]*(j*2-2);
				f[!F][j-1][2][s+2*i]+=f[F][j][2][s]*(j-1);
			}
	}
	for(int s=m;s<=base;s++)
		ans+=f[F][1][2][s+base];
	for(int i=2;i<=n;i++) ans/=i;
	/*
	static char outformat[20];
	sprintf(outformat,"%%%s",format);
	printf(outformat,ans); puts("");
	*/
	printf("%d",(int)ans);
	ans-=(int)ans;
	putchar('.');
	for(int i=1;i<=k;i++){
		ans*=10;
		int t=ans+(i==k?.5:0);
		printf("%d",t);
		ans-=t;
	}
	puts("");
}

int main(){
	scanf("%d%d%d",&n,&m,&k);
	if(k<=15)
		Main<double,N,7500>();
	else
		Main<__float128,N/2,2000>();
}
