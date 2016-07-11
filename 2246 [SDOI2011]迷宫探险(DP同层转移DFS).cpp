#include <cstdio>
const int N=32,K=5,H=6,S=243,dir[4][2]={-1,0,1,0,0,-1,0,1};
int pw3[K+1];
int n,m,k,h,s,l;
char a[N][N];
int p[S];
double best,f[N][N][S][H];
int state[K];
int tim,vis[N][N],flag[N][N];
void maxi(double &a,const double b){
	if(b>a) a=b;
}
void dfs1(int x,int y){
	if(a[x][y]=='#'||vis[x][y]==tim||a[x][y]!='.'&&a[x][y]!='$'&&a[x][y]!='@'&&state[a[x][y]-'A']!=1) return;
	vis[x][y]=tim;
	flag[x][y]=1;
	maxi(best,f[x][y][s][l]);
	for(int d=0;d<4;d++){
		maxi(best,f[x+dir[d][0]][y+dir[d][1]][s][l]);
		dfs1(x+dir[d][0],y+dir[d][1]);
	}
}
void dfs2(int x,int y){
	if(flag[x][y]!=1) return;
	flag[x][y]=0;
	maxi(f[x][y][s][l],best);
	for(int d=0;d<4;d++)
		dfs2(x+dir[d][0],y+dir[d][1]);
}
int main(){
	scanf("%d%d%d%d",&n,&m,&k,&h);
	pw3[0]=1;
	for(int i=1;i<=k;i++) pw3[i]=pw3[i-1]*3;
	for(int j=0;j<=m+1;j++) a[0][j]=a[n+1][j]='#';
	for(int i=1;i<=n;i++) scanf("%s",a[i]+1),a[i][0]=a[i][m+1]='#';
	for(int t=0;t<1<<k;t++){
		int x; scanf("%d",&x);
		for(int tt=0;tt<1<<k;tt++){
			int s=0;
			for(int j=0;j<k;j++) if(tt>>j&1)
				s+=((t>>j&1)+1)*pw3[j];
			p[s]+=x;
		}
	}
	for(s=pw3[k]-1;s>=0;s--){
		for(int j=0;j<k;j++) state[j]=s/pw3[j]%3;
		for(l=1;l<=h;l++){
			for(int i=1;i<=n;i++)
				for(int j=1;j<=m;j++) if(a[i][j]!='#'){
					if(a[i][j]=='@'){
						f[i][j][s][l]=p[s];
						continue;
					}
					if(a[i][j]=='.'||a[i][j]=='$')
						continue;
					int loc=a[i][j]-'A';
					if(state[loc]==0){
						for(int d=0;d<4;d++)
							maxi(f[i][j][s][l],
								f[i+dir[d][0]][j+dir[d][1]][s+  pw3[loc]][l]+
								f[i+dir[d][0]][j+dir[d][1]][s+2*pw3[loc]][l-1]);
					}
					else
					if(state[loc]==2){
						for(int d=0;d<4;d++)
							maxi(f[i][j][s][l],f[i+dir[d][0]][j+dir[d][1]][s][l-1]);
					}
				}
			tim++;
			for(int i=1;i<=n;i++)
				for(int j=1;j<=m;j++){
					best=0;
					dfs1(i,j);
					dfs2(i,j);
				}
		}
	}
	for(int i=1;i<=n;i++)
		for(int j=1;j<=m;j++) if(a[i][j]=='$')
			printf("%.3lf\n",f[i][j][0][h]/p[0]);
}
