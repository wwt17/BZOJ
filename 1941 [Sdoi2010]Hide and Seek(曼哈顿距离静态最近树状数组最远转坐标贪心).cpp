#include <cstdio>
#include <algorithm>
using namespace std;
#define maxi(a,b) if(b>a) a=b
#define mini(a,b) if(b<a) a=b
const int N=500005,inf=(int)5e8;
struct data{
	int x,y,loc;
	bool operator < (const data &B) const{
		return x<B.x||x==B.x&&y<B.y;
	}
} a[N];
int n,m,ord[N];
int s[N],mi[N];
int main(){
	scanf("%d",&n);
	for(int i=1;i<=n;i++) scanf("%d%d",&a[i].x,&a[i].y),ord[i]=a[i].y;
	sort(ord+1,ord+n+1);
	m=unique(ord+1,ord+n+1)-ord-1;
	for(int i=1;i<=n;i++){
		a[i].loc=lower_bound(ord+1,ord+m+1,a[i].y)-ord;
		mi[i]=inf*4;
	}
	sort(a+1,a+n+1);
	for(int i=1;i<=m;i++) s[i]=inf*4;
	for(int i=1;i<=n;i++){
		int x=inf*4,d=inf-a[i].x+inf-a[i].y;
		for(int j=a[i].loc;j;j-=j&-j)
			mini(x,s[j]);
		mini(mi[i],x-d);
		for(int j=a[i].loc;j<=m;j+=j&-j)
			mini(s[j],d);
	}
	for(int i=1;i<=m;i++) s[i]=inf*4;
	for(int i=n;i>=1;i--){
		int x=inf*4,d=inf+a[i].x+inf-a[i].y;
		for(int j=a[i].loc;j;j-=j&-j)
			mini(x,s[j]);
		mini(mi[i],x-d);
		for(int j=a[i].loc;j<=m;j+=j&-j)
			mini(s[j],d);
	}
	for(int i=1;i<=n;i++) a[i].loc=m+1-a[i].loc;
	for(int i=1;i<=m;i++) s[i]=inf*4;
	for(int i=1;i<=n;i++){
		int x=inf*4,d=inf-a[i].x+inf+a[i].y;
		for(int j=a[i].loc;j;j-=j&-j)
			mini(x,s[j]);
		mini(mi[i],x-d);
		for(int j=a[i].loc;j<=m;j+=j&-j)
			mini(s[j],d);
	}
	for(int i=1;i<=m;i++) s[i]=inf*4;
	for(int i=n;i>=1;i--){
		int x=inf*4,d=inf+a[i].x+inf+a[i].y;
		for(int j=a[i].loc;j;j-=j&-j)
			mini(x,s[j]);
		mini(mi[i],x-d);
		for(int j=a[i].loc;j<=m;j+=j&-j)
			mini(s[j],d);
	}
	int x0=inf,x1=-inf,y0=inf,y1=-inf;
	for(int i=1;i<=n;i++){
		int x=a[i].x+a[i].y,y=a[i].x-a[i].y;
		a[i].x=x,a[i].y=y;
		mini(x0,x);
		maxi(x1,x);
		mini(y0,y);
		maxi(y1,y);
	}
	int ans=inf*4;
	for(int i=1;i<=n;i++)
		mini(ans,max(max(a[i].x-x0,x1-a[i].x),max(a[i].y-y0,y1-a[i].y))-mi[i]);
	printf("%d\n",ans);
}
