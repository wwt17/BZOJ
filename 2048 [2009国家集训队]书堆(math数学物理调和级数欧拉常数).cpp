#include <cstdio>
#include <cmath>
const double eps=1e-8,y=0.577215665560569;
int main(){
	long long n,m; scanf("%lld%lld",&n,&m);
	double L=0;
	if(n<=1e8)
		for(int i=1;i<=n;i++) L+=1./i;
	else
		L=log(n)+y;
	L*=.5*m;
	printf("%d\n",(int)(L-eps));
}
