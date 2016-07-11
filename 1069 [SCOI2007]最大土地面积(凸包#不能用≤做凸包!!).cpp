#include <cstdio>
#include <algorithm>
using namespace std;
const int N=2005;
int n,next[N];
struct vec{
	double x,y;
	void read(){
		scanf("%lf%lf",&x,&y);
	}
} a[N],s[N];
int m;
inline bool cmpx(const vec a,const vec b){
	return a.x<b.x;
}
inline double cross(vec &a,vec &b,vec &c){
	return (b.x-a.x)*(c.y-a.y)-(c.x-a.x)*(b.y-a.y);
}
void push(vec p){
	while(m>=2&&cross(s[m-2],s[m-1],p)<=0) m--;
	s[m++]=p;
}
int main(){
	scanf("%d",&n);
	for(int i=0;i<n;i++) a[i].read();
	sort(a,a+n,cmpx);
	for(int i=0;i<n-1;i++) push(a[i]);
	for(int i=n-1;i>=0;i--) push(a[i]);
	m--;
	if(m<4) return printf("%.3lf\n",0.),0;
	for(int i=0;i<m-1;i++) next[i]=i+1;
	next[m-1]=0;
	double ans=0;
	for(int a=0;a<m;a++){
		int i=next[a],j=next[a];
		for(int b=a+1;b<m;b++){
			while(cross(s[a],s[b],s[i])>cross(s[a],s[b],s[next[i]])) i=next[i];
			while(cross(s[a],s[b],s[j])<cross(s[a],s[b],s[next[j]])) j=next[j];
			ans=max(ans,cross(s[a],s[b],s[j])-cross(s[a],s[b],s[i]));
		}
	}
	printf("%.3lf\n",ans/2);
}
