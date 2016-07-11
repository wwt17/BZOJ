#include <cstdio>
#include <algorithm>
using namespace std;
typedef pair<short,short> vec;
#define x first
#define y second
vec dir[4]={ vec(-1,0), vec(1,0), vec(0,-1), vec(0,1) };
vec bound,i,at,dest,slide[128][2],q[300*300],next; int step[300*300],head,tail;
bool flag[128],done[300][300]; char map[300][300];
int main(){
	scanf("%u%u\n",&bound.x,&bound.y);
	for(i.x=0;i.x<bound.x;getchar(),i.x++)
		for(i.y=0;i.y<bound.y;i.y++)
			switch(map[i.x][i.y]=getchar()){
				case '#':
				case '.': break;
				case '@': at=i; break;
				case '=': dest=i; break;
				default: slide[map[i.x][i.y]][flag[map[i.x][i.y]]^=1]=i;
			}
	q[tail]=at;
	step[tail++]=0;
	done[at.x][at.y]=true;
	for(;head<tail;head++)
		for(vec* d=dir;d<dir+4;d++){
			next.x=q[head].x+d->x;
			next.y=q[head].y+d->y;
			if('A'<=map[next.x][next.y]&&map[next.x][next.y]<='Z')
				next=slide[map[next.x][next.y]][slide[map[next.x][next.y]][0]==next];
			if(map[next.x][next.y]!='#'&&!done[next.x][next.y]){
				q[tail]=next;
				step[tail++]=step[head]+1;
				done[next.x][next.y]=true;
				if(next==dest){
					printf("%u\n",step[tail-1]);
					return 0;
				}
			}
		}
}
