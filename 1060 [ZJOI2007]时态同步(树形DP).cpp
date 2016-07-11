#include <cstdio>
const int N=500005;
int n,s;
struct node;
struct edge{
	node *ed; edge *next; int w;
} E[N<<1],*newE=E;
struct node{
	edge *son; node *pa; long long d,f;
	void dp(){
		int cnt=0;
		for(edge *e=son;e;e=e->next) if(e->ed!=pa){
			e->ed->pa=this;
			e->ed->dp();
			f+=e->ed->f;
			long long t=e->w+e->ed->d;
			if(t<=d)
				f+=d-t;
			else{
				f+=cnt*(t-d);
				d=t;
			}
			cnt++;
		}
	}
} V[N];
int main(){
	scanf("%d%d",&n,&s);
	for(int i=1;i<n;i++){
		static int a,b,c; scanf("%d%d%d",&a,&b,&c);
		*newE=(edge){V+b,V[a].son,c},V[a].son=newE++;
		*newE=(edge){V+a,V[b].son,c},V[b].son=newE++;
	}
	V[s].dp();
	printf("%I64d\n",V[s].f);
	scanf("\n");
}
