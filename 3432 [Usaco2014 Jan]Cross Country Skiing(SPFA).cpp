#include <cstdio>
#include <cstdlib>
#include <algorithm>
#include <queue>
using namespace std;
typedef pair<int,int> pii;
const int M=502,N=502,inf=0x7fffffff;
const pii dir[4]={pii(-1,0),pii(1,0),pii(0,-1),pii(0,1)};
int n,m,h[M][N],flag[M][N],d[M][N];
queue<pii> q; bool inq[M][N];
int main(){
	scanf("%d%d",&m,&n);
	for(int j=0;j<=n+1;j++) d[0][j]=d[m+1][j]=0;
	for(int i=1;i<=m;i++){
		d[i][0]=d[i][n+1]=0;
		for(int j=1;j<=n;j++){
			scanf("%d",&h[i][j]);
			d[i][j]=inf;
		}
	}
	int ans=0;
	bool first=true;
	for(int i=1;i<=m;i++)
		for(int j=1;j<=n;j++){
			scanf("%d",&flag[i][j]);
			if(!flag[i][j]) continue;
			if(first){
				first=false;
				q.push(pii(i,j));
				inq[i][j]=true;
				d[i][j]=0;
				while(!q.empty()){
					pii cur=q.front();
					for(int k=0;k<4;k++){
						pii next(cur.first+dir[k].first,cur.second+dir[k].second);
						int val=max(d[cur.first][cur.second],abs(h[cur.first][cur.second]-h[next.first][next.second]));
						if(val<d[next.first][next.second]){
							d[next.first][next.second]=val;
							if(!inq[next.first][next.second]){
								q.push(next);
								inq[next.first][next.second]=true;
							}
						}
					}
					inq[cur.first][cur.second]=false;
					q.pop();
				}
			}
			else
				ans=max(ans,d[i][j]);
		}
	printf("%d\n",ans);
}
