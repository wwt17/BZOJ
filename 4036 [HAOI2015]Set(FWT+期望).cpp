#include <cstdio>
#include <cmath>

const int N=20;

typedef double real;

const real eps=1e-8;

int n;

void fwt(real *a,int n,int f){
	for(int l=1;l<n;l<<=1){
		for(int i=0;i<n;i+=l<<1)
			for(int j=0;j<l;j++){
				a[i+j+l]+=a[i+j]*f;
			}
	}
}

real a[1<<N];

int main(){
	scanf("%d",&n);
	for(int i=0;i<1<<n;i++) scanf("%lf",&a[i]);
	fwt(a,1<<n,1);
	for(int i=0;i<1<<n;i++) a[i]=fabs(a[i]-1)<=eps?0:1/(a[i]-1);
	fwt(a,1<<n,-1);
	real ans=a[(1<<n)-1];
	if(fabs(ans)<=eps)
		puts("INF");
	else
		printf("%.10lf\n",ans);
}
