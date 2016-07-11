#include <cstdio>
#include <queue>
using namespace std;

int n;

int Main(){
	scanf("%d",&n);
	priority_queue<int> q;
	int ans=0,now=1;
	for(int i=1;i<=n;i++){
		int x; scanf("%d",&x);
		if(ans==-1) continue;
		if(now)
			--now;
		else
			if(q.empty()){
				ans=-1;
				continue;
			}
		else
			now=q.top()-1,q.pop(),ans++;
		if(x-1) q.push(x-1);
	}
	return ans;
}

int main(){
	int T; scanf("%d",&T);
	while(T--)
		printf("%d\n",Main());
}
