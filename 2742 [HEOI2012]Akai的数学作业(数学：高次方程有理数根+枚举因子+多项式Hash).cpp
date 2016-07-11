#include <cstdio>
#include <cstdlib>
#include <algorithm>
using namespace std;
typedef pair<int,int> pii;
const int N=105,mos=3,mo[mos]={9999973,9999991,10000019};
int n,a0,an,a[N],b[N],c[N],t;
pii ans[N];
int gcd(const int a,const int b){
	return b?gcd(b,a%b):a;
}
inline bool cmp(const pii &a,const pii &b){
	return 1LL*a.first*b.second<1LL*b.first*a.second;
}
void work(int x,int y){
	for(int m=0;m<mos;m++){
		b[0]=1;
		for(int i=1;i<=n;i++) b[i]=1LL*b[i-1]*x%mo[m];
		c[n]=1;
		for(int i=n-1;i>=0;i--) c[i]=1LL*c[i+1]*y%mo[m];
		long long now=0;
		for(int i=0;i<=n;i++) (now+=1LL*a[i]%mo[m]*b[i]%mo[m]*c[i])%=mo[m];
		if(now) return;
	}
	ans[t++]=pii(x,y);
}
void check(int x,int y){
	if(gcd(x,y)!=1) return;
	work(x,y);
	work(-x,y);
}
int main(){
	scanf("%d",&n);
	for(int i=0;i<=n;i++) scanf("%d",&a[i]);
	for(int i=0;i<=n;i++) if(a[i]){
		a0=abs(a[i]);
		break;
	}
	an=abs(a[n]);
	work(0,1);
	for(int x=1;x*x<=a0;x++) if(a0%x==0)
		for(int y=1;y*y<=an;y++) if(an%y==0){
			check(x,y);
			if(y*y!=an) check(x,an/y);
			if(x*x!=a0){
				check(a0/x,y);
				if(y*y!=an)
					check(a0/x,an/y);
			}
		}
	sort(ans,ans+t,cmp);
	printf("%d\n",t);
	for(int i=0;i<t;i++)
		if(ans[i].second==1)
			printf("%d\n",ans[i].first);
		else
			printf("%d/%d\n",ans[i].first,ans[i].second);
}
