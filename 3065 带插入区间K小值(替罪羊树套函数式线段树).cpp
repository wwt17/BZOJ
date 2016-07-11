#include <cstdio>
#include <algorithm>
using namespace std;

const int N=70005,M=N,segsize=20000000;
double alpha=0.8;

int n;

struct seg{
	seg *l,*r;
	int cnt,sum;
} memseg[segsize],*unused[segsize],**topseg=unused;

void initmemseg(){
	for(int i=segsize-1;i>=0;i--) *topseg++=memseg+i;
}

inline seg* newseg(){
	return *--topseg;
}

void delseg(seg *cur){
	if(!cur) return;
	if(!--cur->cnt){
		delseg(cur->l);
		delseg(cur->r);
		*topseg++=cur;
	}
}

int X,D;
seg* insert(seg *cur,int beg,int end){
	seg *res=newseg();
	if(cur) *res=*cur; else{
		res->l=res->r=NULL;
		res->sum=0;
	}
	res->cnt=1;
	res->sum+=D;
	if(end-beg>1){
		int mid=beg+end>>1;
		if(X<mid){
			res->l=insert(res->l,beg,mid);
			if(res->r) res->r->cnt++;
		}
		else{
			res->r=insert(res->r,mid,end);
			if(res->l) res->l->cnt++;
		}
	}
	return res;
}

seg* merge(seg *u,seg *v){
	seg *res;
	if(!u) res=v; else
	if(!v) res=u; else{
		res=newseg();
		res->cnt=0;
		res->sum=u->sum+v->sum;
		res->l=merge(u->l,v->l);
		res->r=merge(u->r,v->r);
	}
	if(res) res->cnt++;
	return res;
}

struct node{
	node *l,*r;
	int size;
	int a;
	seg *t;
	void update(){
		size=1;
		if(l) size+=l->size;
		if(r) size+=r->size;
		delseg(t);
		int ttt=X;
		X=a;
		D=1;
		t=insert(NULL,0,M);
		X=ttt;
		if(l){ seg* tmp=merge(t,l->t); delseg(t); t=tmp; }
		if(r){ seg* tmp=merge(t,r->t); delseg(t); t=tmp; }
	}
} V[N],*newnode,*seq[N];

seg *rot[N];
int val[N];

int len,len2;

node *root;

void dfs(node *cur){
	if(!cur) return;
	dfs(cur->l);
	seq[len++]=cur;
	dfs(cur->r);
}

node *build(node **beg,node **end){
	if(beg==end) return NULL;
	node **mid=beg+(end-beg>>1);
	(*mid)->l=build(beg,mid);
	(*mid)->r=build(mid+1,end);
	(*mid)->update();
	return *mid;
}

int left,right,loc,v;

void query(node *cur,int beg,int end){
	if(!cur||beg>=right||end<=left) return;
	if(beg>=left&&end<=right){
		rot[len++]=cur->t;
		return;
	}
	int mid=beg+(cur->l?cur->l->size:0)+1;
	if(mid>left&&mid<=right)
		val[len2++]=cur->a;
	query(cur->l,beg,mid-1);
	query(cur->r,mid,end);
}

void modify(node *cur,int beg,int end){
	int mid=beg+(cur->l?cur->l->size:0)+1;
	if(loc<mid)
		modify(cur->l,beg,mid-1);
	else
	if(loc>mid)
		modify(cur->r,mid,end);
	else
	if(D==-1)
		X=cur->a;
	else
		cur->a=X;
	seg *tmp=insert(cur->t,0,M); delseg(cur->t); cur->t=tmp;
}

void insert(node *&cur,int beg,int end){
	if(cur){
		int mid=beg+(cur->l?cur->l->size:0)+1;
		if(loc<=mid)
			insert(cur->l,beg,mid-1);
		else
			insert(cur->r,mid,end);
	}
	else{
		cur=newnode++;
		cur->size=0;
		cur->a=X;
		D=1;
		cur->t=NULL;
	}
	cur->size++;
	seg *tmp=insert(cur->t,0,M); delseg(cur->t); cur->t=tmp;
	if(cur->l&&cur->l->size>cur->size*alpha||cur->r&&cur->r->size>cur->size*alpha){
		len=0;
		dfs(cur);
		cur=build(seq,seq+len);
	}
}

int main(){
	initmemseg();
	scanf("%d",&n);
	for(int i=1;i<=n;i++) scanf("%d",&V[i].a),seq[i]=V+i;
	root=build(seq+1,seq+n+1);
	newnode=V+n+1;
	int q; scanf("%d",&q);
	int lastans=0;
	while(q--){
		char c=getchar();
		if(c=='Q'){
			int k; scanf("%d%d%d",&left,&right,&k); left^=lastans,right^=lastans,k^=lastans; left--;
			len=len2=0;
			query(root,0,n);
			int beg=0,end=M;
			while(end-beg>1){
				int mid=beg+end>>1;
				int cnt=0;
				for(int i=0;i<len;i++) cnt+=rot[i]?rot[i]->l?rot[i]->l->sum:0:0;
				for(int i=0;i<len2;i++) cnt+=val[i]>=beg&&val[i]<mid;
				if(cnt<k){
					k-=cnt;
					beg=mid;
					for(int i=0;i<len;i++) if(rot[i]) rot[i]=rot[i]->r;
				}
				else{
					end=mid;
					for(int i=0;i<len;i++) if(rot[i]) rot[i]=rot[i]->l;
				}
			}
			printf("%d\n",lastans=beg);
		}
		else
		if(c=='M'){
			scanf("%d",&loc); loc^=lastans;
			D=-1;
			modify(root,0,n);
			scanf("%d",&X); X^=lastans;
			D=1;
			modify(root,0,n);
		}
		else
		if(c=='I'){
			scanf("%d%d",&loc,&X); loc^=lastans,X^=lastans;
			insert(root,0,n);
			n++;
		}
		else
			q++;
	}
}
