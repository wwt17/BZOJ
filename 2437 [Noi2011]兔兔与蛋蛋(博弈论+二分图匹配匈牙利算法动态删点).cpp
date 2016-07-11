#include <cstdio>
const int N=45,K=1005;
int n,m,sx,sy,tim,ans[K];
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
bool win(){
	V[sx][sy].ban=true;
	tim++;
	if(V[sx][sy].mat) V[sx][sy].mat->mat=NULL;
	return !V[sx][sy].mat->extend();
}
int main(){
	scanf("%d%d",&n,&m);
	for(int i=1;i<=n;i++){
		scanf("%s",map[i]+1);
		for(int j=1;j<=m;j++){
			if(map[i][j]=='.'){
				sx=i;
				sy=j;
				map[i][j]='X';
			}
		}
	}
	for(int i=1;i<=n;i++)
		for(int j=1;j<=m;j++){
			if(map[i][j]=='O'&&(i^sx^j^sy)&1){
				V[i][j].type=-1;
				if(V[i-1][j].type)
					addedge(&V[i][j],&V[i-1][j]);
				if(V[i][j-1].type)
					addedge(&V[i][j],&V[i][j-1]);
			}
			else
			if(map[i][j]=='X'&&!((i^sx^j^sy)&1)){
				V[i][j].type=1;
				if(V[i-1][j].type)
					addedge(&V[i][j],&V[i-1][j]);
				if(V[i][j-1].type)
					addedge(&V[i][j],&V[i][j-1]);
			}
		}
	hungary();
	int k; scanf("%d",&k);
	for(int t=1;t<=k;t++){
		bool tmp=win();
		scanf("%d%d",&sx,&sy);
		if(win()&&tmp)
			ans[++*ans]=t;
		scanf("%d%d",&sx,&sy);
	}
	printf("%d\n",*ans);
	for(int i=1;i<=*ans;i++) printf("%d\n",ans[i]);
}
