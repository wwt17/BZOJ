#include <cstdio>
#include <cstdlib>
#include <algorithm>
using namespace std;
const int N=55;

int n,ans,a[N],id[N];
bool cmp(const int i,const int j){
	return a[i]<a[j];
}

void dfs(int step,int cnt){
	if(step+cnt>=ans) return;
	if(!cnt&&a[1]==1){
		ans=step;
		return;
	}
	for(int i=2;i<=n;i++){
		int c=cnt;
		c-=i<n&&abs(a[i]-a[i+1])!=1;
		reverse(a+1,a+i+1);
		c+=i<n&&abs(a[i]-a[i+1])!=1;
		dfs(step+1,c);
		reverse(a+1,a+i+1);
	}
}

int main(){
	scanf("%d",&n);
	for(int i=1;i<=n;i++) scanf("%d",&a[i]),id[i]=i;
	sort(id+1,id+n+1,cmp);
	for(int i=1;i<=n;i++) a[id[i]]=i;
	ans=n*2;
	int cnt=0;
	for(int i=1;i<n;i++) cnt+=abs(a[i]-a[i+1])!=1;
	dfs(0,cnt);
	printf("%d\n",ans);
}
