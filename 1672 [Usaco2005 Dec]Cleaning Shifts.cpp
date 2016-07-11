#include <cstdio>
#include <algorithm>
using namespace std;
#define INF 0x70000000
#define INF_bound 0x60000000
#define size 10005
int N,S,T,i;
struct cow{
	int s,t,pay,f;
	void read(){
		scanf("%d%d%d",&s,&t,&pay);
		--s;
		f=INF;
	}
} c[size],*t[size],*s[size],**top,**tmp;
bool cmpt(const cow* a,const cow* b)
	{ return a->t < b->t; }
bool cmpf(const cow* a,const cow* b)
	{ return a->f < b->f; }
int main(){
	scanf("%d%d%d",&N,&S,&T);
	N+=2;
	c[1]=(cow){S,S,0,0}; t[1]=c+1;
	for(i=2;i<N;++i) c[i].read(),t[i]=c+i;
	c[i]=(cow){T,T,0,INF}; t[i]=c+i;
	sort(t+2,t+N,cmpt);
	c[0].f=INF;
	i=1;
	*(top=s)=t[i];
	++top;
	for(i=2;i<=N;++i){
		c->t=t[i]->s;
		tmp=lower_bound(s,top,c,cmpt);
		if(tmp==top) continue;
		t[i]->f=(*tmp)->f+t[i]->pay;
		*(top=lower_bound(s,top,t[i],cmpf))=t[i];
		++top;
	}
	printf("%d\n",c[N].f>INF_bound?-1:c[N].f);
}
