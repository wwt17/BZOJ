#include <cstdio>
#include <cstdlib>
#include <algorithm>
using namespace std;
typedef long long ll;
const int N=100005;
int n;
ll x,ans,a[N],d[N];
int main(){
	scanf("%d",&n);
	for(int i=0;i<n;i++){
		scanf("%lld",&a[i]);
		x+=a[i];
	}
	x/=n;
	for(int i=1;i<n;i++){
		d[i]=d[i-1]+a[i-1]-x;
	}
	nth_element(d,d+n/2,d+n);
	for(int i=0;i<n;i++) ans+=abs(d[i]-d[n/2]);
	printf("%lld\n",ans);
}
