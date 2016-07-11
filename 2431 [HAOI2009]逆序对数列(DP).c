// f[i][j]=sigma(0<=k<=i-1){ f[i-1][j-k] }
const int P=10000;
int f[1001],g[1001];
int main(){
	int n,k,i,j,min;
	scanf("%d%d",&n,&k);
	int ans=0;
	f[0]=1;
	for(j=0;j<=k;j++) g[j]=1;
	for(i=2;i<=n;i++){
		for(j=1;j<=k;j++) f[j]=(g[j]-(j-i<0?0:g[j-i])+P)%P;
		for(j=1;j<=k;j++) g[j]=g[j-1]+f[j];
	}
	printf("%d\n",f[k]);
}
