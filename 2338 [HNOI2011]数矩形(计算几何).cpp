#include <cstdio>
#include <algorithm>
using namespace std;
typedef long long ll;
const int N=1505;
int n;
inline ll sqr(ll x){
	return x*x;
}
inline ll absll(ll x){
	return x<0?-x:x;
}
struct vec{
	int x,y;
} a[N];
inline ll cross(const vec a,const vec b,const vec c){
	return (ll)(b.x-a.x)*(c.y-a.y)-(ll)(c.x-a.x)*(b.y-a.y);
}
struct data{
	int u,v,x,y; ll len;
	bool operator < (const data &b) const{
		return x<b.x||x==b.x&&(y<b.y||y==b.y&&len<b.len);
	}
	bool operator == (const data &b) const{
		return x==b.x&&y==b.y&&len==b.len;
	}
} s[N*N],*newd=s;
int main(){
	scanf("%d",&n);
	for(int i=0;i<n;i++) scanf("%d%d",&a[i].x,&a[i].y);
	for(int i=0;i<n;i++)
		for(int j=i+1;j<n;j++)
			*newd++=(data){i,j,a[i].x+a[j].x,a[i].y+a[j].y,sqr(a[i].x-a[j].x)+sqr(a[i].y-a[j].y)};
	sort(s,newd);
	ll ans=0;
	for(data *i=s;i<newd;i++)
		for(data *j=i+1;j<newd&&*i==*j;j++)
			ans=max(ans,absll(cross(a[i->u],a[j->u],a[j->v])));
	printf("%lld\n",ans);
}
