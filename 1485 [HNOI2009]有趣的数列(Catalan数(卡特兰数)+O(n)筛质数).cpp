#include <cstdio>
typedef long long ll;
const int N=1000005;
int n,mo,prime[N*2],p[N*2],cnt[N*2];
void init(){
	for(int i=2;i<=n*2;i++){
		if(!p[i]) p[i]=prime[++*prime]=i;
		for(int j=1;j<=*prime&&i*prime[j]<=n*2&&prime[j]<=p[i];j++)
			p[i*prime[j]]=prime[j];
	}
}
int main(){
	scanf("%d%d",&n,&mo);
	init();
	for(int i=2*n;i>n+1;i--) cnt[i]++;
	for(int i=2;i<=n;i++) cnt[i]--;
	ll ans=1;
	for(int i=2*n;i>1;i--)
		if(i==p[i]){
			while(cnt[i]){
				cnt[i]--;
				(ans*=i)%=mo;
			}
		}
		else{
			cnt[p[i]]+=cnt[i];
			cnt[i/p[i]]+=cnt[i];
		}
	printf("%d\n",int(ans));
}
