#define N 10000001
char begin;
int n,i,j,k,prime[N>>1],primes,p[N],phi[N];
long long Ans,s[N];
char end;
int main(){
	scanf("%u",&n);
	p[1]=phi[1]=1;
	for(i=2;i<=n;i++){
		if(!p[i]) prime[primes++]=p[i]=i,phi[i]=i-1;
		for(j=0;j<primes&&(k=prime[j]*i)<=n;j++){
			p[k]=prime[j];
			if(prime[j]==p[i]){ phi[k]=prime[j]*phi[i]; break; }
			phi[k]=(prime[j]-1)*phi[i];
		}
		s[i]=s[i-1]+phi[i];
	}
	for(j=0;j<primes;j++)
		Ans+=s[n/prime[j]]<<1|1;
	printf("%llu\n",Ans);
}
