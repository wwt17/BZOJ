#include <cstdio>
#include <cmath>
#include <algorithm>
using namespace std;
typedef double db;

#define sqr(x) ((x)*(x))

const int N=505;
const db eps=1e-6;

int n;
db alpha,tana,d[N],s[N],r[N];
struct tpz{
	db x1,y1,x2,y2;
} t[N];

inline bool inside(int a,int b,db d){
	return d+r[b]<=r[a];
}

inline db calc(db x){
	db ans=0;
	for(int i=0;i<=n;i++){
		db dx2=sqr(x-s[i]),r2=sqr(r[i]);
		if(dx2>=r2) continue;
		ans=max(ans,sqrt(r2-dx2));
	}
	for(int i=1;i<=n;i++){
		if(x<t[i].x1||t[i].x2<x) continue;
		ans=max(ans,t[i].y1+(x-t[i].x1)*(t[i].y2-t[i].y1)/(t[i].x2-t[i].x1));
	}
	return ans;
}

db simpson(db l,db r,db mid,db vl,db vr,db vmid,db simp){
	db	midl=(l+mid)/2,midr=(mid+r)/2,
		vmidl=calc(midl),vmidr=calc(midr),
		simpl=(vl+4*vmidl+vmid)*(mid-l)/6,
		simpr=(vmid+4*vmidr+vr)*(r-mid)/6;
	return fabs(simp-simpl-simpr)<eps?simpl+simpr:
		simpson(l,mid,midl,vl,vmid,vmidl,simpl)+
		simpson(mid,r,midr,vmid,vr,vmidr,simpr);
}
int main(){
	scanf("%d%lf",&n,&alpha);
	tana=tan(alpha);
	for(int i=0;i<=n;i++){
		scanf("%lf",&d[i]);
		d[i]/=tana;
		s[i]=(i?s[i-1]:0)+d[i];
	}
	for(int i=0;i<n;i++)
		scanf("%lf",&r[i]);
	r[n]=0;
	for(int i=1;i<=n;i++){
		if(inside(i-1,i,d[i])||inside(i,i-1,d[i])) continue;
		t[i].x1=s[i-1]+r[i-1]*(r[i-1]-r[i])/d[i];
		t[i].y1=sqrt(sqr(r[i-1])-sqr(t[i].x1-s[i-1]));
		t[i].x2=s[i]+r[i]*(r[i-1]-r[i])/d[i];
		t[i].y2=sqrt(sqr(r[i])-sqr(t[i].x2-s[i]));
	}
	db	a=s[0]-r[0],b=s[n]+r[n];
	for(int i=0;i<=n;i++){
		a=min(a,s[i]-r[i]);
		b=max(b,s[i]+r[i]);
	}
	db	mid=(a+b)/2,
		vl=0,vr=0,vmid=calc(mid),
		simp=(vl+4*vmid+vr)*(b-a)/6;
	printf("%.2lf\n",2*simpson(a,b,mid,vl,vr,vmid,simp));
}
