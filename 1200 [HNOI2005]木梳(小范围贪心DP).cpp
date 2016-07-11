#include <cstdio>
#include <algorithm>
using namespace std;
typedef long long ll;
const int N=100005,S=100;
const ll inf=(ll)1e18;
int n,a[N],T;
void mini(ll &a,const ll b){
	if(b<a) a=b;
}
struct line{
	int s,v[S];
	ll f[S][2];
	void getv(int i){
		s=0;
		for(int j=i-2;j<=i+2;j++) if(j>0&&j<=n){
			if(a[j]-1>0&&a[j]-1<=a[i]) v[s++]=a[j]-1;
			if(a[j]  >0&&a[j]  <=a[i]) v[s++]=a[j];
			if(a[j]+1>0&&a[j]+1<=a[i]) v[s++]=a[j]+1;
		}
		sort(v,v+s);
		s=unique(v,v+s)-v;
	}
} t[2];
int main(){
	scanf("%d",&n);
	for(int i=1;i<=n;i++) scanf("%d",&a[i]);
	a[0]=0x7fffffff;
	t[T].getv(0);
	for(int i=1;i<=n;i++){
		t[!T].getv(i);
		for(int j=0;j<t[!T].s;j++){
			t[!T].f[j][0]=t[!T].f[j][1]=inf;
			for(int jj=0;jj<t[T].s;jj++)
				if(t[T].v[jj]<t[!T].v[j])
					mini(t[!T].f[j][1],t[T].f[jj][0]);
				else
				if(t[T].v[jj]>t[!T].v[j])
					mini(t[!T].f[j][0],t[T].f[jj][1]);
				else
					mini(t[!T].f[j][0],t[T].f[jj][0]),
					mini(t[!T].f[j][1],t[T].f[jj][1]);
			t[!T].f[j][0]+=a[i]-t[!T].v[j];
			t[!T].f[j][1]+=a[i]-t[!T].v[j];
		}
		T^=1;
	}
	ll ans=inf;
	for(int j=0;j<t[T].s;j++)
		mini(ans,t[T].f[j][0]),
		mini(ans,t[T].f[j][1]);
	printf("%lld\n",ans);
}
