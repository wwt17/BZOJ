#include <cstdio>
#include <cmath>
#include <algorithm>
using namespace std;
const int N=50000;
const double eps=1e-8;
int n;
struct vec{
	double x,y;
	vec(){
	}
	vec(double _x,double _y):x(_x),y(_y){
	}
	inline void read(){
		scanf("%lf%lf",&x,&y);
	}
} O,a[N],b[N],s[N],*top;
inline double area(vec &a,vec &b,vec &c){
	return (b.x-a.x)*(c.y-a.y)-(c.x-a.x)*(b.y-a.y);
}
bool cmpxy(const vec &a,const vec &b){
	return a.x<b.x || a.x==b.x && a.y<b.y;
}
bool cmpa(const vec &a,const vec &b){
	return atan2(a.y-O.y,a.x-O.x)<atan2(b.y-O.y,b.x-O.x);
}
void add(vec &p){
	while(top-s>1&&area(top[-2],p,top[-1])>0) top--;
	*top++=p;
}
int score(vec a[],vec b[]){
	int ans=0;
	sort(a,a+n,cmpxy);
	O=vec((a[0].x+a[n-1].x)/2+eps*1000,(a[0].y+a[n-1].y)/2+eps*1000);
	top=s;
	for(int i=0;i<n;i++) add(a[i]);
	for(int i=n-1;i--;) add(a[i]);
	sort(s,--top,cmpa);
	for(int i=0;i<n;i++){
		vec *next=lower_bound(s,top,b[i],cmpa),*last=next-1;
		if(next==s) last=top-1;
		if(next==top) next=s;
		double tmp=area(*last,*next,b[i]);
		if(tmp>eps||fabs(tmp)<=eps
			 &&(last->x<=b[i].x&&b[i].x<=next->x
			 || next->x<=b[i].x&&b[i].x<=last->x)
			 &&(last->y<=b[i].y&&b[i].y<=next->y
			 || next->y<=b[i].y&&b[i].y<=last->y)
			) ans++;
	}
	return ans;
}
int main(){
	scanf("%d",&n);
	for(int i=0;i<n;i++) a[i].read();
	for(int i=0;i<n;i++) b[i].read();
	printf("%d %d\n",score(a,b),score(b,a));
}
