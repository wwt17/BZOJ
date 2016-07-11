#include <cstdio>
#include <algorithm>
using namespace std;

const int N=12;

int n;
int a[N+1][1<<N];

long long ans=0;

bool check(int *a){
	return a[0]+1==a[1]&&(a[1]&1);
}

void dfs(int n,int cnt=0,int s=1){
	if(n==0){
		ans+=s;
		return;
	}
	int len=0,seq[2];
	for(int i=0;i<1<<n;i+=2) if(!check(a[n]+i)){
		if(len==2) return;
		seq[len++]=i;
	}
	if(len==0){
		for(int i=0;i<1<<n;i+=2) a[n-1][i>>1]=a[n][i]>>1;
		dfs(n-1,cnt,s);
	}
	else
	if(len==1){
		swap(a[n][seq[0]],a[n][seq[0]+1]);
		if(check(a[n]+seq[0])){
			for(int i=0;i<1<<n;i+=2) a[n-1][i>>1]=a[n][i]>>1;
			dfs(n-1,cnt+1,s*(cnt+1));
		}
	}
	else
	if(len==2){
		for(int x=0;x<=1;x++) for(int y=0;y<=1;y++){
			swap(a[n][seq[0]+x],a[n][seq[1]+y]);
			if(check(a[n]+seq[0])&&check(a[n]+seq[1])){
				for(int i=0;i<1<<n;i+=2) a[n-1][i>>1]=a[n][i]>>1;
				dfs(n-1,cnt+1,s*(cnt+1));
			}
			swap(a[n][seq[0]+x],a[n][seq[1]+y]);
		}
	}
}

int main(){
	scanf("%d",&n);
	for(int i=0;i<1<<n;i++) scanf("%d",&a[n][i]),a[n][i]--;
	dfs(n);
	printf("%lld\n",ans);
}
