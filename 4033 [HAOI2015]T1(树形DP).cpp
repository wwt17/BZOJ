#include <cstdio>
#include <algorithm>
using namespace std;
typedef long long ll;

const int N=2005;

int n,k;

struct node;
struct edge{
	node *ed;
	edge *next;
	int w;
} E[N<<1],*newE=E;
struct node{
	node *pa;
	edge *son;
	int size;
	ll f[N];
	void dp(){
		size=1;
		f[0]=0;
		f[1]=0;
		for(edge *e=son;e;e=e->next) if(e->ed!=pa){
			node *v=e->ed;
			v->pa=this;
			v->dp();
			for(int i=0;i<=v->size;i++){
				if(i>k){
					v->f[i]=0;
					continue;
				}
				v->f[i]+=1LL*e->w*(i*(k-i)+(v->size-i)*(n-v->size-k+i));
			}
			static ll g[N];
			for(int i=0;i<=size+v->size;i++) g[i]=0;
			for(int i=0;i<=size;i++)
				for(int j=0;j<=v->size;j++)
					g[i+j]=max(g[i+j],f[i]+v->f[j]);
			for(int i=0;i<=size+v->size;i++) f[i]=g[i];
			size+=v->size;
		}
	}
} V[N];

int main(){
	scanf("%d%d",&n,&k);
	for(int i=1;i<n;i++){
		int x,y,z; scanf("%d%d%d",&x,&y,&z);
		*newE=(edge){V+y,V[x].son,z},V[x].son=newE++;
		*newE=(edge){V+x,V[y].son,z},V[y].son=newE++;
	}
	V[1].dp();
	printf("%lld\n",V[1].f[k]);
}
