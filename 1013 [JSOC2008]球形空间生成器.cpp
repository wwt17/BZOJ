#include <cstdio>
#include <cstdlib>
#include <cmath>
#define sizen 11
#define eps (1e-8)
inline double sqr(double& a) { return a*a; }
inline bool exist(double& a) { return fabs(a)>eps; }
int main() {
    int n,i,j;
    scanf("%d",&n);
    double equ[n+1][sizen];
    for (i=0;i<=n;++i) {
        equ[i][0]=0;
        for (j=1;j<=n;++j)
            scanf("%lf",&equ[i][j]),
            equ[i][0]+=sqr(equ[i][j]),
            equ[i][j]*=2;
    }
    for (i=n;i;--i)
    		for (j=0;j<=n;++j) equ[i][j]-=equ[i-1][j];
    int k;
    double tmp;
    for (i=1;i<=n;++i) {
				for (k=i;k<=n&&!exist(equ[k][i]);++k);
				if (i!=k)
					for (j=0;j<=n;++j) tmp=equ[i][j],equ[i][j]=equ[k][j],equ[k][j]=tmp;
        equ[i][0]/=equ[i][i];
        for (j=n;j>=i;--j) equ[i][j]/=equ[i][i];
				for (k=1;k<=n;++k) if (k!=i) {
					equ[k][0]-=equ[i][0]*equ[k][i];
          for (j=n;j>=i;--j) equ[k][j]-=equ[i][j]*equ[k][i];
				}
    }
    for (i=1;i<=n;++i) printf("%.3lf%c",equ[i][0],i<n?' ':'\n');
system("pause");}
