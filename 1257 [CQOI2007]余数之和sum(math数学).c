// sigma{k%i}(1<=i<=n)
//=sigma{k-k/i*i}
//=k*n-sigma{k/i*i}
int n,k,i,l,r,mid;
int main(){
	scanf("%u%u",&n,&k);
	long long Ans=(long long)k*n;
	for(i=1;i<=n;i=r+1){
		l=i,r=n;
		while(l<r)
			if(k/(mid=(l+r+1)>>1)==k/i)
				l=mid;
			else
				r=mid-1;
		Ans-=k/i*(long long)(r+i)*(r-i+1)>>1;
	}
	printf("%llu\n",Ans);
}
