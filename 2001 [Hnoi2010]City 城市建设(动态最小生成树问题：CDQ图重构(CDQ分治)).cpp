/*
对修改CDQ分治。
对于当前修改区间，我们考虑当前区间内的修改对图的影响。

Contraction:
把所有被修改的边权设为-oo，做Kruskal，
那些不被修改而在最小生成树中的边一定在当前区间所有询问后的最小生成树中。
所以可以把这些边缩起来。

Reduction:
把所有被修改的边权设为+oo，做Kruskal，
那些不被修改而不在最小生成树中的边一定不在当前区间所有询问后的最小生成树中。
所以可以把这些边删除。

这样图的规模就减小了。递归左右两边。

设当前区间询问数为K，图的规模经缩小后：
点数≤K+1：
	证明：在Contraction操作后，生成树边数为K。
边数≤2K：
	证明：在Reduction操作中最坏情况是+oo的边全都不在生成树中，由于点数为K+1，故该生成树边数为K。再加上所有被修改边，共2K。 

故有复杂度：O(Q log Q (log Q + α(Q)))
*/
#include <cstdio>
#include <algorithm>
using namespace std;
const int N=20100,M=50100,Q=50100,logQ=18,inf=(int)1e9;
int n,m,q;
long long ans;

int memw[M];

struct edge{
	int u,v,*w,flag,lab;
	void read(){
		scanf("%d%d%d",&u,&v,w);
		u--;
		v--;
	}
} memE[Q*2*2];
struct modi{
	int e,d;
	void read(){
		scanf("%d%d",&e,&d);
		e--;
	}
} memseq[Q*2];
int tmp[Q];
int belong[N];
int get(int x){
	if(belong[x]==x) return x;
	return belong[x]=get(belong[x]);
}
edge *ord[M];
bool cho[M];
int lab[N];

bool cmp(const edge* i,const edge* j){
	return *i->w<*j->w;
}
long long kruskal(int n,edge *E,int m){
	long long ret=0;
	for(int i=0;i<m;i++) ord[i]=E+i;
	sort(ord,ord+m,cmp);
	for(int i=0;i<n;i++) belong[i]=i;
	for(int i=0;i<m;i++){
		int x=get(ord[i]->u),y=get(ord[i]->v);
		if(cho[ord[i]-E]=x!=y)
			belong[x]=y,
			ret+=*ord[i]->w;
	}
	return ret;
}

void work(modi *seq,int q,int n,edge *E,int m){
	for(int i=0;i<m;i++) E[i].flag=0;
	if(q==1){
		*E[seq->e].w=seq->d;
		printf("%lld\n",ans+kruskal(n,E,m));
		return;
	}
	for(int i=0;i<q;i++){
		tmp[i]=*E[seq[i].e].w;
		*E[seq[i].e].w=-inf;
	}
	kruskal(n,E,m);
	for(int i=0;i<m;i++) if(cho[i]&&*E[i].w!=-inf)
		E[i].flag=1;
	for(int i=0;i<q;i++)
		*E[seq[i].e].w=inf;
	kruskal(n,E,m);
	for(int i=0;i<m;i++) if(!cho[i]&&*E[i].w!=inf)
		E[i].flag=2;
	for(int i=q-1;i>=0;i--)
		*E[seq[i].e].w=tmp[i];
	for(int i=0;i<n;i++) belong[i]=i;
	edge *tE=E+m;
	int mm=0;
	for(int i=0;i<m;i++){
		if(E[i].flag==0)
			tE[E[i].lab=mm++]=E[i];
		else
		if(E[i].flag==1)
			belong[get(E[i].u)]=get(E[i].v),
			ans+=*E[i].w;
	}
	int nn=0;
	for(int i=0;i<n;i++)
		if(get(i)==i)
			lab[i]=nn++;
	for(int i=0;i<mm;i++)
		tE[i].u=lab[get(tE[i].u)],
		tE[i].v=lab[get(tE[i].v)];
	int mid=q/2;
	int qq=0;
	modi *tseq=seq+q;
	for(int i=0;i<mid;i++){
		tseq[qq]=seq[i];
		tseq[qq].e=E[tseq[qq].e].lab;
		qq++;
	}
	work(tseq,qq,nn,tE,mm);
	qq=0;
	for(int i=mid;i<q;i++){
		tseq[qq]=seq[i];
		tseq[qq].e=E[tseq[qq].e].lab;
		qq++;
	}
	work(tseq,qq,nn,tE,mm);
	for(int i=0;i<m;i++)
		if(E[i].flag==1)
			ans-=*E[i].w;
}

int main(){
	scanf("%d%d%d",&n,&m,&q);
	for(int i=0;i<m;i++){
		memE[i].w=memw+i;
		memE[i].read();
	}
	for(int i=0;i<q;i++)
		memseq[i].read();
	work(memseq,q,n,memE,m);
}
