#include <cstdio>
const int N=(int)1e7+5;
int n,mo,val[N],inv[N],po[N];
int main(){
	scanf("%d%d",&n,&mo);
	val[1]=inv[1]=1;
	for(int i=2;i<=n;i++)
		if(i%mo)
			if(i<mo) val[i]=i,inv[i]=1LL*(mo-mo/i)*inv[mo%i]%mo;
			else val[i]=val[i-mo],inv[i]=inv[i-mo];
		else val[i]=val[i/mo],inv[i]=inv[i/mo],po[i]=po[i/mo]+1;
	long long now=1,cnt=0;
	int ans=1;
	for(int i=1;i<=n;i++){
		now=now*val[n-i+1]%mo*inv[i]%mo*2%mo;
		if(!(cnt+=po[n-i+1]-po[i])) ans^=now;
	}
	printf("%d\n",ans);
}
