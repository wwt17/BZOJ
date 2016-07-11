#include <cstdio>
#include <cstdlib>
#include <cmath>
const int N=20,M=6,Count=4000,Step=200;
const double inf=1e20,eps=1e-9;
inline double sqr(double x){ return x*x; }
int n,m,a[N],b[N],x[M];
double X,Ans=inf;
int main(){
	scanf("%d%d",&n,&m);
	for(int i=0;i<n;i++){
		scanf("%d",a+i);
		X+=a[i];
	}
	X/=m;
	for(int count=0;count<Count;count++){
		for(int j=0;j<m;j++) x[j]=0;
		for(int i=0;i<n;i++) x[b[i]=rand()%m]+=a[i];
		double curo=0;
		for(int j=0;j<m;j++) curo+=sqr(x[j]-X);
		for(int step=0;step<Step;step++){
			int i=rand()%n,k;
			while(b[i]==(k=rand()%m));
			double delta=
				-sqr(x[b[i]]-X)+sqr(x[b[i]]-a[i]-X)
				-sqr(x[k   ]-X)+sqr(x[k   ]+a[i]-X);
			if(delta>=-eps) continue;
			x[b[i]]-=a[i];
			x[b[i]=k]+=a[i];
			curo+=delta;
		}
		if(curo<Ans) Ans=curo;
		if(Ans<0.1*m) break;
	}
	printf("%.2lf\n",sqrt(Ans/m));
}
