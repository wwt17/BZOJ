#define P 12345678910LL
int n; long long s[50001],*top=s;
int main(){
	scanf("%u",&n);
	while(n--)
		if(getchar(),getchar()=='0') *++top=0;
		else *(top-1)+=*top?(*top<<1)%P:1,top--;
	printf("%llu\n",*top%P);
}
