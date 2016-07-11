#include <cstdio>
#include <cmath>
#include <algorithm>
using namespace std;
const int N=50005;
const double eps=1e-7,inf=1e20;
inline bool mini(double &a,const double b){
	return a>b?(a=b,true):false;
}
inline double round0(double x){
	return fabs(x)<eps?0:x;
}
int n,m,next[N];
struct vec{
	double x,y;
	vec(){
	}
	vec(double _x,double _y):x(_x),y(_y){
	}
	void read(){
		scanf("%lf%lf",&x,&y);
	}
	void println(){
		printf("%.5lf %.5lf\n",round0(x),round0(y));
	}
	bool operator == (const vec &b){
		return x==b.x&&y==b.y;
	}
} a[N],s[N],O;
inline bool cmpa(const vec a,const vec b){
	return atan2(a.y-O.y,a.x-O.x)<atan2(b.y-O.y,b.x-O.x);
}
inline double cross(vec &a,vec &b,vec &c){
	return (b.x-a.x)*(c.y-a.y)-(c.x-a.x)*(b.y-a.y);
}
inline double dot(vec &a,vec &b,vec &c){
	return (b.x-a.x)*(c.x-a.x)+(b.y-a.y)*(c.y-a.y);
}
inline vec rotate(vec &a){
	return vec(-a.y,a.x);
}
vec operator + (vec a,vec b){
	return vec(a.x+b.x,a.y+b.y);
}
vec operator - (vec a,vec b){
	return vec(a.x-b.x,a.y-b.y);
}
vec operator * (const double k,vec a){
	return vec(k*a.x,k*a.y);
}
int main(){
	scanf("%d",&n);
	for(int i=0;i<n;i++) a[i].read();
	O=a[0];
	for(int i=1;i<n;i++) if(a[i].x<O.x) O=a[i];
	O.x+=eps;
	sort(a,a+n,cmpa);
	n=unique(a,a+n)-a;
	for(int i=0;i<n;i++){
		while(m>=2&&cross(s[m-2],s[m-1],a[i])<0) m--;
		s[m++]=a[i];
	}
	for(int i=0;i<m-1;i++) next[i]=i+1;
	next[m-1]=0;
	double ans=inf;
	vec res[4];
	int a=0,b=0,c=0,d=0;
	while(dot(s[a],s[next[a]],s[b])<=dot(s[a],s[next[a]],s[next[b]])) b=next[b];
	d=b;
	while(dot(s[a],s[next[a]],s[d])>=dot(s[a],s[next[a]],s[next[d]])) d=next[d];
	for(;a<m;a++){
		while(dot(s[a],s[next[a]],s[b])<=dot(s[a],s[next[a]],s[next[b]])) b=next[b];
		while(cross(s[a],s[next[a]],s[c])<=cross(s[a],s[next[a]],s[next[c]])) c=next[c];
		while(dot(s[a],s[next[a]],s[d])>=dot(s[a],s[next[a]],s[next[d]])) d=next[d];
		double xb=dot(s[a],s[next[a]],s[b]),xd=dot(s[a],s[next[a]],s[d]),
			y=cross(s[a],s[next[a]],s[c]),k=dot(s[a],s[next[a]],s[next[a]]);
		if(mini(ans,(xb-xd)*y/k)){
			vec ex=s[next[a]]-s[a],ey=rotate(ex);
			res[0]=s[a]+xd/k*ex;
			res[1]=s[a]+xb/k*ex;
			res[2]=res[1]+y/k*ey;
			res[3]=res[0]+y/k*ey;
		}
	}
	printf("%.5lf\n",ans);
	int first=0;
	for(int i=1;i<4;i++)
		if(res[i].y<res[first].y||res[i].y==res[first].y&&res[i].x<res[first].x) first=i;
	for(int i=0;i<4;i++)
		res[(first+i)%4].println();
}
