#include <cstdio>
#include <algorithm>
using namespace std;
#define x first
#define y second
typedef pair<int,int> pii;

template<class T>
bool mini(T &a,const T b){
	return b<a?(a=b,true):false;
}

const int N=1005,S=N*N,inf=S;

const pii dir[4]={pii(-1,0),pii(1,0),pii(0,-1),pii(0,1)};

int n,m,head,tail;
char a[N][N];
pii to[N][N][4];
int near[N][N],dist[N][N];
bool inq[N][N];
pii q[S];

int main(){
	scanf("%d%d",&n,&m);
	for(int i=1;i<=n;i++)
		scanf("%s",a[i]+1);
	for(int i=0;i<=n+1;i++) for(int j=0;j<=m+1;j++)
		if(i==0||i==n+1||j==0||j==m+1) a[i][j]='#';
	for(int i=0;i<=n;i++) for(int j=0;j<=m;j++)
		to[i][j][0]=a[i][j]=='#'?pii(i+1,j):to[i-1][j][0],
		to[i][j][2]=a[i][j]=='#'?pii(i,j+1):to[i][j-1][2];
	for(int i=n+1;i>=1;i--) for(int j=m+1;j>=1;j--)
		to[i][j][1]=a[i][j]=='#'?pii(i-1,j):to[i+1][j][1],
		to[i][j][3]=a[i][j]=='#'?pii(i,j-1):to[i][j+1][3];
	head=tail=0;
	for(int i=0;i<=n+1;i++) for(int j=0;j<=m+1;j++)
		if(a[i][j]=='#')
			near[i][j]=0,q[tail++]=pii(i,j);
		else
			near[i][j]=inf;
	while(head!=tail){
		pii u=q[head++];
		for(int d=0;d<4;d++){
			pii v(u.x+dir[d].x,u.y+dir[d].y);
			if(v.x>=1&&v.x<=n&&v.y>=1&&v.y<=m&&near[v.x][v.y]==inf){
				near[v.x][v.y]=near[u.x][u.y]+1;
				q[tail++]=v;
			}
		}
	}
	head=tail=0;
	for(int i=1;i<=n;i++) for(int j=1;j<=m;j++)
		if(a[i][j]=='S'){
			q[tail++]=pii(i,j);
			dist[i][j]=0;
		}
		else
		if(a[i][j]=='#')
			dist[i][j]=0;
		else
			dist[i][j]=inf;
	while(head!=tail){
		pii u=q[head]; if(++head==S) head=0; inq[u.x][u.y]=false;
		for(int d=0;d<4;d++){
			pii v(u.x+dir[d].x,u.y+dir[d].y);
			if(mini(dist[v.x][v.y],dist[u.x][u.y]+1)&&!inq[v.x][v.y]){
				q[tail]=v; if(++tail==S) tail=0; inq[v.x][v.y]=true;
			}
		}
		for(int d=0;d<4;d++){
			pii v(to[u.x][u.y][d]);
			if(mini(dist[v.x][v.y],dist[u.x][u.y]+near[u.x][u.y])&&!inq[v.x][v.y]){
				q[tail]=v; if(++tail==S) tail=0; inq[v.x][v.y]=true;
			}
		}
	}
	for(int i=1;i<=n;i++) for(int j=1;j<=m;j++)
		if(a[i][j]=='C')
			printf("%d\n",dist[i][j]);
}
