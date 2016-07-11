#include <cstdio>
#include <cmath>
#include <algorithm>
using namespace std;
typedef double db;
long long ans,X,Y;
const int N=3005;
const db pi=acos(-1);
const int rest[2]={0,5};
int n,m;
struct vec{
	int x,y;
	db a;
} a[N],b[N*2];
bool cmpa(const vec &a,const vec &b){
	return a.a<b.a;
}
int main(){
	scanf("%d",&n);
	for(int i=0;i<n;i++)
		scanf("%d%d",&a[i].x,&a[i].y);
	for(int i=0;i<n;i++){
		m=0;
		for(int j=i+1;j<n;j++){
			b[m].x=a[j].x-a[i].x;
			b[m].y=a[j].y-a[i].y;
			b[m].a=atan2(b[m].y,b[m].x);
			m++;
		}
		sort(b,b+m,cmpa);
		for(int j=0;j<m;j++) b[m+j]=b[j],b[m+j].a+=2*pi;
		X=Y=0;
		for(int j=0,k=0;j<m;j++){
			for(;k<m*2&&b[k].a<b[j].a+pi;k++)
				X+=b[k].y,Y-=b[k].x;
			ans+=b[j].x*X+b[j].y*Y;
			X-=b[j].y,Y+=b[j].x;
		}
	}
	printf("%lld.%d\n",ans/2,rest[ans%2]);
}
