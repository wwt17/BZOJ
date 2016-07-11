#include <cstdio>
#include <cmath>
#include <queue>
#define sqr(x) ((x)*(x))
bool map[32][32];
short dist[32][32];
struct vec{
	short x,y;
	vec(){}
	vec(short _x,short _y):x(_x),y(_y){}
} n,i,j;
short t;
const vec dir[4]={vec(-1,0),vec(1,0),vec(0,-1),vec(0,1)};
std::deque<vec> q;
int main(){
	scanf("%hd%hd%hd\n",&n.x,&n.y,&t);
	for(i.x=1;i.x<=n.x;scanf("\n"),i.x++)
		for(i.y=1;i.y<=n.y;map[i.x][i.y]=getchar()=='1',i.y++);
	short ans=0;
	for(i.x=1;i.x<=n.x;i.x++)
		for(i.y=1;i.y<=n.y;i.y++){
			for(j.x=1;j.x<=n.x;j.x++)
				for(j.y=1;j.y<=n.y;j.y++)
					dist[j.x][j.y]=t+1;
			dist[i.x][i.y]=map[i.x][i.y];
			q.push_back(i);
			while(!q.empty()){
				vec u=q.front(); q.pop_front();
				for(int d=0;d<4;d++){
					vec v(u.x+dir[d].x,u.y+dir[d].y);
					if(dist[u.x][u.y]+map[v.x][v.y]<dist[v.x][v.y]){
						dist[v.x][v.y]=dist[u.x][u.y]+map[v.x][v.y];
						if(map[v.x][v.y])
							q.push_back(v);
						else
							q.push_front(v);
					}
				}
			}
			for(j.x=i.x;j.x<=n.x;j.x++)
				for(j.y=1;j.y<=n.y;j.y++)
					if(dist[j.x][j.y]<t+1&&sqr(j.x-i.x)+sqr(j.y-i.y)>ans)
						ans=sqr(j.x-i.x)+sqr(j.y-i.y);
		}
	printf("%.6lf\n",sqrt((double)ans));
}
