#include <cstdio>
#include <algorithm>
#include <functional>
using namespace std;
#define size 50001
int N,i,h[size],v[size],f[size],s[size],top,ans;
struct cmp {
	bool operator () (const int a,const int b) {
		return h[a]>h[b];
	}
};
int main() {
	scanf("%d",&N);
	for (i=1;i<=N;++i) scanf("%d%d",&h[i],&v[i]);
	top=0;
	for (i=1;i<=N;++i) {
		s[top=lower_bound(s+1,s+top+1,i,cmp())-s]=i;
		f[s[top-1]]+=v[i];
	}
	top=0;
	for (i=N;i;--i) {
		s[top=lower_bound(s+1,s+top+1,i,cmp())-s]=i;
		f[s[top-1]]+=v[i];;
	}
	for (i=1;i<=N;++i) ans=max(ans,f[i]);
	printf("%d\n",ans);
	system("pause");
}
