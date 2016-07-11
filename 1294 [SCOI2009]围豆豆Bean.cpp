#include <cstdio>
#include <cstring>
#include <algorithm>
#include <queue>
int N,M,D,V[12],d[12][12][1<<10],val[1<<10],i,j,k,Ans;
char map[12][12]; int mov[12][12];
const int dx[]={-1,1,0,0},dy[]={0,0,-1,1};
struct situ{
	int x,y,s;
};
void BFS(int x,int y){
	static std::queue<situ> q;
	memset(d,-1,sizeof(d));
	d[x][y][0]=0;
	q.push((situ){x,y,0});
	situ now,next;
	while(!q.empty()){
		now=q.front(); q.pop();
		for(int dir=0;dir<4;++dir)
			if(map[next.x=now.x+dx[dir]][next.y=now.y+dy[dir]]=='0'){
				next.s=now.s^(dir&2?0:dir&1?mov[next.x][next.y]:mov[now.x][now.y]);
				if(d[next.x][next.y][next.s]!=-1) continue;
				d[next.x][next.y][next.s]=d[now.x][now.y][now.s]+1;
				q.push(next);
			}
	}
}
int main(){
	scanf("%u%u\n%u",&N,&M,&D);
	for(int dd=0;dd<D;++dd) scanf("%d",V+dd);
	for(k=0;k<1<<D;++k){
		val[k]=0;
		for(int dd=0;dd<D;++dd) if(k&(1<<dd)) val[k]+=V[dd];
	}
	for(i=1;i<=N;++i){
		scanf("%s",map[i]+1);
		for(j=1;j<=M;++j){
			mov[i][j]=mov[i][j-1];
			if(map[i][j]>'0') mov[i][j]|=1<<(map[i][j]-'1');
		}
	}
	for(i=1;i<=N;++i)
		for(j=1;j<=M;++j) if(map[i][j]=='0'){
			BFS(i,j);
			for(k=0;k<1<<D;++k) if(d[i][j][k]!=-1)
				Ans=std::max(Ans,val[k]-d[i][j][k]);
		}
	printf("%d\n",Ans);
}
