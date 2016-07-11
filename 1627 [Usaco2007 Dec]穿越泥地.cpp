#include <cstdio>
#include <queue>
#define Base 502
const char dx[4]={1,-1,0,0},dy[4]={0,0,-1,1};
bool f[Base<<1^1][Base<<1^1];
struct xy{
	short x,y; int step;
};
int main(){
	int X,Y,N;
	scanf("%d%d%d",&X,&Y,&N);
	std::queue<xy> q;
	q.push((xy){X+Base,Y+Base,0});
	f[X+Base][Y+Base]=1;
	while(N--){
		scanf("%d%d",&X,&Y);
		f[Base+X][Base+Y]=1;
	}
	xy u,v; int d;
	while(!q.empty()){
		u=q.front(); q.pop();
		v.step=u.step+1;
		for(d=0;d<4;++d)
			if(!f[v.x=u.x+dx[d]][v.y=u.y+dy[d]]){
				f[v.x][v.y]=1;
				if(v.x==Base&&v.y==Base){
					printf("%d\n",v.step);
					scanf("%d");
					return 0;
				}
				q.push(v);
			}
	}
}
