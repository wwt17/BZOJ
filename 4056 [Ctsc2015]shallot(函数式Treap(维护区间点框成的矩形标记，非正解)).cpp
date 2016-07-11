#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef double db;
typedef pair<int,int> pii;
#define eprintf(...) fprintf(stderr,__VA_ARGS__)

const int N=int(1e5)+5,M=N,MZ=int(5e4)+5;

const int inf=int(1e8)+5;

template<class T>
inline void mini(T &a,const T b){
	if(b<a) a=b;
}
template<class T>
inline void maxi(T &a,const T b){
	if(b>a) a=b;
}

template<class T>
inline T sign(const T x){
	if(x>0) return +1;
	if(x<0) return -1;
	return 0;
}

int n,m,C,ans;

struct vec{
	int x,y;
	vec(){
	}
	vec(int _x,int _y):x(_x),y(_y){
	}
};

inline ll cross(const vec &a,const vec &b){
	return (ll)a.x*b.y-(ll)a.y*b.x;
}

inline vec getvec(){
	vec a; scanf("%d%d",&a.x,&a.y);
	return a;
}

inline bool check(const vec &p,const vec &d,const vec &a,const vec &b){
	ll Tmp=cross(d,p);
	return sign(cross(d,a)-Tmp)*sign(cross(d,b)-Tmp)<=0;
}

struct node{
	node *l,*r;
	int weight;
	int size;
	vec a;
	int xmin,xmax,ymin,ymax;
	void update(){
		size=1;
		xmin=xmax=a.x;
		ymin=ymax=a.y;
		if(l){
			size+=l->size;
			mini(xmin,l->xmin);
			maxi(xmax,l->xmax);
			mini(ymin,l->ymin);
			maxi(ymax,l->ymax);
		}
		if(r){
			size+=r->size;
			mini(xmin,r->xmin);
			maxi(xmax,r->xmax);
			mini(ymin,r->ymin);
			maxi(ymax,r->ymax);
		}
	}
} nodepool[(N+MZ)*2*40],*newnode=nodepool;

node* new_node(const node *a){
	*newnode=*a;
	return newnode++;
}

node* new_node(const vec p){
	newnode->weight=rand();
	newnode->l=NULL;
	newnode->r=NULL;
	newnode->a=p;
	newnode->update();
	return newnode++;
}

node *root[M];

node* insert(node *cur,int loc,vec p){
	if(cur==NULL)
		return new_node(p);
	node *ret=new_node(cur);
	int midsize=(ret->l==NULL?0:ret->l->size)+1;
	if(loc<midsize){
		ret->l=insert(ret->l,loc,p);
		if(ret->l->weight>ret->weight){
			node *tmp=new_node(ret->l);
			ret->l=tmp->r;
			ret->update();
			tmp->r=ret;
			ret=tmp;
		}
	}
	else{
		ret->r=insert(ret->r,loc-midsize,p);
		if(ret->r->weight>ret->weight){
			node *tmp=new_node(ret->r);
			ret->r=tmp->l;
			ret->update();
			tmp->l=ret;
			ret=tmp;
		}
	}
	ret->update();
	return ret;
}

void query(node *cur,vec p,vec d){
	if(cur==NULL) return;
	ll	Tmp=cross(d,p),
		tmp1=sign(cross(d,vec(cur->xmin,cur->ymin))-Tmp),
		tmp2=sign(cross(d,vec(cur->xmin,cur->ymax))-Tmp),
		tmp3=sign(cross(d,vec(cur->xmax,cur->ymin))-Tmp),
		tmp4=sign(cross(d,vec(cur->xmax,cur->ymax))-Tmp);
	if(!(tmp2*tmp1<=0||tmp3*tmp1<=0||tmp4*tmp1<=0)) return;
	if(cur->l){
		node *x=cur->l;
		while(x->r!=NULL) x=x->r;
		ans+=check(p,d,x->a,cur->a);
		query(cur->l,p,d);
	}
	if(cur->r){
		node *x=cur->r;
		while(x->l!=NULL) x=x->l;
		ans+=check(p,d,cur->a,x->a);
		query(cur->r,p,d);
	}
}

int main(){
	freopen("shallot.in","r",stdin);
	freopen("shallot.out","w",stdout);
	scanf("%d%d%d",&n,&m,&C);
	for(int i=1;i<=n;i++){
		vec p=getvec();
		root[0]=insert(root[0],i-1,p);
	}
	for(int T=1;T<=m;T++){
		char op[2]; scanf("%s",op);
		if(op[0]=='H'){
			int t; scanf("%d",&t); vec p=getvec(); vec d=getvec();
			if(C){
				p.x^=ans;
				p.y^=ans;
				d.x^=ans;
				d.y^=ans;
			}
			root[T]=root[t];
			ans=0;
			query(root[T],p,d);
			printf("%d\n",ans);
		}
		else{
			int t,loc; scanf("%d%d",&t,&loc); vec p=getvec();
			if(C){
				p.x^=ans;
				p.y^=ans;
			}
			root[T]=insert(root[t],loc,p);
		}
	}
}
