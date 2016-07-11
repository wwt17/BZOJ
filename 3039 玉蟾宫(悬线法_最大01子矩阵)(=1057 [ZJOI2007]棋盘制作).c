#define M 1001
int n,m,i,j,ans,h[M],l[M],r[M]; char ch;
int main(){
	scanf("%u%u",&n,&m);
	for(i=1;i<=n;i++){
		for(j=1;j<=m;j++){
			while((ch=getchar())!='R'&&ch!='F');
			if(ch=='F') h[j]++; else h[j]=0;
		}
		for(j=1;j<=m;j++)
			for(l[j]=j;l[j]>1&&h[l[j]-1]>=h[j];l[j]=l[l[j]-1]);
		for(j=m;j>=1;j--)
			for(r[j]=j;r[j]<m&&h[r[j]+1]>=h[j];r[j]=r[r[j]+1]);
		for(j=1;j<=m;j++)
			if(ans<(r[j]-l[j]+1)*h[j]) ans=(r[j]-l[j]+1)*h[j];
	}
	printf("%u\n",ans*3);
}
