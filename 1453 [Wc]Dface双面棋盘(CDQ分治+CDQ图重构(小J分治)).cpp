#include <cstdio>
const int N=205,M=10000;
int n,m,ans[2];
bool map[N][N];
int cnt[N][N];
struct vec{
	int x,y;
	vec(){
	}
	vec(int _x,int _y):x(_x),y(_y){
	}
} q[M];
struct node;
struct rec{
	node *x; node *y;
} stack[M*100],*top=stack;
struct node{
	node *belong;
	node* get(){
		if(!belong) return this;
		*top++=(rec){this,belong};
		return belong=belong->get();
	}
} V[N][N];
void back(rec *bef){
	while(top>bef){
		top--;
		top->x->belong=top->y;
		if(!top->y){
			int num=top->x-V[0];
			ans[map[num/N][num%N]]++;
		}
	}
}
const vec dir[4]={vec(-1,0),vec(1,0),vec(0,-1),vec(0,1)};
void add(vec a){
	ans[map[a.x][a.y]]++;
	for(int d=0;d<4;d++){
		vec b(a.x+dir[d].x,a.y+dir[d].y);
		if(b.x<1||b.x>n||b.y<1||b.y>n) continue;
		node *x,*y;
		if(!cnt[b.x][b.y]&&map[a.x][a.y]==map[b.x][b.y]
		&&(x=V[a.x][a.y].get())!=(y=V[b.x][b.y].get())){
			*top++=(rec){x,x->belong};
			x->belong=y;
			ans[map[a.x][a.y]]--;
		}
	}
}
void work(vec *beg,vec *end){
	rec *last=top;
	if(end-beg==1){
		map[beg->x][beg->y]^=1;
		if(!--cnt[beg->x][beg->y]) add(*beg);
		printf("%d %d\n",ans[1],ans[0]);
		back(last);
		if(!cnt[beg->x][beg->y]++) ans[map[beg->x][beg->y]]--;
		return;
	}
	vec *mid=beg+(end-beg)/2;
	
	for(vec *i=mid;i<end;i++) if(!--cnt[i->x][i->y]) add(*i);
	work(beg,mid);
	back(last);
	for(vec *i=mid;i<end;i++) if(!cnt[i->x][i->y]++) ans[map[i->x][i->y]]--;
	
	for(vec *i=beg;i<mid;i++) if(!--cnt[i->x][i->y]) add(*i);
	work(mid,end);
	back(last);
	for(vec *i=beg;i<mid;i++) if(!cnt[i->x][i->y]++) ans[map[i->x][i->y]]--;
}
int main(){
	scanf("%d",&n);
	for(int i=1;i<=n;i++)
		for(int j=1;j<=n;j++){
			static int x; scanf("%d",&x);
			map[i][j]=x;
		}
	scanf("%d",&m);
	for(int i=0;i<m;i++){
		scanf("%d%d",&q[i].x,&q[i].y);
		cnt[q[i].x][q[i].y]++;
	}
	for(int i=1;i<=n;i++)
		for(int j=1;j<=n;j++) if(!cnt[i][j])
			add(vec(i,j));
	work(q,q+m);
}
