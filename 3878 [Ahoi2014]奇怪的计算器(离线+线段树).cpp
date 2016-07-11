#include <cstdio>
#include <algorithm>
using namespace std;
typedef long long ll;

const int M=(int)1e5+5,N=(int)1e5+5;

int n,m,L,R,ans[N];

struct data{
	int val,id;
	friend bool operator < (const data &a,const data &b){
		return a.val<b.val;
	}
} a[N];

struct seg{
	ll mul,cnt,add,mi,ma,vi,va,cov;
	void cover(ll d){
		cov=d;
		mul=1;
		cnt=0;
		add=0;
		vi=d;
		va=d;
	}
	void mult(ll d){
		mul*=d;
		cnt*=d;
		add*=d;
		vi*=d;
		va*=d;
	}
	void inc(ll d){
		add+=d;
		vi+=d;
		va+=d;
	}
	void inct(ll d){
		cnt+=d;
		vi+=mi*d;
		va+=ma*d;
	}
	void down(seg &l,seg &r){
		if(cov){
			l.cover(cov);
			r.cover(cov);
			cov=0;
		}
		if(mul!=1){
			l.mult(mul);
			r.mult(mul);
			mul=1;
		}
		if(cnt){
			l.inct(cnt);
			r.inct(cnt);
			cnt=0;
		}
		if(add){
			l.inc(add);
			r.inc(add);
			add=0;
		}
	}
	void update(seg &l,seg &r){
		mi=l.mi;
		vi=l.vi;
		ma=r.ma;
		va=r.va;
	}
} t[N*4];

void build(int cur=1,int beg=0,int end=n){
	if(end-beg==1){
		t[cur].mi=t[cur].ma=a[end].val;
		return;
	}
	int mid=beg+end>>1;
	build(cur<<1,beg,mid);
	build(cur<<1|1,mid,end);
	t[cur].update(t[cur<<1],t[cur<<1|1]);
}

void getans(int cur=1,int beg=0,int end=n){
	if(end-beg==1){
		ans[a[end].id]=t[cur].va;
		return;
	}
	int mid=beg+end>>1;
	t[cur].down(t[cur<<1],t[cur<<1|1]);
	getans(cur<<1,beg,mid);
	getans(cur<<1|1,mid,end);
}

void cover(int L,int R,int D,int cur=1,int beg=0,int end=n){
	if(end<=L||beg>=R) return;
	if(beg>=L&&end<=R){
		t[cur].cover(D);
		return;
	}
	int mid=beg+end>>1;
	cover(L,R,D,cur<<1,beg,mid);
	cover(L,R,D,cur<<1|1,mid,end);
	t[cur].update(t[cur<<1],t[cur<<1|1]);
}

void dealL(int cur=1,int beg=0,int end=n){
	if(t[cur].vi>=L) return;
	if(end-beg==1){
		cover(0,end,L);
		return;
	}
	t[cur].down(t[cur<<1],t[cur<<1|1]);
	int mid=beg+end>>1;
	if(t[cur<<1|1].vi<L)
		dealL(cur<<1|1,mid,end);
	else
		dealL(cur<<1,beg,mid);
}
void dealR(int cur=1,int beg=0,int end=n){
	if(t[cur].va<=R) return;
	if(end-beg==1){
		cover(beg,n,R);
		return;
	}
	t[cur].down(t[cur<<1],t[cur<<1|1]);
	int mid=beg+end>>1;
	if(t[cur<<1].va>R)
		dealR(cur<<1,beg,mid);
	else
		dealR(cur<<1|1,mid,end);
}

struct opt{
	char c; int d;
	void read(){
		for(;;){
			bool ok;
			switch(c=getchar()){
				case '+':
				case '-':
				case '*':
				case '@':
					ok=true;
					break;
				default:
					ok=false;
			}
			if(ok) break;
		}
		scanf("%d",&d);
	}
	void work(){
		if(c=='+'){
			t[1].inc(d);
			dealR();
		}
		else
		if(c=='-'){
			t[1].inc(-d);
			dealL();
		}
		else
		if(c=='*'){
			t[1].mult(d);
			dealR();
		}
		else
		if(c=='@'){
			t[1].inct(d);
			dealR();
		}
		else
			printf("Err c=%c\n",c);
	}
} seq[M];

int main(){
	scanf("%d%d%d",&m,&L,&R);
	for(int i=1;i<=m;i++) seq[i].read();
	seq[0]=(opt){'@',1};
	scanf("%d",&n);
	for(int i=1;i<=n;i++) scanf("%d",&a[i].val),a[i].id=i;
	sort(a+1,a+n+1);
	build();
	for(int i=0;i<=m;i++){
		seq[i].work();
	}
	getans();
	for(int i=1;i<=n;i++) printf("%d\n",ans[i]);
	puts("");
}
