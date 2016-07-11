#include <cstdio>
#include <cmath>
const int N=55;
const double eps=1e-8;
int n;
double tmp=1,g[N][N];

int main(){
	scanf("%d",&n);
	for(int i=1;i<=n;i++)
		for(int j=1;j<=n;j++){
			double p;
			scanf("%lf",&p);
			if(p==1) p-=eps;
			if(i!=j){
				if(i<j) tmp*=1-p;
				p=p/(1-p);
				g[i][i]-=g[i][j]=-p;
			}
		}
	n--;
	double det=1;
	for(int i=1;i<=n;i++){
		if(fabs(g[i][i]<eps)){
			det=0;
			break;
		}
		det*=g[i][i];
		for(int k=n;k>=i;k--) g[i][k]/=g[i][i];
		for(int j=1;j<=n;j++) if(j!=i)
			for(int k=n;k>=i;k--) g[j][k]-=g[j][i]*g[i][k];
	}
	printf("%.12lf\n",det*tmp);
}
