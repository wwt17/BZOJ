#include <cstdio>
int main(){
	double n; scanf("%lf",&n);
	printf("%.9lf\n",n*(n+1)/(4*n-2));
}
/*
#include <cstdio>

const int N=1005;

int n=100;

double f[N],g[N];

int main(){
	f[0]=0; g[0]=1;
	f[1]=1; g[1]=1;
	for(int i=2;i<=n;i++){
		for(int j=0;j<=i-1;j++)
			g[i]+=g[j]*g[i-1-j];
		for(int j=0;j<=i-1;j++)
			f[i]+=g[j]*g[i-1-j]/g[i]*(f[j]+f[i-1-j]);
		printf("f[%d]=%lf\n",i,f[i]);
	}
	scanf("\n");
}
*/
