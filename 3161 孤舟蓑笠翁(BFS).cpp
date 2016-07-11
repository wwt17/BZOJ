#include <cstdio>
#include <cstdlib>
#include <algorithm>
#include <vector>
#include <queue>
using namespace std;

const int N=1005,K=N*N,inf=(int)5e8;

struct vec{
	int x,y;
	vec(int _x=0,int _y=0):x(_x),y(_y){
	}
};

int n,m,k,dmin,dmax;
vec a[N],seq[K];
int ans[K];
vector<int> e[N][2];
int nearest[N][N],dist[N][N];
queue<vec> q;

void mini(int &a,const int b){
	if(b<a) a=b;
}

int main(){
	scanf("%d%d%d%d",&n,&m,&dmin,&dmax);
	for(int i=1;i<=n;i++) scanf("%d%d",&a[i].x,&a[i].y);
	scanf("%d",&k);
	for(int i=1;i<=k;i++) scanf("%d%d",&seq[i].x,&seq[i].y),ans[i]=inf;
	for(int i=1;i<=n;i++) e[i][0].push_back(i),e[i][1].push_back(i);
	for(int i=1;i<=m;i++){
		int x,y,type;
		scanf("%d%d%d",&x,&y,&type);
		e[x][type].push_back(y);
		e[y][type].push_back(x);
	}
	for(int i=1;i<=n;i++)
		for(int j=1;j<=n;j++){
			int d=abs(a[i].x-a[j].x)+abs(a[i].y-a[j].y);
			if(d>=dmin&&d<=dmax)
				dist[i][j]=inf;
			else
				dist[i][j]=-1;
		}
	for(int i=1;i<=k;i++){
		q.push(seq[i]);
		nearest[seq[i].x][seq[i].y]=i;
		dist[seq[i].x][seq[i].y]=0;
	}
	while(!q.empty()){
		vec u=q.front(); q.pop();
		for(vector<int>::iterator i=e[u.x][0].begin();i!=e[u.x][0].end();i++)
			for(vector<int>::iterator j=e[u.y][1].begin();j!=e[u.y][1].end();j++){
				vec v(*i,*j);
				if(dist[u.x][u.y]+1<dist[v.x][v.y]){
					dist[v.x][v.y]=dist[u.x][u.y]+1;
					nearest[v.x][v.y]=nearest[u.x][u.y];
					q.push(v);
				}
			}
	}
	vec u;
	for(u.x=1;u.x<=n;u.x++)
		for(u.y=1;u.y<=n;u.y++) if(nearest[u.x][u.y])
			for(vector<int>::iterator i=e[u.x][0].begin();i!=e[u.x][0].end();i++)
				for(vector<int>::iterator j=e[u.y][1].begin();j!=e[u.y][1].end();j++){
					vec v(*i,*j);
					if(nearest[v.x][v.y]&&nearest[u.x][u.y]!=nearest[v.x][v.y]){
						mini(ans[nearest[u.x][u.y]],dist[u.x][u.y]+1+dist[v.x][v.y]);
					}
				}
	for(int i=1;i<=k;i++)
		printf("%d\n",ans[i]<inf?ans[i]:-1);
}
