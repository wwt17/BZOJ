// f[i][j][k]<=f[i_][j_][k]+val[i][j]
// f[i][j][k|k_]<=f[i][j][k]+f[i][j][k_]
#include <cstdio>
#include <queue>
using namespace std;
const int N=12,M=12,K=10,inf=100000000;
int n,m,k,val[N][M],f[1<<K][N][M];
typedef pair<int,int> pii;
const pii dir[4]={pii(-1,0),pii(1,0),pii(0,-1),pii(0,1)};
inline bool mini(int &a,const int b){
	return b<a?(a=b,true):false;
}
queue<pii> q,q_;
bool inq[N][M];
char map[N][M];
struct data{
	int s; pii u;
	data(){
	}
	data(int _s,pii _u):s(_s),u(_u){
	}
	void search();
} pre[1<<K][N][M];
void data::search(){
	if(!s||!u.first||!u.second) return;
	map[u.first][u.second]=val[u.first][u.second]?'o':'x';
	data &tmp=pre[s][u.first][u.second];
	tmp.search();
	data(s-tmp.s,tmp.u).search();
}
int main(){
	scanf("%d%d",&n,&m);
	for(int i=1;i<=n;i++)
		for(int j=1;j<=m;j++){
			scanf("%d",&val[i][j]);
			if(!val[i][j]) k++;
		}
	for(int s=1;s<1<<k;s++)
		for(int i=1;i<=n;i++)
			for(int j=1;j<=m;j++)
				f[s][i][j]=inf;
	int k_=0;
	for(int i=1;i<=n;i++)
		for(int j=1;j<=m;j++){
			if(!val[i][j])
				f[1<<(k_++)][i][j]=0;
			q_.push(pii(i,j));
		}
	for(int s=1;s<1<<k;s++){
		for(int sub=(s-1)&s;sub;sub=(sub-1)&s)
			for(int i=1;i<=n;i++)
				for(int j=1;j<=m;j++)
					if(mini(f[s][i][j],f[sub][i][j]+f[s-sub][i][j]-val[i][j]))
						pre[s][i][j]=data(sub,pii(i,j));
		q=q_;
		for(int i=1;i<=n;i++)
			for(int j=1;j<=m;j++)
				inq[i][j]=true;
		while(!q.empty()){
			pii u=q.front();
			for(int d=0;d<4;d++){
				pii v(u.first+dir[d].first,u.second+dir[d].second);
				if(mini(f[s][v.first][v.second],f[s][u.first][u.second]+val[v.first][v.second])){
					pre[s][v.first][v.second]=data(s,u);
					if(!inq[v.first][v.second]){
						q.push(v);
						inq[v.first][v.second]=true;
					}
				}
			}
			inq[u.first][u.second]=false;
			q.pop();
		}
		for(int j=0;j<=m+1;j++) f[s][0][j]=f[s][n+1][j]=inf;
		for(int i=1;i<=n;i++) f[s][i][0]=f[s][i][m+1]=inf;
	}
	pii u; int s=(1<<k)-1,ans=inf;
	for(int i=1;i<=n;i++)
		for(int j=1;j<=m;j++){
			map[i][j]='_';
			if(mini(ans,f[s][i][j]))
				u=pii(i,j);
		}
	printf("%d\n",ans);
	data(s,u).search();
	for(int i=1;i<=n;puts(""),i++)
		for(int j=1;j<=m;putchar(map[i][j]),j++);
}
