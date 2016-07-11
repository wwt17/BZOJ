#define N 502
#define inf 0x7fffffff
#define max(a,b) (a>b?a:b)
#define maxi(a,b) if(a<b) a=b
char x[N],y[N],z[N];
int f[N][N][2];
_Bool F;
int main(){
	scanf("%s%s%s",x+1,y+1,z+1);
	int i,j,k;
	for(i=1;x[i];i++)
		for(j=1;y[j];j++){
			f[i][j][!F]=max(f[i-1][j][!F],f[i][j-1][!F]);
			if(x[i]==y[j])
				maxi(f[i][j][!F],f[i-1][j-1][!F]+1);
		}
	for(k=1;z[k];F^=1,k++){
		f[0][0][F]=-inf;
		for(j=1;y[j];j++) f[0][j][F]=-inf;
		for(i=1;x[i];i++) f[i][0][F]=-inf;
		for(i=1;x[i];i++)
			for(j=1;y[j];j++){
				f[i][j][F]=max(f[i-1][j][F],f[i][j-1][F]);
				if(x[i]==y[j]){
					maxi(f[i][j][F],f[i-1][j-1][F]+1);
					if(x[i]==z[k])
						maxi(f[i][j][F],f[i-1][j-1][!F]+1);
				}
			}
	}
	if(f[i-1][j-1][!F]>0)
		printf("%d\n",f[i-1][j-1][!F]);
	else
		puts("NO SOLUTION");
}
