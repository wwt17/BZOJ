#include <cstdio>
#include <algorithm>
using namespace std;
typedef pair<int,int> pii;
const int N=(int)1e5+5;

bool cmp(const pii &a,const pii &b){
	return a.first*b.second<b.first*a.second;
}

int n;
pii a[N];

int main(){
	scanf("%d",&n);
	for(int i=0;i<n;i++) scanf("%d",&a[i].first);
	for(int i=0;i<n;i++) scanf("%d",&a[i].second);
	sort(a,a+n,cmp);
	int t=0;
	long long ans=0;
	for(int i=0;i<n;i++){
		t+=a[i].first;
		ans+=1LL*t*a[i].second;
	}
	printf("%lld\n",ans);
}
