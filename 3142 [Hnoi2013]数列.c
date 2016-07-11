// Ans = n*m^(k-1) - (k-1)*m*(m+1)/2*m^(k-2)
//     = (n-(k-1)*(m+1)/2) * m^(k-1)
long long n,m,k,P,q,ans;
int main(){
	scanf("%lld%lld%lld%lld",&n,&k,&m,&P); n%=P;
	if(k==1){
		printf("%lld\n",n);
		return 0;
	}
	ans=((n*m-m*(m+1)/2%P*(k-1))%P+P)%P;
	for(q=k-2;q;q>>=1,m=m*m%P)
		if(q&1) ans=ans*m%P;
	printf("%lld\n",ans);
}
