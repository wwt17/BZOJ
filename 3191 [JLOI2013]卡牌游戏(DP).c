//f[i][j]=sigma{j==loc?0:f[i-1][loc<j?j-loc:i-(loc-j)]/M}
#define N 51
#define M 51
int n,m,i,j,k,a[M],loc;
float F[2][N],*f=F[0],*ff=F[1],*tmp;
int main(){
	scanf("%u%u",&n,&m);
	for(k=1;k<=m;++k) scanf("%u",a+k),a[k]--;
	f[1]=1;
	for(i=2;i<=n;tmp=f,f=ff,ff=tmp,++i)
		for(j=1;j<=i;ff[j++]/=m)
			for(ff[j]=0,k=1;k<=m;++k)
				if(j!=(loc=a[k]%i+1))
					ff[j]+=f[loc<j?j-loc:i-loc+j];
	for(j=1;j<=n;++j) printf("%.2f%%%c",f[j]*100,j<n?' ':'\n');
}
