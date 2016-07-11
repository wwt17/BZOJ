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
int s[N],t[N],mi[N],ma[N];
int main(){
	scanf("%d",&n);
	for(int i=1;i<=n;i++) scanf("%d%d",&a[i].x,&a[i].y),ord[i]=a[i].y;
	sort(ord+1,ord+n+1);
	m=unique(ord+1,ord+n+1)-ord-1;
	for(int i=1;i<=n;i++){
		a[i].loc=lower_bound(ord+1,ord+m+1,a[i].y)-ord;
		mi[i]=inf*4;
		ma[i]=0;
	}
	sort(a+1,a+n+1);
	for(int i=1;i<=m;i++) s[i]=inf*4,t[i]=0;
	for(int i=1;i<=n;i++){
		int x=inf*4,y=0,d=inf+a[i].x+inf+a[i].y;
		for(int j=a[i].loc;j;j-=j&-j){
			mini(x,s[j]);
			maxi(y,t[j]);
		}
		mini(mi[i],d-y);
		maxi(ma[i],d-x);
		for(int j=a[i].loc;j<=m;j+=j&-j){
			mini(s[j],d);
			maxi(t[j],d);
		}
	}
	for(int i=1;i<=m;i++) s[i]=inf*4,t[i]=0;
	for(int i=n;i>=1;i--){
		int x=inf*4,y=0,d=inf-a[i].x+inf+a[i].y;
		for(int j=a[i].loc;j;j-=j&-j){
			mini(x,s[j]);
			maxi(y,t[j]);
		}
		mini(mi[i],d-y);
		maxi(ma[i],d-x);
		for(int j=a[i].loc;j<=m;j+=j&-j){
			mini(s[j],d);
			maxi(t[j],d);
		}
	}
	for(int i=1;i<=n;i++) a[i].loc=m+1-a[i].loc;
	for(int i=1;i<=m;i++) s[i]=inf*4,t[i]=0;
	for(int i=1;i<=n;i++){
		int x=inf*4,y=0,d=inf+a[i].x+inf-a[i].y;
		for(int j=a[i].loc;j;j-=j&-j){
			mini(x,s[j]);
			maxi(y,t[j]);
		}
		mini(mi[i],d-y);
		maxi(ma[i],d-x);
		for(int j=a[i].loc;j<=m;j+=j&-j){
			mini(s[j],d);
			maxi(t[j],d);
		}
	}
	for(int i=1;i<=m;i++) s[i]=inf*4,t[i]=0;
	for(int i=n;i>=1;i--){
		int x=inf*4,y=0,d=inf-a[i].x+inf-a[i].y;
		for(int j=a[i].loc;j;j-=j&-j){
			mini(x,s[j]);
			maxi(y,t[j]);
		}
		mini(mi[i],d-y);
		maxi(ma[i],d-x);
		for(int j=a[i].loc;j<=m;j+=j&-j){
			mini(s[j],d);
			maxi(t[j],d);
		}
	}
	int ans=inf*4;
	for(int i=1;i<=n;i++)
		mini(ans,ma[i]-mi[i]);
	printf("%d\n",ans);
	scanf("\n");
}
