#include <cstdio>
const int N=40005,inf=N*200;
long long ans;
int n,a[N],last[N],next[N];
#define link(a,b) (next[a]=b,last[b]=a)
int main(){
	scanf("%d",&n);
	a[0]=inf;
	for(int i=1;i<=n;i++){
		scanf("%d",a+i);
		link(last[0],i);
		link(i,0);
	}
	for(int t=n,k=next[0];t>1;t--){
		for(;;k=next[k]) if(a[last[k]]<=a[next[k]]){
			int x=k;
			ans+=a[k]+=a[last[k]];
			link(last[last[k]],next[k]);
			for(k=next[k];a[last[k]]<=a[x];k=last[k]);
			link(last[k],x);
			link(x,k);
			k=x;
			if(last[k]) k=last[k];
			break;
		}
	}
	printf("%lld\n",ans);
}
