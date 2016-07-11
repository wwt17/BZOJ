int N,M,min,i,j;
long long cnt[100001],ans;
int main(){
	scanf("%u%u",&N,&M);
	min=N<M?N:M;
	for(i=min;i;i--){
		cnt[i]=(long long)(N/i)*(M/i);
		for(j=i<<1;j<=min;j+=i) cnt[i]-=cnt[j];
		ans+=i*cnt[i];
	}
	printf("%lld\n",(ans<<1)-(long long)N*M);
}
