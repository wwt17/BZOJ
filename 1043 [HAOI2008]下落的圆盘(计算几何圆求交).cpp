#include <cstdio>
#include <cmath>
#include <algorithm>
using namespace std;
const int N=1005;
int n;
typedef double db;
const db eps=1e-7,pi=acos(-1);
inline db sqr(const db x){
	return x*x;
}
struct vec{
	db x,y;
	vec(db _x=0,db _y=0):x(_x),y(_y){
	}
};
struct circle:vec{
	db r;
} a[N];
typedef pair<db,int> data;
data ord[N*4],*top;
db ans;
int main(){
	freopen("1043.in","r",stdin);
	freopen("1043.out","w",stdout);
	scanf("%d",&n);
	for(int i=0;i<n;i++) scanf("%lf%lf%lf",&a[i].r,&a[i].x,&a[i].y);
	for(circle *u=a;u<a+n;u++){
		top=ord;
		for(circle *v=u+1;v<a+n;v++){
			vec t(v->x-u->x,v->y-u->y);
			db	dis2=sqr(t.x)+sqr(t.y);
			if(sqrt(dis2)+u->r<=v->r+eps){
				top=ord;
				*top++=data(-pi,1);
				*top++=data(pi,-1);
				break;
			}
			if(sqr(u->r+v->r)<=dis2+eps||sqrt(dis2)+v->r<=u->r+eps) continue;
			db	dir=atan2(t.y,t.x),
				theta=acos((dis2+sqr(u->r)-sqr(v->r))/(2*sqrt(dis2)*u->r)),
				l=dir-theta,
				r=dir+theta;
			if(l<-pi){
				*top++=data(l+2*pi,1);
				*top++=data(pi,-1);
				*top++=data(-pi,1);
				*top++=data(r,-1);
			}
			else
			if(r>pi){
				*top++=data(l,1);
				*top++=data(pi,-1);
				*top++=data(-pi,1);
				*top++=data(r-2*pi,-1);
			}
			else{
				*top++=data(l,1);
				*top++=data(r,-1);
			}
		}
		*top++=data(-pi,0);
		*top++=data(pi,0);
		sort(ord,top);
		int cov=0;
		db now=0;
		for(data *p=ord;p+1<top;p++){
			cov+=p[0].second;
			if(!cov) now+=p[1].first-p[0].first;
		}
		ans+=now*u->r;
	}
	printf("%.3lf\n",ans);
	scanf("\n");
}
