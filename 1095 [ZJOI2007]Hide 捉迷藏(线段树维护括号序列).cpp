//http://www.shuizilong.com/house/archives/bzoj-1095-zjoi2007hide-%E6%8D%89%E8%BF%B7%E8%97%8F/
#include <cstdio>
#include <algorithm>
using namespace std;
#define max3(a,b,c) max(max(a,b),c)
#define max4(a,b,c,d) max(max(a,b),max(c,d))
const int N=100000,inf=N;
int n,m;
struct node;
struct edge{
	node *ed; edge *next;
} E[N*2],*newE=E;
struct node{
	edge *son; node *pa; bool dark; int loc;
	void dfs();
	void change();
} V[N+1];
struct data{
	int ls,rs,rp,rm,lp,lm,dis;
} t[N*3*4];
char seq[N*3]; int num[N*3],cnt,darks;
void node::dfs(){
	dark=true;
	seq[loc=cnt++]='1';
	for(edge* e=son;e;e=e->next) if(e->ed!=pa){
		e->ed->pa=this;
		seq[cnt++]='[';
		e->ed->dfs();
		seq[cnt++]=']';
	}
}
void update(int i){
	#define S t[i]
	#define S1 t[i<<1]
	#define S2 t[i<<1|1]
	#define a S1.ls
	#define b S1.rs
	#define c S2.ls
	#define d S2.rs
	if(b<c) S.ls=a-b+c,S.rs=d; else S.ls=a,S.rs=b-c+d;
	S.dis=max4(S1.dis,S1.rm+S2.lp,S1.rp+S2.lm,S2.dis);
	S.rp=max3(S1.rp-c+d,S1.rm+c+d,S2.rp);
	S.rm=max(S1.rm+c-d,S2.rm);
	S.lp=max3(S2.lp-b+a,S2.lm+b+a,S1.lp);
	S.lm=max(S2.lm+b-a,S1.lm);
	#undef a
	#undef b
	#undef c
	#undef d
}
void build(int i,int l,int r){
	if(r-l==1){
		num[l]=i;
		t[i].ls=seq[l]==']';
		t[i].rs=seq[l]=='[';
		t[i].rp=t[i].rm=t[i].lp=t[i].lm=t[i].dis=seq[l]=='1'?0:-inf;
		return;
	}
	build(i<<1,l,(l+r)>>1);
	build(i<<1|1,(l+r)>>1,r);
	update(i);
}
void node::change(){
	if(dark^=1) darks++; else darks--;
	seq[loc]^=1;
	int i=num[loc];
	t[i].rp=t[i].rm=t[i].lp=t[i].lm=t[i].dis=-inf-t[i].dis;
	while(i>>=1) update(i);
}
int main(){
	scanf("%u",&n);
	int i;
	for(i=1;i<n;i++){
		static int a,b;
		scanf("%u%u",&a,&b);
		*newE=(edge){V+b,V[a].son},V[a].son=newE++;
		*newE=(edge){V+a,V[b].son},V[b].son=newE++;
	}
	V[1].dfs();
	build(1,0,cnt);
	darks=n;
	scanf("%u",&m);
	while(m--)
		if(scanf("\n"),getchar()=='C'){
			scanf("%u",&i);
			V[i].change();
		}
		else printf("%d\n",darks==1?1:darks==0?-1:t[1].dis);
}
