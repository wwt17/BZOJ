#include <cstdio>
#include <cmath>

const int N=10005;
typedef double db;
inline db sqr(const db x){
	return x*x;
}

int n;
db x[N],y[N],w[N];
db X,Y;

int main(){
	scanf("%d",&n);
	for(int i=1;i<=n;i++){
		scanf("%lf%lf%lf",x+i,y+i,w+i);
		X+=x[i]*w[i];
		Y+=y[i]*w[i];
	}
	X/=n;
	Y/=n;
	db t=1e3;
	while(t>1e-8){
		db dx=0,dy=0;
		for(int i=1;i<=n;i++){
			double tmp=w[i]/(1e-9+sqrt(sqr(x[i]-X)+sqr(y[i]-Y)));
			dx+=(x[i]-X)*tmp;
			dy+=(y[i]-Y)*tmp;
		}
		X+=dx*t;
		Y+=dy*t;
		if(t>.5) t*=.5;
		else t*=.97;
	}
	printf("%.3lf %.3lf\n",X,Y);
}
