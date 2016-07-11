#include <cstdio>
#include <cmath>
typedef double db;
const int N=120005;
inline db sqr(db x){
	return x*x;
}
inline db inv(db x){
	return fabs(x)<=1e-7?0:1/x;
}
inline db fix(db x){
	return fabs(x)<=1e-4?0:x;
}
int n,m;
db A,B,C,D,E,F,a[N],b[N],c[N];
int main(){
	scanf("%d",&m);
	while(m--){
		int type; scanf("%d",&type);
		if(type==0){
			db x1,y1,x2,y2; scanf("%lf%lf%lf%lf",&x1,&y1,&x2,&y2);
			x2-=x1;
			y2-=y1;
			a[n]=y2;
			b[n]=-x2;
			c[n]=x2*y1-y2*x1;
			db t=sqrt(sqr(a[n])+sqr(b[n]));
			a[n]/=t;
			b[n]/=t;
			c[n]/=t;
			A+=sqr(a[n]);
			B+=sqr(b[n]);
			C+=2*a[n]*b[n];
			D+=2*a[n]*c[n];
			E+=2*b[n]*c[n];
			F+=sqr(c[n]);
			n++;
		}
		else
		if(type==1){
			int k; scanf("%d",&k); k--;
			A-=sqr(a[k]);
			B-=sqr(b[k]);
			C-=2*a[k]*b[k];
			D-=2*a[k]*c[k];
			E-=2*b[k]*c[k];
			F-=sqr(c[k]);
		}
		else
			printf("%.2lf\n",fix(F-sqr(E)*inv(4*B)-sqr(D-2*C*E*inv(4*B))*inv(4*(A-sqr(C)*inv(4*B)))));
	}
}
