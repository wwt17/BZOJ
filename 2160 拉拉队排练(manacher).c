#define N 1000010
#define P 19930726
#define ll unsigned long long
char s[N]; int n,rad[N],cnt[N],Ans; ll K,sum;
inline unsigned power(unsigned a,ll b){
	ll ans=1;
	for(;b;b>>=1){
		if(b&1) ans=ans*a%P;
		a=(ll)a*a%P;
	}
	return ans;
}
main(){
	scanf("%u%llu",&n,&K);
	int i,k;
	s[0]='@';
	scanf("%s",s+1);
	#define min(a,b) a<b?a:b
	#define max(a,b) a>b?a:b
	for(i=1;i<=n;i+=k){
		while(s[i-rad[i]-1]==s[i+rad[i]+1]) rad[i]++;
		for(k=1;k<=rad[i]&&rad[i]-k!=rad[i-k];k++)
			rad[i+k]=min(rad[i]-k,rad[i-k]);
		rad[i+k]=max(rad[i]-k,0);
	}
	for(i=1;i<=n;i++) cnt[rad[i]<<1|1]++;
	unsigned Ans=1;
	for(i=n;i;i--) if(i&1)
		if(K>(sum+=cnt[i])){
			Ans=(ll)Ans*power(i,sum)%P;
			K-=sum;
		}
		else{
			Ans=(ll)Ans*power(i,K)%P;
			K=0;
			break;
		}
	K?puts("-1"):printf("%u\n",Ans);
}
