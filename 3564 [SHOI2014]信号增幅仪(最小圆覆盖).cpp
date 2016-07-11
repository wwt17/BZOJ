#include <cstdio>
#include <cmath>
#include <algorithm>
using namespace std;

const int N=1000005;
const double eps=1e-6;

int n;

struct vec{
	double x,y;
	void read(){
		scanf("%lf%lf",&x,&y);
	}
} a[N];

double t[2][3];

#define sqr(x) ((x)*(x))

inline double dist2(vec &a,vec &b){
	return sqr(a.x-b.x)+sqr(a.y-b.y);
}

pair<vec,double> mincircle(vec *beg,vec *end){
	vec O=*beg;
	double R2=0;
	for(vec *i=beg+1;i<end;i++) if(dist2(O,*i)>R2){
		O=*i;
		R2=0;
		for(vec *j=beg;j<i;j++) if(dist2(O,*j)>R2){
			vec *k;
			double best=0;
			for(vec *kk=beg;kk<j;kk++){
				double now=((i->x-kk->x)*(j->x-kk->x)+(i->y-kk->y)*(j->y-kk->y))/sqrt(dist2(*i,*kk)*dist2(*j,*kk));
				if(now>best){
					best=now;
					k=kk;
				}
			}
			if(best){
				double 	leni=sqr(i->x)+sqr(i->y),
						lenj=sqr(j->x)+sqr(j->y),
						lenk=sqr(k->x)+sqr(k->y);
				if(fabs(k->x-i->x)>eps){
					O.y=((lenk-leni)*(k->x-j->x)/(2*(k->x-i->x))-(lenk-lenj)/2)/((k->y-i->y)*(k->x-j->x)/(k->x-i->x)-(k->y-j->y));
					O.x=((lenk-leni)/2-(k->y-i->y)*O.y)/(k->x-i->x);
				}
				else{
					O.y=((lenk-lenj)*(k->x-i->x)/(2*(k->x-j->x))-(lenk-leni)/2)/((k->y-j->y)*(k->x-i->x)/(k->x-j->x)-(k->y-i->y));
					O.x=((lenk-lenj)/2-(k->y-j->y)*O.y)/(k->x-j->x);
				}
			}
			else{
				O.x=(i->x+j->x)/2;
				O.y=(i->y+j->y)/2;
			}
			R2=dist2(O,*i);
		}
	}
	return make_pair(O,R2);
}

int main(){
	scanf("%d",&n);
	for(int i=0;i<n;i++) a[i].read();
	random_shuffle(a,a+n);
	pair<vec,double> ans=mincircle(a,a+n);
	printf("%.2lf %.2lf %.2lf\n",ans.first.x,ans.first.y,sqrt(ans.second));
}
