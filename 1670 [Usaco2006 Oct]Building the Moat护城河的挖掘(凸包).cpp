#include <cstdio>
#include <cmath>
#include <algorithm>
using namespace std;
#define size 5001
inline double sqr(const double x) { return x*x; }
struct complex {
	double x,y;
	void read() { scanf("%lf%lf",&x,&y); }
	void print() { printf("(%lf,%lf)\n",x,y); }
} p[size];
inline bool cmpx(const complex& a,const complex& b)
	{ return a.x<b.x||a.x==b.x&&a.y<b.y; }
inline complex vector(const complex& a,const complex& b)
	{ return (complex){b.x-a.x,b.y-a.y}; }
inline double dist(const complex& a,const complex& b)
	{ return sqrt(sqr(a.x-b.x)+sqr(a.y-b.y)); }
inline double cross(const complex& a,const complex& b)
	{ return a.x*b.y-b.x*a.y; }
int main() {
	int N,i;
	scanf("%d",&N);
	for (i=0;i<N;++i) p[i].read();
	sort(p,p+N,cmpx);
	complex* s[size]; int stop=0;
	for (i=0;i<N-1;++i) {
		while (1<stop&&cross(vector(*s[stop],p[i]),vector(*s[stop-1],*s[stop]))<0) --stop;
		s[++stop]=&p[i];
	}
	for (i=N-1;i>=0;--i) {
		while (1<stop&&cross(vector(*s[stop],p[i]),vector(*s[stop-1],*s[stop]))<0) --stop;
		s[++stop]=&p[i];
	}
	double ans=0;
	for (i=1;i<stop;++i) ans+=dist(*s[i],*s[i+1]);
	printf("%.2lf\n",ans);
}
