#include <cstdio>
#include <cmath>
#include <list>
using namespace std;
const int N=305;
const double eps=1e-8,inf=1e15;
inline double fcmp(double x){
	return fabs(x)<eps?0:x;
}
int n; double ans=inf;
struct point{
	double x,y;
	point(){
	}
	point(double _x,double _y):x(_x),y(_y){
	}
	//void print(){ printf(" (%.2lf,%.2lf)",x,y); }
} a[N];
double area(point &A,point &B,point &C){
	return (B.x-A.x)*(C.y-A.y)-(C.x-A.x)*(B.y-A.y);
}
point intersection(point A,point B,point C,point D){
	double s1=area(A,B,C);
	double s2=area(A,B,D);
	return point((C.x*s2+D.x*-s1)/(-s1+s2),(C.y*s2+D.y*-s1)/(-s1+s2));
}
list<point> b;
/*
void print(){
	printf("b:\n"); for(list<point>::iterator i=b.begin();i!=b.end();i++) i->print(),puts(""); puts("");
}
*/
int main(){
	scanf("%d",&n);
	for(int i=0;i<n;i++) scanf("%lf",&a[i].x);
	for(int i=0;i<n;i++) scanf("%lf",&a[i].y);
	b.push_back(point(a[0].x,inf));
	b.push_back(point(a[0].x,-inf));
	b.push_back(point(a[n-1].x,-inf));
	b.push_back(point(a[n-1].x,inf));
	//print();
	list<point>::iterator cur,next;
	point *curp,*nextp;
	for(curp=a,nextp=a+1;nextp<a+n;curp=nextp++){
		#define judge(it) (fcmp(area(*curp,*nextp,*(it)))<=0)
		bool curmk=judge(b.begin()),nextmk;
		for(cur=b.begin(),next=++b.begin();next!=b.end();curmk=nextmk,cur=next++){
			nextmk=judge(next);
			if(curmk^nextmk) b.insert(next,intersection(*cur,*next,*curp,*nextp));
			//print();
			if(curmk) b.erase(cur);
			//print();
		}
		//print();
	}
	curp=a,nextp=a+1;
	for(cur=b.begin(),next=++b.begin();next!=b.end();cur=next++){
		double k=(next->y-cur->y)/(next->x-cur->x),b=cur->y-k*cur->x;
		for(;nextp<a+n&&nextp->x<next->x;curp=nextp++)
			ans=min(ans,k*nextp->x+b-nextp->y);
		if(nextp==a+n) break;
		k=(nextp->y-curp->y)/(nextp->x-curp->x),b=curp->y-k*curp->x;
		ans=min(ans,next->y-k*next->x-b);
	}
	printf("%.3lf\n",fcmp(ans));
}
