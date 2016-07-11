#include <cstdio>
const int N=101,M=1000;
int n,m,now;
struct node;
struct edge{
	node *ed; edge *next;
} E[M<<1],*newE;
struct node{
	edge *son; int dfn,low; bool instack; int belong;
	void init(){
		son=NULL;
		dfn=belong=0;
	}
	void tarjan(){
		static node *stack[N],**top=stack;
		static int index=0;
		dfn=low=++index;
		instack=true;
		*top++=this;
		for(edge *e=son;e;e=e->next)
			if(!e->ed->dfn){
				e->ed->tarjan();
				if(e->ed->low<low) low=e->ed->low;
			}
			else
				if(e->ed->instack&&e->ed->low<low) low=e->ed->low;
		if(dfn==low){
			now++;
			do{
				(*--top)->instack=false;
				(*top)->belong=now;
			} while(*top!=this);
		}
	}
} V[N][2];
inline bool geth(){
	for(;;)
		switch(getchar()){
			case 'm': return false;
			case 'h': return true;
		}
}
int main(){
	int k; scanf("%d",&k);
	while(k--){
		newE=E; now=0;
		scanf("%d%d",&n,&m);
		for(int i=1;i<=n;i++)
			for(int h=0;h<2;h++)
				V[i][h].init();
		for(int i=0;i<m;i++){
			bool hx=geth();
			int x; scanf("%d",&x);
			bool hy=geth();
			int y; scanf("%d",&y);
			*newE=(edge){&V[y][hy],V[x][!hx].son},V[x][!hx].son=newE++;
			*newE=(edge){&V[x][hx],V[y][!hy].son},V[y][!hy].son=newE++;
		}
		for(int i=1;i<=n;i++){
			for(int h=0;h<2;h++) if(!V[i][h].dfn)
				V[i][h].tarjan();
			if(V[i][0].belong==V[i][1].belong){
				puts("BAD");
				goto end;
			}
		}
		puts("GOOD");
		end:;
	}
}
