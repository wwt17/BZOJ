#include <cstdio>
#include <cstdlib>
#include <algorithm>
using namespace std;
const int N=100001;
const long long inf=0x7ffffffffffLL;
int n,a[N],b[N];
long long f[N];
#define P(x,y) (a[x]==b[y]?inf:abs(a[x]-b[y]))
int main(){
	scanf("%d",&n);
	for(int i=1;i<=n;i++) scanf("%d%d",a+i,b+i);
	sort(a+1,a+n+1);
	sort(b+1,b+n+1);
	f[1]=P(1,1);
	f[2]=min(f[1]+P(2,2),(long long)(P(1,2)+P(2,1)));
	for(int i=3;i<=n;i++)
		f[i]=min(f[i-1]+P(i,i),
			min(f[i-2]+P(i-1,i)+P(i,i-1),
				f[i-3]+min(P(i-2,i)+P(i-1,i-2)+P(i,i-1),
					P(i-2,i-1)+P(i-1,i)+P(i,i-2))));
	f[n]>=inf?puts("-1"):printf("%lld\n",f[n]);
}
