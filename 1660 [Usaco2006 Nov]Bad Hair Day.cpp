#include <cstdio>
#include <algorithm>
#include <functional>
using namespace std;
int main() {
	int N,hi;
	scanf("%d",&N);
	int s[N+1],top=0;
	long long ans=0;
	while (N--) {
		scanf("%d",&hi);
		top=lower_bound(s+1,s+top+1,hi,greater<int>())-s;
		ans+=top-1;
		s[top]=hi;
	}
	printf("%I64d\n",ans);
	system("pause");
}
