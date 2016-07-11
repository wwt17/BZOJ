#include <cstdio>
#include <map>
using namespace std;
typedef long long ll;
const int N=1e5+5,P=1e9+7;
int n;
struct tree{
	tree *l,*r;
	int sum[3];
	tree():l(NULL),r(NULL){
		sum[0]=sum[1]=sum[2]=0;
	}
};
int D,D2;
ll ans[3];
struct vec{
	ll x,y;
	void read(){
		scanf("%I64d%I64d\n",&x,&y);
	}
	void add();
	void del();
	int query();
} L[N],*R,*X,*l,*r;
void insert(tree *&cur,vec *beg,vec *end){
	if(!cur) cur=new tree;
	cur->sum[0]++;
	(cur->sum[1]+=D)%=P;
	(cur->sum[2]+=D2)%=P;
	if(end-beg>1){
		vec *mid=beg+(end-beg>>1);
		if(X<mid)
			insert(cur->l,beg,mid);
		else
			insert(cur->r,mid,end);
	}
}
void erase(tree *&cur,vec *beg,vec *end){
	if(end-beg>1){
		vec *mid=beg+(end-beg>>1);
		if(X<mid)
			erase(cur->l,beg,mid);
		else
			erase(cur->r,mid,end);
	}
	(cur->sum[1]-=D)%=P;
	(cur->sum[2]-=D2)%=P;
	if(!--cur->sum[0]){
		delete cur;
		cur=NULL;
	}
}
void query(tree *cur,vec *beg,vec *end){
	if(!cur||l>=end||r<=beg) return;
	if(l<=beg&&r>=end){
		ans[0]+=cur->sum[0];
		ans[1]+=cur->sum[1];
		ans[2]+=cur->sum[2];
		return;
	}
	vec *mid=beg+(end-beg>>1);
	if(l<mid) query(cur->l,beg,mid);
	if(r>mid) query(cur->r,mid,end);
}
map<ll,tree*> sx,sy;
void vec::add(){
	X=this;
	D=y%P;
	D2=(ll)D*D%P;
	insert(sx[x],L,R);
	D=x%P;
	D2=(ll)D*D%P;
	insert(sy[y],L,R);
}
void vec::del(){
	X=this;
	D=y%P;
	D2=(ll)D*D%P;
	erase(sx[x],L,R);
	D=x%P;
	D2=(ll)D*D%P;
	erase(sy[y],L,R);
}
int vec::query(){
	X=this;
	ll res=0;
	ans[0]=ans[1]=ans[2]=0;
	::query(sx[x],L,R);
	int yy=y%P;
	res+=ans[2]%P-2*ans[1]%P*yy%P+ans[0]%P*yy%P*yy%P;
	ans[0]=ans[1]=ans[2]=0;
	::query(sy[y],L,R);
	int xx=x%P;
	res+=ans[2]%P-2*ans[1]%P*xx%P+ans[0]%P*xx%P*xx%P;
	return (res%P+P)%P;
}
int main(){
	scanf("%d%*d",&n);
	R=L+n;
	for(int i=0;i<n;i++){
		L[i].read();
		L[i].add();
	}
	int t; scanf("%d",&t);
	int lastans=0,x,a,b;
	ll d;
	while(t--)
		switch(getchar()){
			case 'U': scanf("%d%I64d",&x,&d);
				x^=lastans;
				x--;
				L[x].del();
				L[x].y+=d;
				L[x].add();
				break;
			case 'D': scanf("%d%I64d",&x,&d);
				x^=lastans;
				x--;
				L[x].del();
				L[x].y-=d;
				L[x].add();
				break;
			case 'L': scanf("%d%I64d",&x,&d);
				x^=lastans;
				x--;
				L[x].del();
				L[x].x-=d;
				L[x].add();
				break;
			case 'R': scanf("%d%I64d",&x,&d);
				x^=lastans;
				x--;
				L[x].del();
				L[x].x+=d;
				L[x].add();
				break;
			case 'Q': scanf("%d%d%d",&x,&a,&b);
				x^=lastans;
				x--;
				l=L+(a-1);
				r=L+b;
				printf("%d\n",lastans=L[x].query());
				break;
			default: t++;
		}
	scanf("\n");
}
