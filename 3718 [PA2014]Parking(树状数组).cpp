#include <cstdio>
#include <cmath>
#include <algorithm>
using namespace std;
inline int getint(){
	char c;
	while((c=getchar())<'0'||c>'9'); int a=c-'0';
	while((c=getchar())>='0'&&c<='9') a=a*10+c-'0';
	return a;
}
const int N=50005;
int n,w,s[N];
struct car{
	int x,y,loc;
} a[N],*ord[N],*ord2[N];
inline bool cmp(const car *a,const car *b){
	return a->x<b->x;
}
bool work(){
	n=getint(),w=getint();
	for(int i=0;i<n;i++){
		int x1=getint(),y1=getint();
		a[i].x=min(x1,getint());
		a[i].y=abs(y1-getint());
		ord[i]=a+i;
	}
	sort(ord,ord+n,cmp);
	for(int i=0;i<n;i++){
		int x1=getint(),y1=getint();
		a[i].x=min(x1,getint());
		a[i].y=abs(y1-getint());
		ord2[i]=a+i;
	}
	sort(ord2,ord2+n,cmp);
	for(int i=0;i<n;i++) ord2[i]->loc=i;
	for(int i=1;i<=n;i++) s[i]=0;
	for(int i=n;i--;){
		for(int x=ord[i]->loc;x;x-=x&-x)
			if(s[x]+ord[i]->y>w) return 0;
		for(int x=ord[i]->loc+1;x<=n;x+=x&-x)
			if(s[x]<ord[i]->y) s[x]=ord[i]->y;
	}
	return 1;
}
int main(){
	int t=getint();
	while(t--)
		puts(work()?"TAK":"NIE");
}
