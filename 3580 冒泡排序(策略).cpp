#include <cstdio>
#include <algorithm>
using namespace std;

const int N=6;

int n,i,j,a[N*2],b[N*2],t[N],cnt[N];
bool flag[N];
long long k;

void add(int x){
	for(x=n+1-x;x<=n;x+=x&-x) t[x]++;
}
int query(int x){
	int ans=0;
	for(x=n+1-x;x;x-=x&-x) ans+=t[x];
	return ans;
}

int main(){
	scanf("%d%lld",&n,&k);
	for(i=1;i<=n;i++){
		scanf("%d",&a[i]);
		b[i]=query(a[i]);
		add(a[i]);
		cnt[b[i]]++;
	}
	int sum=0;
	for(j=0;j<n;j++){
		sum+=cnt[j];
		if(k<=n-sum) break;
		k-=n-sum;
	}
	if(j==n&&k){
		puts("Impossible!");
		return 0;
	}
	for(i=1;i<=n;i++) if(b[i]<=j) flag[a[i]]=1;
	int p=0;
	for(i=j+1;i<=n+j;i++) if(b[i]<=j){
		while(!flag[p]) p++;
		a[i]=p;
		flag[p]=false;
	}
	for(i=j+1;i<=n-1;i++)
		if(a[i]>a[i+1]){
			swap(a[i],a[i+1]);
			if(!--k) break;
		}
	for(i=1;i<=n;i++) printf("%d%c",a[j+i],i<n?' ':'\n');
}
