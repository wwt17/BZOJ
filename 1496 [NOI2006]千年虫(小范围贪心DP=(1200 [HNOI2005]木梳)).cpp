#include <cstdio>
#include <algorithm>
using namespace std;
typedef long long ll;
const int N=1000005,S=100;
const ll inf=(ll)1e18;
int n,a[N],b[N],T;
void mini(ll &a,const ll b){
	if(b<a) a=b;
}
struct line{
	int s,v[S];
	ll f[S][2];
	void getv(int i){
		s=0;
		for(int j=i-2;j<=i+2;j++) if(j>0&&j<=n){
			if(a[j]-1<=a[i]) v[s++]=a[j]-1;
			if(a[j]  <=a[i]) v[s++]=a[j];
			if(a[j]+1<=a[i]) v[s++]=a[j]+1;
		}
		sort(v,v+s);
		s=unique(v,v+s)-v;
	}
} t[2];
ll calc(){
	t[T].s=1;
	t[T].v[0]=-100;
	t[T].f[0][0]=0;
	t[T].f[0][1]=inf;
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
		mini(ans,t[T].f[j][1]);
	return ans;
}
int main(){
	scanf("%d",&n);
	for(int i=1;i<=n;i++) scanf("%d%d",&a[i],&b[i]),a[i]--;
	ll ans=calc();
	for(int i=1;i<=n;i++) a[i]=1000000-b[i];
	ans+=calc();
	printf("%lld\n",ans);
}
