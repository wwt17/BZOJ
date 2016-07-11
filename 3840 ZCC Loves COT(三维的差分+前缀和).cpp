#include <cstdio>
typedef long long ll;
const int N=111;
int n,m,q;
ll a[N][N][N][4];
int main(){
	scanf("%d%d%d",&n,&m,&q);
	
	while(m--){
		int x,y,z,r; scanf("%d%d%d%d",&x,&y,&z,&r);
		a[x][y][z][0]++;
		a[x+r][y][z][0]--;
		a[x][y+1][z][1]--;
		a[x+r][y+1+r][z][1]++;
		a[x][y][z+1][2]--;
		a[x+r][y][z+1][2]++;
		a[x][y+1][z+2][3]++;
		a[x+r][y+1+r][z+2+r][3]--;
	}
	
	for(int i=1;i<=n;i++)
	for(int j=1;j<=i;j++)
	for(int k=1;k<=j;k++)
		a[i+1][j][k][0]+=a[i][j][k][0],
		a[i+1][j+1][k][1]+=a[i][j][k][1],
		a[i+1][j][k][2]+=a[i][j][k][2],
		a[i+1][j+1][k+1][3]+=a[i][j][k][3];
	
	for(int i=1;i<=n;i++)
	for(int j=1;j<=i;j++)
	for(int k=1;k<=j;k++)
		a[i][j][k][0]+=a[i][j][k][1],
		a[i][j][k][2]+=a[i][j][k][3];
	
	for(int i=1;i<=n;i++)
	for(int j=1;j<=i;j++)
	for(int k=1;k<=j;k++)
		a[i][j+1][k][0]+=a[i][j][k][0],
		a[i][j+1][k+1][2]+=a[i][j][k][2];
	
	for(int i=1;i<=n;i++)
	for(int j=1;j<=i;j++)
	for(int k=1;k<=j;k++)
		a[i][j][k][0]+=a[i][j][k][2];
	for(int i=1;i<=n;i++)
	for(int j=1;j<=i;j++)
	for(int k=1;k<=j;k++)
		a[i][j][k+1][0]+=a[i][j][k][0];
	
	for(int i=1;i<=n+5;i++)
	for(int j=1;j<=i+5;j++)
	for(int k=1;k<=j+5;k++){
		if(i<=n&&i>=j&&j>=k); else a[i][j][k][0]=0;
		a[i][j][k][1]=a[i][j][k][2]=a[i][j][k][3]=0;
	}
	
	for(int i=1;i<=n;i++)
	for(int j=1;j<=i;j++)
	for(int k=j;k>=1;k--)
		a[i][j][k][2]=a[i][j][k][0]+=a[i][j][k+1][0];
	
	for(int i=1;i<=n;i++)
	for(int j=i;j>=1;j--)
	for(int k=1;k<=j;k++)
		a[i][j][k][1]=a[i][j][k][0]+=a[i][j+1][k][0],
		a[i][j][k][3]=a[i][j][k][2]+=a[i][j+1][k+1][2];
	
	for(int i=n;i>=1;i--)
	for(int j=1;j<=i;j++)
	for(int k=1;k<=j;k++)
		a[i][j][k][0]+=a[i+1][j][k][0],
		a[i][j][k][1]+=a[i+1][j+1][k][1],
		a[i][j][k][2]+=a[i+1][j][k][2],
		a[i][j][k][3]+=a[i+1][j+1][k+1][3];
	
	while(q--){
		int x,y,z,r; scanf("%d%d%d%d",&x,&y,&z,&r);
		ll ans=0;
		ans+=a[x][y][z][0];
		ans-=a[x+r][y][z][0];
		ans-=a[x][y+1][z][1];
		ans+=a[x+r][y+1+r][z][1];
		ans-=a[x][y][z+1][2];
		ans+=a[x+r][y][z+1][2];
		ans+=a[x][y+1][z+2][3];
		ans-=a[x+r][y+1+r][z+2+r][3];
		printf("%lld\n",ans);
	}
}
