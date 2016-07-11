#include <cstdio>
typedef long long ll;
const int N=45;
int n,m,a[N][N];
ll base[N],b[N][N];
void add(ll x){
	for(int i=0;i<m;i++) if(x>>i&1){
		if(!base[i]){
			base[i]=x;
			break;
		}
		x^=base[i];
	}
}
int main(){
	scanf("%d%d",&n,&m);
	for(int j=1;j<=m;j++) b[1][j]=1LL<<(j-1);
	for(int i=2;i<=n+1;i++)
		for(int j=1;j<=m;j++)
			b[i][j]=b[i-1][j-1]^b[i-1][j]^b[i-1][j+1]^b[i-2][j];
	for(int j=1;j<=m;j++)
		add(b[n+1][j]);
	for(int i=m-1;i>=0;i--){
		if(!base[i]){
			a[1][i+1]=1;
			continue;
		}
		for(int j=i+1;j<m;j++) if(base[i]>>j&1)
			base[i]^=base[j];
		for(int j=i+1;j<m;j++) if(base[i]>>j&1)
			a[1][i+1]^=a[1][j+1];
	}
	for(int i=2;i<=n+1;i++)
		for(int j=1;j<=m;j++)
			a[i][j]=a[i-1][j-1]^a[i-1][j]^a[i-1][j+1]^a[i-2][j];
	for(int i=1;i<=n;i++)
		for(int j=1;j<=m;j++)
			putchar('0'+a[i][j]),
			putchar(" \n"[j==m]);
}
