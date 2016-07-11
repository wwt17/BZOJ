#include <cstdio>
#include <vector>
using namespace std;

inline void maxi(int &a,const int b){
	if(b>a) a=b;
}

const int N=1005,M=5005,D=10;

int n,m;
int lg[1<<D];
int x[M],y[M],z[M];
int p[M];

struct node;
struct data{
	int id;
	int last;
	int sum;
};
struct edge{
	node *ed;
	edge *next;
} E[N<<1],*newE=E;
struct node{
	edge *son;
	int col;
	void build(node *fa=NULL,int c=0){
		col=c;
		for(edge *e=son;e;e=e->next) if(e->ed!=fa)
			e->ed->build(this,c^1);
	}
	int d;
	node *q[10];
	int f[1<<D],g[D],h;
	vector<data> lis;
	void dfs(node *fa=NULL){
		for(edge *e=son;e;e=e->next){
			node *v=e->ed;
			if(v==fa) continue;
			v->dfs(this);
			for(vector<data>::iterator it=v->lis.begin();it!=v->lis.end();it++)
				lis.push_back((data){it->id,d,it->sum});
			q[d++]=v;
		}
		f[0]=0;
		for(int s=1;s<1<<d;s++){
			f[s]=f[s^(s&-s)]+q[lg[s&-s]]->h;
		}
		for(int i=0;i<(int)lis.size();i++){
			if(p[lis[i].id]){
				int j=p[lis[i].id]-1,x=lis[i].last,y=lis[j].last;
				for(int s=0;s<1<<d;s++) if((x==-1||!(s>>x&1))&&(y==-1||!(s>>y&1)))
					maxi(f[s|(x==-1?0:1<<x)|(y==-1?0:1<<y)],f[s]+lis[i].sum+lis[j].sum+z[lis[i].id]);
				p[lis[i].id]=-1;
			}
			else
				p[lis[i].id]=i+1;
		}
		for(int x=0;x<d;x++){
			g[x]=0;
			for(int s=0;s<1<<d;s++) if(!(s>>x&1))
				maxi(g[x],f[s]);
		}
		h=0;
		for(int s=0;s<1<<d;s++)
			maxi(h,f[s]);
		int j=0;
		for(int i=0;i<(int)lis.size();i++){
			if(p[lis[i].id]!=-1)
				lis[j++]=lis[i];
			p[lis[i].id]=0;
		}
		lis.resize(j);
		for(int i=0;i<(int)lis.size();i++){
			lis[i].sum+=lis[i].last==-1?h:g[lis[i].last];
		}
	}
} V[N];

int main(){
	for(int i=0;i<D;i++) lg[1<<i]=i;
	scanf("%d%d",&n,&m);
	int ans=0;
	for(int i=1;i<=m;i++){
		scanf("%d%d%d",&x[i],&y[i],&z[i]);
		ans+=z[i];
		if(!z[i]){
			*newE=(edge){V+y[i],V[x[i]].son},V[x[i]].son=newE++;
			*newE=(edge){V+x[i],V[y[i]].son},V[y[i]].son=newE++;
		}
	}
	V[1].build();
	for(int i=1;i<=m;i++) if(z[i]&&V[x[i]].col==V[y[i]].col){
		V[x[i]].lis.push_back((data){i,-1,0});
		V[y[i]].lis.push_back((data){i,-1,0});
	}
	V[1].dfs();
	printf("%d\n",ans-V[1].h);
}
