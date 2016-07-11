#include <cstdio>
#include <algorithm>
using namespace std;
const int N=100005;
int n,t,ans;
long long a[N],f[N];
int main(){
	scanf("%d%d",&n,&t);
	for(int i=1;i<=n;i++){
		int b,k; scanf("%d%d",&b,&k);
		a[i]=-(1LL*k*t+b);
	}
	for(int i=1;i<=n;i++)
		*upper_bound(f+1,f+n+1,a[i])=a[i];
	for(ans=1;f[ans];ans++);
	printf("%d\n",ans-1);
}
