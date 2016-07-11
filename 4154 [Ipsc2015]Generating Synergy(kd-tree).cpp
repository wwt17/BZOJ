#include <cstdio>
#include <algorithm>
using namespace std;

const int mo=(int)1e9+7;

const int N=(int)1e5+5;

int n,q,len,tim;

int XL,XR,YL,YR;
int C;

struct node{
	node *fa,*son,*next;
	int depth;
	int st,en;
	void dfs(int Depth=1){
		depth=Depth;
		st=len;
		for(node *v=son;v;v=v->next){
			v->dfs(Depth+1);
		}
		en=++len;
		x=en;
		y=depth;
	}
	node *pa,*l,*r;
	int x,y,xL,xR,yL,yR;
	int col,coltim,cov,covtim;
	void init(){
		col=1;
		coltim=0;
		cov=0;
		covtim=0;
	}
	void update(){
		xL=xR=x;
		yL=yR=y;
		if(l){
			xL=min(xL,l->xL);
			xR=max(xR,l->xR);
			yL=min(yL,l->yL);
			yR=max(yR,l->yR);
		}
		if(r){
			xL=min(xL,r->xL);
			xR=max(xR,r->xR);
			yL=min(yL,r->yL);
			yR=max(yR,r->yR);
		}
	}
	void cover(int c,int t){
		cov=c; covtim=t;
		col=c; coltim=t;
	}
	void Cover(){
		if(this==NULL) return;
		if(xR<XL||xL>XR||yR<YL||yL>YR) return;
		if(xL>=XL&&xR<=XR&&yL>=YL&&yR<=YR){
			return cover(C,tim);
		}
		if(x>=XL&&x<=XR&&y>=YL&&y<=YR)
			col=C,coltim=tim;
		l->Cover();
		r->Cover();
	}
	int query(){
		int c=col,t=coltim;
		for(node *u=this;u;u=u->pa){
			if(u->cov&&u->covtim>t){
				c=u->cov;
				t=u->covtim;
			}
		}
		return c;
	}
} V[N],*seq[N];

bool cmpx(const node *u,const node *v){
	return u->x<v->x;
}
bool cmpy(const node *u,const node *v){
	return u->y<v->y;
}

node *root;

node* build(node **beg,node **end,bool isy=false){
	if(end-beg==0) return NULL;
	node **mid=end-(end-beg>>1);
	nth_element(beg+1,mid,end+1,isy?cmpy:cmpx);
	node *cur=*mid;
	cur->pa=NULL;
	if(cur->l=build(beg,mid-1,isy^1)) cur->l->pa=cur;
	if(cur->r=build(mid,end  ,isy^1)) cur->r->pa=cur;
	cur->update();
	return cur;
}

int Main(){
	scanf("%d%*d%d",&n,&q);
	for(int i=1;i<=n;i++) V[i].son=NULL;
	for(int i=2;i<=n;i++){
		int j; scanf("%d",&j);
		V[i].fa=V+j;
		V[i].next=V[i].fa->son;
		V[i].fa->son=V+i;
	}
	len=0;
	V[1].dfs();
	for(int i=1;i<=n;i++) seq[i]=V+i;
	root=build(seq,seq+n);
	for(int i=1;i<=n;i++) V[i].init();
	int ret=0;
	for(tim=1;tim<=q;tim++){
		int x,l; scanf("%d%d%d",&x,&l,&C);
		if(C==0){
			ret=(ret+1LL*tim*V[x].query())%mo;
		}
		else{
			XL=V[x].st+1;
			XR=V[x].en;
			YL=V[x].depth;
			YR=V[x].depth+l;
			root->Cover();
		}
	}
	return ret;
}

int main(){
	int T; scanf("%d",&T);
	while(T--) printf("%d\n",Main());
}
