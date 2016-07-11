#include <cstdio>
typedef double db;
const int N=10005;
int n;
db E,lambda,s[N],k[N],vv[N],v[N];
void getvi(int i){
	db c=lambda/2/k[i],x=5e2;
	// f(x)=(x-vv[i])*x^2-c
	// f'(x)=3*x^2-2*vv[i]*x
	for(;;){
		db d=((x-vv[i])*x*x-c)/(3*x*x-2*vv[i]*x);
		if(d<1e-6) break;
		x-=d;
	}
	v[i]=x;
}
int main(){
	scanf("%d%lf",&n,&E);
	for(int i=1;i<=n;i++) scanf("%lf%lf%lf",&s[i],&k[i],&vv[i]);
	db l=0,r=1e3;
	while(r-l>1e-9){
		lambda=(l+r)/2;
		db e=0;
		for(int i=1;i<=n;i++){
			getvi(i);
			e+=k[i]*s[i]*(v[i]-vv[i])*(v[i]-vv[i]);
		}
		if(e>E)
			r=lambda;
		else
			l=lambda;
	}
	db T=0;
	for(int i=1;i<=n;i++) T+=s[i]/v[i];
	printf("%.9lf\n",T);
}
