#include <cstdio>
const int N=55;
typedef long long ll;
const ll P=10007;

int n;
ll c[N],h[P];
int ans;

const int B=1<<16;
int sum1[B];

inline int sum(ll x){
	return sum1[x>>48]+sum1[x>>32&B-1]+sum1[x>>16&B-1]+sum1[x&B-1];
}

void dfs(ll s,int cnt){
	if(cnt+sum(s)<ans) return;
	if(!s){
		if(cnt>ans) ans=cnt;
		return;
	}
	dfs(s&h[(s&-s)%P],cnt+1);
	dfs(s-(s&-s),cnt);
}

int main(){
	for(int i=0;i<B;i++) sum1[i]=sum1[i>>1]+(i&1);
	scanf("%d",&n);
	int a,b;
	while(scanf("%d%d",&a,&b)==2){
		a--; b--;
		c[a]|=1LL<<b;
		c[b]|=1LL<<a;
	}
	for(int i=0;i<n;i++){
		c[i]&=~(1LL<<i);
		h[(1LL<<i)%P]=c[i];
	}
	dfs((1LL<<n)-1,0);
	printf("%d\n",ans);
}
