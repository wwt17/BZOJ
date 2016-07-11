#define N 102
int n,m,s,ans,a[N][N],b[N][N];
int main(){
	scanf("%d%d",&n,&m);
	int i,j,r,c;
	for(i=1;i<=n;i++)
		for(j=1;j<=m;j++)
			scanf("%d",&a[i][j]),s+=a[i][j];
	for(r=1;r<=n;r++) if(s%r==0)
		for(c=1;c<=m;c++) if(s%(r*c)==0&&r*c>ans){
			for(i=1;i<=n;i++)
				for(j=1;j<=m;j++)
					b[i][j]=a[i][j]-a[i][j-1]-a[i-1][j]+a[i-1][j-1];
			for(i=1;i<=n-r+1;i++){
				for(j=1;j<=m-c+1;j++){
					b[i+r][j]+=b[i][j];
					b[i][j+c]+=b[i][j];
					b[i+r][j+c]-=b[i][j];
					b[i][j]=0;
				}
				for(;j<=m;j++)
					if(b[i][j]) goto fail;
			}
			for(;i<=n;i++)
				for(j=1;j<=m-c;j++)
					if(b[i][j]) goto fail;
			ans=r*c;
			fail:;
		}
	printf("%d\n",s/ans);
}
