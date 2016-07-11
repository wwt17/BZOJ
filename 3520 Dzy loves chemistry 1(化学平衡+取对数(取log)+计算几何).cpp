#include <cstdio>
#include <cmath>
#include <algorithm>
using namespace std;
typedef double db;
const int N=1005;
int n,m,ans;
db s[N],t[N];
int main(){
	scanf("%d",&n);
	n--;
	for(int i=1;i<=n;i++){
		scanf("%lf",&s[i]);
		s[i]=s[i-1]+log(s[i]);
	}
	for(int i=0;i<=n;i++){
		m=0;
		for(int j=i+1;j<=n;j++) if(j!=i)
			t[m++]=(s[j]-s[i])/(j-i);
		sort(t,t+m);
		for(int j=0,jj;j<m;j=jj){
			for(jj=j+1;jj<m&&abs(t[jj]-t[jj-1])<1e-12;jj++);
			if(jj-j>ans) ans=jj-j;
		}
	}
	printf("%d\n",ans+1);
}
