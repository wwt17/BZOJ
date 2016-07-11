#include <cstdio>
#include <algorithm>
using namespace std;
typedef pair<short,short> pii;
#define fi first
#define se second
const int N=505,inf=(int)1e9+7;
const pii dir[4]={pii(-1,0),pii(1,0),pii(0,-1),pii(0,1)};
int K,n,m;
char map[N][N];
signed char dao[N][N][4];
pii to[N][N][4];
int f[10][10][N][N];
bool vis[N][N][4];
int sum[N*N];
int head,tail,head2,tail2;
pii q[N*N],q2[N*N];
int dis[N*N];
void calc(int x,int y,int d){
	if(to[x][y][d].fi) return;
	if(vis[x][y][d]){
		to[x][y][d].fi=1;
		return;
	}
	vis[x][y][d]=true;
	int xx=x+dir[d].fi,yy=y+dir[d].se;
	if(map[xx][yy]=='x')
		to[x][y][d]=pii(x,y);
	else{
		calc(xx,yy,dao[xx][yy][d]);
		to[x][y][d]=to[xx][yy][dao[xx][yy][d]];
	}
	vis[x][y][d]=false;
}
bool mini(int &a,const int b){
	return b<a?(a=b,true):false;
}

int main(){
	scanf("%d%d%d",&K,&m,&n);
	for(int i=1;i<=n;i++){
		scanf("%s",map[i]+1);
		map[i][0]=map[i][m+1]='x';
	}
	for(int j=0;j<=m+1;j++)
		map[0][j]=map[n+1][j]='x';
	for(int i=1;i<=n;i++)
		for(int j=1;j<=m;j++)
			switch(map[i][j]){
				case 'x':
					break;
				case 'A':
					dao[i][j][0]=2;
					dao[i][j][1]=3;
					dao[i][j][2]=1;
					dao[i][j][3]=0;
					break;
				case 'C':
					dao[i][j][0]=3;
					dao[i][j][1]=2;
					dao[i][j][2]=0;
					dao[i][j][3]=1;
					break;
				default:
					dao[i][j][0]=0;
					dao[i][j][1]=1;
					dao[i][j][2]=2;
					dao[i][j][3]=3;
					break;
			}
	for(int i=1;i<=n;i++)
		for(int j=1;j<=m;j++) if(map[i][j]!='x')
			for(int d=0;d<4;d++)
				calc(i,j,d);
	for(int l=K;l>=1;l--) for(int r=l;r<=K;r++){
		for(int i=0;i<=n*m;i++) sum[i]=0;
		for(int i=1;i<=n;i++) for(int j=1;j<=m;j++) if(map[i][j]!='x'){
			f[l][r][i][j]=l==r&&map[i][j]=='0'+l?0:inf;
			for(int k=l;k<r;k++) mini(f[l][r][i][j],f[l][k][i][j]+f[k+1][r][i][j]);
			if(f[l][r][i][j]<inf)
				sum[f[l][r][i][j]]++;
		}
		for(int i=1;i<=n*m;i++) sum[i]+=sum[i-1];
		head=1,tail=0;
		head2=1,tail2=sum[n*m];
		for(int i=1;i<=n;i++) for(int j=1;j<=m;j++) if(map[i][j]!='x'&&f[l][r][i][j]<inf)
			q2[sum[f[l][r][i][j]]--]=pii(i,j);
		for(int i=1;i<=n*m;i++)
			dis[i]=f[l][r][q2[i].fi][q2[i].se];
		while(head<=tail||head2<=tail2){
			pii u;
			if(head<=tail&&(head2>tail2||f[l][r][q[head].fi][q[head].se]<=dis[head2]))
				u=q[head++];
			else{
				u=q2[head2++];
				if(f[l][r][u.fi][u.se]!=dis[head2-1]) continue;
			}
			for(int d=0;d<4;d++){
				pii v=to[u.fi][u.se][d];
				if(mini(f[l][r][v.fi][v.se],f[l][r][u.fi][u.se]+1))
					q[++tail]=v;
			}
		}
	}
	int ans=inf;
	for(int i=1;i<=n;i++)
		for(int j=1;j<=m;j++) if(map[i][j]!='x')
			mini(ans,f[1][K][i][j]);
	printf("%d\n",ans==inf?-1:ans);
}
