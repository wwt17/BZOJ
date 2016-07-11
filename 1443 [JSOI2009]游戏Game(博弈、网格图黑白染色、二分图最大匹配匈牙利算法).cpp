/*
【NOI 2011】兔兔和蛋蛋 弱化版
黑白染色形成二分图，合法的连边。
每个人走到的所有颜色都是一样的。
定理：如果某一点一定在最大匹配中，则从该点开始先手必胜。否则后手必胜。
证明：
1. 起始点一定在最大匹配中
	先手策略是沿匹配边走。
	1) 后手走的一定是非匹配边。
		如果后手走的是匹配边，则初始点不一定在最大匹配中。
	2) 先手每次只要沿匹配边走即可。
		如果存在一个点不能沿匹配边走，则整条路径有偶数条边。
		那么把所有边反一下就得到另一个最大匹配，且初始点不再该最大匹配中，与假设矛盾。
	这样，先手一定可以走。故先手必胜。
2. 起始点不一定在最大匹配中
	1) 先手走到的所有点一定在最大匹配中。
		因为起始点不一定在最大匹配中，所以把起始点去掉后的图的最大匹配数与原图相同。 
		如果先手走到一个不一定在去掉起始点后的图的最大匹配中的点，那么去掉这两个点后的图的最大匹配数与只去掉起始点后的最大匹配数相同。
		所以去掉这两个点后的图与原图的最大匹配数相同。
		然而对于原图，可以在去掉两个点之后的图中加上连接这两个点的边，使得最大匹配数+1。
		故产生矛盾，假设不成立，原命题得证。
	这样，根据1，后手必胜，故先手必败。 
	
	枚举起始点，尝试把起始点禁掉，跑匈牙利算法。对起始点的对应点找增广路。
	改成跑一次就过了。
	写dinic+tarjan更快。 
*/
#include <cstdio>
const int N=105;
int n,m,sx,sy,tim;
char map[N][N];
struct node;
struct edge{
	node *ed;
	edge *next;
} E[N*N*4],*newE=E;
struct node{
	node *mat;
	edge *son;
	int type;
	int vis;
	bool ban;
	bool extend(){
		if(!this) return true;
		if(ban) return false;
		for(edge *e=son;e;e=e->next){
			node *v=e->ed;
			if(v->ban||v->vis==tim) continue;
			v->vis=tim;
			if(v->mat->extend()){
				v->mat=this;
				mat=v;
				return true;
			}
		}
		return false;
	}
} V[N][N];
void addedge(node *u,node *v){
	*newE=(edge){v,u->son},u->son=newE++;
	*newE=(edge){u,v->son},v->son=newE++;
}
void hungary(){
	for(int i=1;i<=n;i++)
		for(int j=1;j<=m;j++) if(V[i][j].type==1&&!V[i][j].mat){
			tim++;
			V[i][j].extend();
		}
}
int main(){
	scanf("%d%d",&n,&m);
	for(int i=1;i<=n;i++){
		scanf("%s",map[i]+1);
		for(int j=1;j<=m;j++)
			if(map[i][j]=='.'){
				V[i][j].type=i+j&1?-1:1;
				if(V[i-1][j].type)
					addedge(&V[i][j],&V[i-1][j]);
				if(V[i][j-1].type)
					addedge(&V[i][j],&V[i][j-1]);
			}
	}
	hungary();
	bool found=false;
	for(sx=1;sx<=n;sx++)
		for(sy=1;sy<=m;sy++) if(V[sx][sy].type){
			V[sx][sy].ban=true;
			tim++;
			if(V[sx][sy].mat->extend()){
				V[sx][sy].mat=NULL;
				if(!found) found=true,puts("WIN");
				printf("%d %d\n",sx,sy);
			}
			V[sx][sy].ban=false;
		}
	if(!found) puts("LOSE");
}
