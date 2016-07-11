main(n,k){
	scanf("%d%d",&n,&k);
	if(k-1<n-k) printf("%d\n",(k-1)+k+1); else
	if(k-1>n-k) printf("%d\n",(n-k)+(n-k+1)+1); else
	printf("%d\n",n==1?1:n+1);
}
