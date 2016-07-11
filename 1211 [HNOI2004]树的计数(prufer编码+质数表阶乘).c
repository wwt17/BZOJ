#define N 150
int n,s,d,p[N],prime[N],primes,cnt[N];
long long ans=1;
int main(){
	int i,j,k;
	scanf("%d",&n);
	p[1]=1;
	for(i=2;i<=n-2;i++){
		if(!p[i]) p[i]=prime[primes++]=i;
		for(j=0;j<primes&&prime[j]<=p[i]&&i*prime[j]<=n-2;j++)
			p[i*prime[j]]=prime[j];
		for(j=i;j>1;j/=p[j]) cnt[p[j]]++;
	}
	for(i=0;i<n;i++){
		scanf("%d",&d);
		if(d>n-1) goto fail;
		s+=d;
		for(k=2;k<=d-1;k++)
			for(j=k;j>1;j/=p[j]) if(!cnt[p[j]]--)
				goto fail;
	}
	if(s!=(n-1)*2) goto fail;
	for(j=0;j<primes;j++)
		while(cnt[prime[j]]--)
			ans*=prime[j];
	printf("%lld\n",ans);
	return 0;
	fail:
	puts("0");
}
