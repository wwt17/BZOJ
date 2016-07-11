long long N,A,B,X,x,i,M;
int main(){
	scanf("%llu%lld%lld%lld%lld",&N,&X,&A,&B,&M);
	x=(M-N*X+B*N*(N-1)/2)/(A+B);
	printf("%lld",X);
	for(i=N-1;i;--i) printf(" %lld",X+=x>=i?(x-=i,A):-B);
	putchar('\n');
}
