#include <cstdio>
#include <cmath>
#include <algorithm>
using namespace std;
typedef double db;
const db eps=1e-7,inf=1./0;
inline db fix(db x){
	return abs(x)<eps?0:x;
}
const int N=25,M=32;
int n;
db dis;
db k,b;
typedef pair<db,int> data;
data ord[N*M*5],*ordtop;
db tmp[N*M*5],*tmptop;
void cover(){
	for(db *p=tmp;p<tmptop;p++)
		*ordtop++=data(*p,(p-tmp)&1?-1:1);
}
struct vec{
	db x,y;
	vec(db _x=0,db _y=0):x(_x),y(_y){
	}
	friend vec operator + (const vec &a,const vec &b){
		return vec(a.x+b.x,a.y+b.y);
	}
	friend vec operator - (const vec &a,const vec &b){
		return vec(a.x-b.x,a.y-b.y);
	}
	void operator *= (const db t){
		x*=t; y*=t;
	}
	void operator /= (const db t){
		x/=t; y/=t;
	}
	db abs(){
		return sqrt(x*x+y*y);
	}
	db calc(){
		return fix(y-(k*x+b));
	}
	void work(){
		db A=1+k*k,B=-x+k*(b-y),C=x*x+(b-y)*(b-y)-dis*dis;
		tmptop=tmp+2;
		db delta=fix(B*B-A*C);
		if(delta<=0) return;
		tmp[0]=(-B-sqrt(delta))/A;
		tmp[1]=(-B+sqrt(delta))/A;
		cover();
	}
};
inline vec getvec(){
	const vec d(1-1e-7,1e-7);
	double x,y;
	scanf("%lf%lf",&x,&y);
	return vec(x*d.x-y*d.y,x*d.y+y*d.x);
}
struct poly{
	int m;
	vec a[M];
	void read(){
		scanf("%d",&m);
		for(int i=0;i<m;i++) a[i]=getvec();
		a[m]=a[0];
	}
	void work(){
		tmptop=tmp;
		for(int j=0;j<m;j++){
			db u=a[j].calc(),v=a[j+1].calc();
			db kk=(a[j+1].y-a[j].y)/(a[j+1].x-a[j].x),bb=a[j].y-kk*a[j].x;
			db xx=(bb-b)/(k-kk);
			if(u<0&&v>0||u>0&&v<0)
				*tmptop++=xx;
			else
			if(u==0){
				db w=a[(j?j:m)-1].calc();
				if(w<0){
					if(v>=0)
						*tmptop++=a[j].x;
				}
				else
				if(w>0){
					if(v<=0)
						*tmptop++=a[j].x;
				}
				else{
					if(v!=0)
						*tmptop++=a[j].x;
				}
			}
		}
		sort(tmp,tmptop);
		cover();
	}
	void doit(){
		work();
		static poly rect;
		for(int j=0;j<m;j++){
			a[j].work();
			rect.m=4;
			vec ddd=a[j+1]-a[j],d(-ddd.y,ddd.x);
			d/=d.abs();
			d*=dis;
			rect.a[0]=a[j]+d;
			rect.a[1]=a[j+1]+d;
			rect.a[2]=a[j+1]-d;
			rect.a[3]=a[j]-d;
			rect.a[4]=rect.a[0];
			rect.work();
		}
	}
};

poly a[N],aa;
bool check(){
	for(int j=0;j+1<aa.m;j++){
		k=(aa.a[j+1].y-aa.a[j].y)/(aa.a[j+1].x-aa.a[j].x);
		b=aa.a[j].y-k*aa.a[j].x;
		ordtop=ord;
		*ordtop++=data(-inf,0);
		*ordtop++=data(+inf,0);
		for(int i=0;i<n;i++) a[i].doit();
		sort(ord,ordtop);
		int cov=0;
		db x0=aa.a[j].x,x1=aa.a[j+1].x;
		if(x0>x1) swap(x0,x1);
		for(data *p=ord;p+1<ordtop;p++){
			cov+=p->second;
			if(!cov){
				if(min(x1,p[1].first)-max(x0,p[0].first)>eps)
					return 1;
			}
		}
	}
	return 0;
}
int main(){
	scanf("%d",&n);
	aa.read();
	for(int i=0;i<n;i++) a[i].read();
	db l=0,r=3e4;
	while(r-l>2e-3){
		dis=(l+r)/2;
		if(check())
			l=dis;
		else
			r=dis;
	}
	printf("%.2lf\n",(l+r)/2);
}
