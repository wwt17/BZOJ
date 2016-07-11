#include <cstdio>
const int N=16,mo=1000000007;
int n,a[N][N],f[1<<N],g[1<<N];
int main(){
	scanf("%d",&n);
	for(int i=0;i<n;i++)
		for(int j=0;j<n;j++)
			scanf("%d",&a[i][j]);
	g[0]=1;
	for(int s=1;s<1<<n;s++){
		g[s]=1;
		for(int i=0;i<n;i++) if(s>>i&1)
			for(int j=i+1;j<n;j++) if(s>>j&1)
				g[s]=g[s]*(a[i][j]+1LL)%mo;
		f[s]=g[s];
		for(int S=s^(s&-s),t=S;t;t=(t-1)&S)
			f[s]=(f[s]-1LL*f[s^t]*g[t]%mo+mo)%mo;
	}
	printf("%d\n",f[(1<<n)-1]);
}
