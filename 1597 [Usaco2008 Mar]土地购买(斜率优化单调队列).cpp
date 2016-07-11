//f[i]=min{f[j]+x[i]*y[j+1]}
#include <cstdio>
#include <algorithm>
#include <queue>
using namespace std;
const int N=50005;
int n,st,ed;
long long f;
typedef pair<long long,long long> vec;
#define x first
#define y second
vec a[N],q[N];
#define calc(v,i) (v.x+a[i].x*v.y)
inline bool cross(vec &a,vec &b,vec &c){
	return (double)(b.y-a.y)/(b.x-a.x)>(double)(c.y-a.y)/(c.x-a.x);
}
int main(){
	scanf("%d",&n);
	for(int i=1;i<=n;i++) scanf("%lld%lld",&a[i].x,&a[i].y);
	sort(a+1,a+n+1);
	for(int i=1,j=0;i<=n;i++){
		for(;j&&a[j].x<=a[i].x&&a[j].y<=a[i].y;j--);
		a[++j]=a[i];
	}
	q[st=ed=1]=vec(0,a[1].y);
	for(int i=1;;i++){
		f=calc(q[st],i);
		while(ed-st+1>=2&&(f>calc(q[st+1],i))){
			++st;
			f=calc(q[st],i);
		}
		if(i==n) break;
		vec now(f,a[i+1].y);
		while(ed-st+1>=2&&cross(q[ed-1],q[ed],now)) ed--;
		q[++ed]=now;
	}
	printf("%lld\n",f);
}
