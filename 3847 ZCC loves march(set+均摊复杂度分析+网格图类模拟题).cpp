#include <cstdio>
#include <set>
using namespace std;
typedef long long ll;
#define lld "lld"
const int N=100005,mo=(int)1e9+7;

inline ll sqr(const ll x){
	return x*x;
}

int n,dx[256],dy[256];
ll bnd;

struct block{
	block *belong;
	ll x,y;
	int size;
	block(ll x,ll y):belong(NULL),x(x),y(y),size(0){
	}
	block* get(){
		return belong?(belong=belong->get()):this;
	}
	friend ll calc(const block &a,const block &b){
		return (sqr((a.x-b.x)%mo)+sqr((a.y-b.y)%mo))%mo;
	}
} *V[N];

struct cmpx{
	bool operator () (const block* a,const block* b){
		return a->x<b->x||a->x==b->x&&a->y<b->y;
	}
};
typedef set<block*,cmpx> setx;
setx X;

struct cmpy{
	bool operator () (const block* a,const block* b){
		return a->y<b->y||a->y==b->y&&a->x<b->x;
	}
};
typedef set<block*,cmpy> sety;
sety Y;

block* add(ll x,ll y,int d){
	block *t=new block(x,y);
	setx::iterator i=X.find(t);
	if(i!=X.end()){
		delete t;
		t=*i;
	}
	if(!t->size){
		X.insert(t);
		Y.insert(t);
	}
	t->size+=d;
	if(!t->size){
		X.erase(t);
		Y.erase(t);
	}
	return t;
}

int main(){
	dx['U']=-1;
	dx['D']=+1;
	dy['L']=-1;
	dy['R']=+1;
	scanf("%d%"lld,&n,&bnd);
	add(0,0,1);
	add(bnd+1,bnd+1,1);
	for(int i=1;i<=n;i++){
		ll x,y; scanf("%"lld"%"lld,&x,&y);
		V[i]=add(x,y,1);
	}
	int m; scanf("%d",&m);
	int ans=0;
	while(m--){
		char c=getchar();
		if(c>=0&&dx[c]||dy[c]){
			int u; ll d; scanf("%d%"lld,&u,&d); u^=ans;
			V[u]=V[u]->get();
			ll x=V[u]->x,y=V[u]->y;
			add(x,y,-1);
			V[u]=add(x+dx[c]*d,y+dy[c]*d,+1);
		}
		else
		if(c=='Q'){
			int u; scanf("%d",&u); u^=ans;
			ans=0;
			V[u]=V[u]->get();
			setx::iterator i=X.find(V[u]),ii;
			while((*--(ii=i))->x==(*i)->x){
				ans=(ans+calc(**ii,**i)*(*ii)->size)%mo;
				add((*i)->x,(*i)->y,(*ii)->size);
				add((*ii)->x,(*ii)->y,-(*ii)->size);
				(*ii)->belong=*i;
			}
			while((*++(ii=i))->x==(*i)->x){
				ans=(ans+calc(**ii,**i)*(*ii)->size)%mo;
				add((*i)->x,(*i)->y,(*ii)->size);
				add((*ii)->x,(*ii)->y,-(*ii)->size);
				(*ii)->belong=*i;
			}
			sety::iterator j=Y.find(V[u]),jj;
			while((*--(jj=j))->y==(*j)->y){
				ans=(ans+calc(**jj,**j)*(*jj)->size)%mo;
				add((*j)->x,(*j)->y,(*jj)->size);
				add((*jj)->x,(*jj)->y,-(*jj)->size);
				(*jj)->belong=*j;
			}
			while((*++(jj=j))->y==(*j)->y){
				ans=(ans+calc(**jj,**j)*(*jj)->size)%mo;
				add((*j)->x,(*j)->y,(*jj)->size);
				add((*jj)->x,(*jj)->y,-(*jj)->size);
				(*jj)->belong=*j;
			}
			printf("%d\n",ans);
		}
		else
			m++;
	}
}
