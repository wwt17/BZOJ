#include <cstdio>
#include <algorithm>
using namespace std;
const int N=50001;
int n,a,b,c,d,k,p[N],miu[N],sum[N],prime[N],primes;
void Mobius(){
	miu[1]=1;
	for(int i=2;i<N;i++){
		if(!p[i]){
			p[i]=prime[primes++]=i;
			miu[i]=-1;
		}
		for(int j=0;j<primes&&i*prime[j]<N&&prime[j]<=p[i];j++){
			p[i*prime[j]]=prime[j];
			miu[i*prime[j]]=prime[j]==p[i]?0:-miu[i];
		}
	}
	for(int i=1;i<N;i++) sum[i]=sum[i-1]+miu[i];
}
long long calc(int a,int b){
	if(a>b) swap(a,b);
	long long ans=0;
	for(int i=1,j;i<=a;i=j+1){
		j=min(a/(a/i),b/(b/i));
		ans+=(long long)(sum[j]-sum[i-1])*(a/i)*(b/i);
	}
	return ans;
}
int main(){
	Mobius();
	scanf("%d",&n);
	while(n--){
		scanf("%d%d%d%d%d",&a,&b,&c,&d,&k); a--,c--;
		a/=k,b/=k,c/=k,d/=k;
		printf("%lld\n",calc(a,c)-calc(a,d)-calc(b,c)+calc(b,d));
	}
}
