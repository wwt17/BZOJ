#include <cstdio>
#include <cstring>
#define N 10001
#define MAXA 1000000000
int left,right,mid;
struct Set;
struct Set{
	struct seg_tree{
		seg_tree *l,*r; int cnt;
		seg_tree():l(NULL),r(NULL),cnt(0){
		}
		/*
		seg_tree(seg_tree* _l,seg_tree* _r,int _cnt):
			l(_l),r(_r),cnt(_cnt){
		}
		*/
	} *t;
	Set():t(NULL){
	}
	/*
	Set(seg_tree* _t):t(_t){
	}
	seg_tree* copy(seg_tree* b){
		if(!b) return NULL;
		return new seg_tree(copy(b->l),copy(b->r),b->cnt);
	}
	Set(const Set &b):t(copy(b.t)){
	}
	*/
	#define INIT() int left=0,right=MAXA,mid; seg_tree* *x=&t;
	Set& operator += (const int c){
		INIT();
		while(true){
			mid=(left+right)>>1;
			if(!*x) *x=new seg_tree;
			(*x)->cnt++;
			if(c<mid) x=&(*x)->l,right=mid-1; else
			if(mid<c) x=&(*x)->r,left=mid+1; else
			break;
		}
		return *this;
	}
	Set& operator -= (const int c){
		INIT();
		seg_tree* &tmp=t;
		while(true){
			mid=(left+right)>>1;
			if(!*x) *x=new seg_tree;
			(*x)->cnt--;
			if(c<mid) x=&(*x)->l,right=mid-1; else
			if(mid<c) x=&(*x)->r,left=mid+1; else
			break;
		}
		return *this;
	}
	void insert(seg_tree* &a,seg_tree* &b){
		if(!b) return;
		if(!a) a=new seg_tree;
		a->cnt+=b->cnt;
		insert(a->l,b->l);
		insert(a->r,b->r);
	}
	Set& operator += (Set &b){
		insert(t,b.t);
		return *this;
	}
	void remove(seg_tree* &a,seg_tree* &b){
		if(!b) return;
		if(!a) a=new seg_tree;
		static seg_tree* *tmp;
		remove(a->l,b->l);
		remove(a->r,b->r);
		if(!(a->cnt-=b->cnt)){ delete a; a=NULL; }
	}
	/*
	Set& operator -= (Set &b){
		remove(t,b.t);
		return *this;
	}
	Set operator - (Set b){
		return (Set)(*this)-=b;
	}
	int nth(int n){
		INIT();
		int sum;
		while(true){
			mid=(left+right)>>1;
			if(n<=((*x)->l?(*x)->l->cnt:0)) x=&(*x)->l,right=mid-1; else
			if(n>(sum=(*x)->cnt-((*x)->r?(*x)->r->cnt:0))) x=&(*x)->r,left=mid+1,n-=sum; else
			return mid;
		}
		return -1;
	}
	*/
} s[N],sx[N],sy[N],*topx,*topy,*p;
bool flag[N];
int nth(int i,int j,int n){
	left=0,right=MAXA;
	i--;
	int x,y,sum;
	for(topx=sx,topy=sy,x=i,y=j;x!=y;x>y?(*topx++=s[x],x-=x&-x):(*topy++=s[y],y-=y&-y));
	while(true){
		mid=(left+right)>>1;
		sum=0;
		for(p=sx;p<topx;p++) p->t&&p->t->l?sum-=p->t->l->cnt:0;
		for(p=sy;p<topy;p++) p->t&&p->t->l?sum+=p->t->l->cnt:0;
		if(n<=sum){
			for(p=sx;p<topx;p++) p->t?p->t=p->t->l:0;
			for(p=sy;p<topy;p++) p->t?p->t=p->t->l:0;
			right=mid-1;
			continue;
		}
		sum=0;
		for(p=sx;p<topx;p++) p->t?sum-=p->t->cnt-(p->t->r?p->t->r->cnt:0):0;
		for(p=sy;p<topy;p++) p->t?sum+=p->t->cnt-(p->t->r?p->t->r->cnt:0):0;
		if(n>sum){
			for(p=sx;p<topx;p++) p->t?p->t=p->t->r:0;
			for(p=sy;p<topy;p++) p->t?p->t=p->t->r:0;
			left=mid+1;
			n-=sum;
			continue;
		}
		return mid;
	}
}
int n,m,i,j,k,t,a[N];
char opt;
/*
inline Set prefix(int x){
	Set ret;
	for(;x;x-=x&-x)
		ret+=s[x];
	return ret;
}
*/
inline void modify(int x,const int a,const int b){
	for(;x<=n;x+=x&-x){
		s[x]-=a;
		s[x]+=b;
	}
}
int main(){
	scanf("%u%u",&n,&m);
	for(i=1;i<=n;i++){
		scanf("%u",a+i);
		s[i]+=a[i];
		if(i+(i&-i)<=n)
			s[i+(i&-i)]+=s[i];
	}
	while(m--)
		switch(scanf("\n"),getchar()){
			case 'Q': scanf("%u%u%u",&i,&j,&k);
				printf("%u\n",nth(i,j,k));
				break;
			case 'C': scanf("%u%u",&i,&t);
				modify(i,a[i],t);
				a[i]=t;
		}
	scanf("%u");
}
