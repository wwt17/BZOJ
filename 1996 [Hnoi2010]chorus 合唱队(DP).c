//f[i][j][right]=f[i+1][j][] or f[i][j-1][]
#define N 1001
#define P 19650827
short n,i,j,h[N];
int f[N][2],t0,t1;
main(){
	scanf("%hu",&n);
	for(i=1;i<=n;++i) scanf("%hu",h+i);
	for(i=n;i;--i){
		f[i][0]=1;
		for(j=i+1;j<=n;++j){
			t0=(h[i]<h[i+1]?f[j][0]:0)+(h[i]<h[j]?f[j][1]:0);
			t1=(h[j]>h[i]?f[j-1][0]:0)+(h[j]>h[j-1]?f[j-1][1]:0);
			f[j][0]=t0%P;
			f[j][1]=t1%P;
		}
	}
	printf("%u\n",(t0+t1)%P);
}
