#include <cstdio>
#include <cmath>
#include <algorithm>
using namespace std;
#define y1 Y1
typedef double db;
const int N=2005;
const db inf=1./0;
int n,st,en;
db v,xS,yS,xT,yT,x1[N],x2[N],y1[N],y2[N],y[N][2],f[N][2];
inline db dist(db x1,db y1,db x2,db y2){
	return sqrt((x1-x2)*(x1-x2)+(y1-y2)*(y1-y2));
}
int main(){
	scanf("%d",&n);
	for(int i=1;i<=n;i++)
		scanf("%lf%lf%lf%lf",x1+i,y1+i,x2+i,y2+i);
	scanf("%lf%lf%lf%lf",&xS,&yS,&xT,&yT);
	if(xS>xT) swap(xS,xT),swap(yS,yT);
	scanf("%lf",&v);
	for(int i=1;i<n;i++){
		y[i][0]=max(y1[i],y1[i+1]);
		y[i][1]=min(y2[i],y2[i+1]);
	}
	for(st=1;x2[st]<xS;st++);
	if(x2[st]==xS){
		if(yS>=y1[st]&&yS<=y2[st]); else st++;
	}
	for(en=n;x1[en]>xT;en--);
	if(x1[en]==xT){
		if(yT>=y1[en]&&yT<=y2[en]); else en--;
	}
	for(int i=st;i<en;i++)
		for(int k=0;k<=1;k++){
			db l=-inf,r=inf;
			f[i][k]=inf;
			for(int j=i-1;j>=st;j--){
				db	a=(y[i][k]-y[j][1])/(x2[i]-x2[j]),
					b=(y[i][k]-y[j][0])/(x2[i]-x2[j]);
				if(a>=l&&a<=r)
					f[i][k]=min(f[i][k],f[j][1]+dist(x2[j],y[j][1],x2[i],y[i][k]));
				if(b>=l&&b<=r)
					f[i][k]=min(f[i][k],f[j][0]+dist(x2[j],y[j][0],x2[i],y[i][k]));
				l=max(l,a);
				r=min(r,b);
			}
			db a=(y[i][k]-yS)/(x2[i]-xS);
			if(a>=l&&a<=r)
				f[i][k]=min(f[i][k],dist(xS,yS,x2[i],y[i][k]));
		}
	db l=-inf,r=inf;
	db ans=inf;
	for(int j=en-1;j>=st;j--){
		db	a=(yT-y[j][1])/(xT-x2[j]),
			b=(yT-y[j][0])/(xT-x2[j]);
		if(a>=l&&a<=r)
			ans=min(ans,f[j][1]+dist(x2[j],y[j][1],xT,yT));
		if(b>=l&&b<=r)
			ans=min(ans,f[j][0]+dist(x2[j],y[j][0],xT,yT));
		l=max(l,a);
		r=min(r,b);
	}
	db a=(yT-yS)/(xT-xS);
	if(a>=l&&a<=r)
		ans=min(ans,dist(xS,yS,xT,yT));
	printf("%.10lf\n",ans/v);
}
