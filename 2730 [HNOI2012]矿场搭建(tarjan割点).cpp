#include <cstdio>
const int N=501,M=N;
int n,m,cnt; long long Ans;
int w,now,sum[N],flag[N];
struct node;
struct edge{
	node *ed; edge *next;
} E[M<<1],*newE;
struct node{
	edge *son; node *pa; int dfn,low; bool instack,p;
	void init(){
		son=NULL; pa=NULL; dfn=low=instack=p=0;
	}
	void tarjan(){
		static int index=0;
		static node *stack[N],**top=stack;
		dfn=low=++index;
		*top++=this;
		instack=true;
		for(edge *e=son;e;e=e->next) if(e->ed!=pa)
			if(!e->ed->dfn){
				e->ed->pa=this;
				e->ed->tarjan();
				if(e->ed->low<low) low=e->ed->low;
				if(e->ed->low>=dfn){
					p=true;
					if(!pa) w++;
					now++;
					flag[now]=sum[now]=0;
					do{
						(*--top)->instack=false;
						sum[now]++;
						flag[now]+=(*top)->p;
					} while(*top!=e->ed);
				}
			}
			else
				if(e->ed->instack&&e->ed!=pa&&e->ed->low<low) low=e->ed->low;
	}
} V[N];
int main(){
	for(int Case=1;scanf("%d",&m),m;Case++){
		n=0;
		newE=E;
		for(int i=0;i<m;i++){
			static int x,y; scanf("%d%d",&x,&y);
			while(n<x) V[++n].init();
			while(n<y) V[++n].init();
			*newE=(edge){V+y,V[x].son},V[x].son=newE++;
			*newE=(edge){V+x,V[y].son},V[y].son=newE++;
		}
		now=0;
		for(int i=1;i<=n;i++) if(!V[i].dfn){
			w=0;
			V[i].tarjan();
			if(w==1) flag[now]--;
		}
		cnt=0;
		Ans=1;
		for(int i=1;i<=now;i++) if(!flag[i])
			cnt++,Ans*=sum[i];
		printf("Case %d: ",Case);
		if(!cnt) printf("2 %lld\n",(long long)n*(n-1)/2);
		else printf("%d %lld\n",cnt,Ans);
	}
}
