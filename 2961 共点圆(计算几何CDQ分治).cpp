/*
(x-x0)^2+(y-y0)^2<=x0^2+y0^2
x^2+y^2<=2*x0*x+2*y0*y
x=x/(x^2+y^2)
y=y/(x^2+y^2)
2*x0*x+2*y0*y>=1
x0*x+y0*y>=.5
y0*y>=.5-x0*x
because y0>0
y>=.5/y0-x0/y0*x
维护二次函数一样的半平面凸壳
*/ 

#include <cstdio>
#include <algorithm>
using namespace std;
typedef double db;

const int N=500005;

int n,m;

bool ans[N];
struct vec{
	db x,y; int z;
	friend bool operator < (const vec &a,const vec &b){
		if(a.z<0&&b.z<0) return a.y==b.y?a.x>b.x:a.y<b.y;
		if(a.z<0||b.z<0) return a.z<0;
		return a.x<b.x;
	}
	friend db operator % (const vec &a,const vec &b){
		return (b.x-a.x)/(a.y-b.y);
	}
	bool up(const vec &b){
		return y*b.x+x<=b.y;
	}
} a[N];
int t,p[N];
db c[N];

void work(int beg,int end){
	if(end-beg==1) return;
	int mid=beg+end>>1;
	work(beg,mid);
	work(mid,end);
	t=0;
	for(int i=beg;i<mid;i++) if(a[i].z<0&&(!t||a[i].y!=a[p[t]].y)){
		while(t>=2&&a[p[t]]%a[i]<=c[t-1]) t--;
		if(t) c[t]=a[p[t]]%a[i];
		p[++t]=i;
	}
	if(t) for(int i=mid,j=1;i<end;i++) if(a[i].z>=0&&ans[a[i].z]){
		for(;j<t&&c[j]<a[i].x;j++);
		ans[a[i].z]&=a[p[j]].up(a[i]);
	}
	inplace_merge(a+beg,a+mid,a+end);
}

int main(){
	scanf("%d",&n);
	bool any=0;
	for(int i=0;i<n;i++){
		int type; db x,y;
		scanf("%d%lf%lf",&type,&x,&y);
		if(!type){
			a[i].z=-1;
			a[i].x=.5/y;
			a[i].y=-x/y;
			any=1;
		}
		else{
			ans[m]=any;
			a[i].z=m++;
			a[i].x=x/(x*x+y*y);
			a[i].y=y/(x*x+y*y);
		}
	}
	work(0,n);
	for(int i=0;i<m;i++) puts(ans[i]?"Yes":"No");
}
