#include <cstdio>
#include <cmath>
#include <set>
using namespace std;
const int M=100001,Q=200000;
inline double sqr(double x){ return x*x; }
int X,Y;
double ans;
struct vec{
	int x,y; double a;
	vec(){
	}
	vec(int _x,int _y):x(_x),y(_y),a(atan2(_y-Y,_x-X)){
	}
	bool operator < (const vec &b) const{
		return a<b.a;
	}
} p[M];
bool flag[M];
inline double dist(const vec &A,const vec &B){
	return sqrt(sqr(A.x-B.x)+sqr(A.y-B.y));
}
inline double area(const vec &A,const vec &B,const vec &C){
	return (double)(B.x-A.x)*(C.y-A.y)-(double)(B.y-A.y)*(C.x-A.x);
}
multiset<vec> s;
struct query{
	int type,i; double ans;
} qr[Q];
void insert(vec &p){
	if(p.x==0) return;
	set<vec>::iterator loc=s.insert(p),it1=loc,it2=loc,next;
	--it1; ++it2;
	if(area(*it1,*it2,p)>0){
		s.erase(loc);
		return;
	}
	ans-=dist(*it1,*it2);
	for(next=it1;it1!=s.begin();it1=next){
		next--;
		if(area(*next,*it1,p)>=0) break;
		ans-=dist(*next,*it1);
		s.erase(it1);
	}
	ans+=dist(*it1,p);
	for(next=it2,next++;next!=s.end();it2=next,next++){
		if(area(*next,*it2,p)<=0) break;
		ans-=dist(*next,*it2);
		s.erase(it2);
	}
	ans+=dist(*it2,p);
}
int main(){
	int n,m,q,x,y;
	scanf("%d%d%d",&n,&x,&y);
	X=n/2,Y=0;
	s.insert(vec(0,0));
	s.insert(vec(n,0));
	*p=vec(x,y);
	ans=n;
	scanf("%d",&m);
	for(int i=1;i<=m;i++){
		scanf("%d%d",&x,&y);
		p[i]=vec(x,y);
	}
	scanf("%d",&q);
	for(int t=0;t<q;t++)
		if(scanf("%d",&qr[t].type),qr[t].type==1)
			scanf("%d",&qr[t].i),flag[qr[t].i]=true;
	for(int i=0;i<=m;i++) if(!flag[i])
		insert(p[i]);
	for(int t=q;t--;)
		switch(qr[t].type){
			case 1: insert(p[qr[t].i]); break;
			case 2: qr[t].ans=ans;
		}
	for(int t=0;t<q;t++) if(qr[t].type==2)
		printf("%.2lf\n",qr[t].ans);
}
