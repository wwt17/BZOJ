#include <cstdio>
#include <algorithm>
using namespace std;
typedef long long ll;
struct vec{
	int x,y;
	ll z;
};
const int N=5005;
int n,ans;
ll A,B,C;
vec a[N],b[N],c[N];
bool cmpx(const vec a,const vec b){
	return a.x<b.x;
}
bool cmpy(const vec a,const vec b){
	return a.y<b.y;
}
bool cmpz(const vec a,const vec b){
	return a.z<b.z;
}
int main(){
	scanf("%d%lld%lld%lld",&n,&A,&B,&C);
	for(int i=0;i<n;i++){
		scanf("%d%d",&a[i].x,&a[i].y);
		a[i].z=A*a[i].x+B*a[i].y;
		b[i]=c[i]=a[i];
	}
	sort(a,a+n,cmpx);
	sort(b,b+n,cmpy);
	sort(c,c+n,cmpz);
	for(vec *i=a;i<a+n;i++) if(i==a||i->x!=(i-1)->x){
		int now=0;
		for(vec *j=b,*jj=j,*k=c;j<b+n;j=jj){
			ll t=A*i->x+B*j->y+C;
			for(;k<c+n&&k->z<=t;k++)
				if(k->x>=i->x&&k->y>=j->y)
					now++;
			if(now>ans) ans=now;
			for(;jj<b+n&&j->y==jj->y;jj++)
				if(jj->x>=i->x&&jj->z<=t)
					now--;
		}
	}
	printf("%d\n",ans);
}
