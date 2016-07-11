// f[i][j]=f[i][j-1]+f[i-1][j-1]
int n,m,i,j; long long f[16];
int main(){
	scanf("%d%d",&m,&n);
	for(j=0;j<=n;j++) f[j]=1;
	for(i=1;i<=m;i++){
		for(j=n;j;j--) f[j]+=f[j-1];
		f[0]=2;
	}
	printf("%lld\n",f[n]);
}
