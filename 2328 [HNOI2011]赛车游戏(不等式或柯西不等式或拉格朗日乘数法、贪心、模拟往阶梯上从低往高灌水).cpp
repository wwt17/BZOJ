//如果没有各种限制，那么可以用不等式或柯西不等式或拉格朗日乘数法证明所有v相同时最优。对于下坡，v应有一个初值v0。按v0排序后贪心，把速度最小的那些速度提升，相当于模拟在一个阶梯上从低到高灌水的过程
#include <cstdio>
#include <cmath>
#include <algorithm>
using namespace std;
typedef double db;
#define y1 y1_
const db oo=1./0,eps=1e-10L;

const int N=10005;
int n;
db a,b,vmax,f;
struct data{
	db s,d,v0;
} q[N];
bool cmp(const data &a,const data &b){
	return a.v0<b.v0;
}
db delta[N];

void work(){
	scanf("%lf%lf%lf%lf",&a,&b,&vmax,&f);
	scanf("%d",&n);
	for(int i=1;i<=n;i++){
		db x,y; scanf("%lf%lf",&x,&y);
		q[i].s=y/x;
		q[i].d=sqrt(x*x+y*y)/1000;
		x/=1000;
		y/=1000;
		q[i].v0=min(vmax,max(0.,-b*q[i].s/a));
		f-=q[i].d*max(0.,a*q[i].v0+b*q[i].s);
	}
	if(f<-eps){
		puts("IMPOSSIBLE");
		return;
	}
	sort(q+1,q+n+1,cmp);
	db sum=0;
	for(int i=0;i<=n;i++) delta[i]=0;
	for(int i=1;i<=n;i++){
		sum+=q[i].d*a;
		db bnd=min(vmax,i<n?q[i+1].v0:oo);
		if((bnd-q[i].v0)*sum<=f){
			f-=(bnd-q[i].v0)*sum;
			delta[i]=(bnd-q[i].v0);
		}
		else{
			delta[i]=f/sum;
			f=0;
			break;
		}
	}
	db ans=0;
	for(int i=n;i;i--){
		if(q[i].v0+delta[i]<=eps){
			puts("IMPOSSIBLE");
			return;
		}
		ans+=q[i].d/(q[i].v0+delta[i]);
		delta[i-1]+=delta[i];
	}
	printf("%.5lf\n",ans);
}

int main(){
	int T; scanf("%d",&T);
	while(T--)
		work();
}
