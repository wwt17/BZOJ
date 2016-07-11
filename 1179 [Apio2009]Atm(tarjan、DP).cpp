#include <cstdio>
int N,M,i,a,b,S,P;
struct node;
struct edge{
	node *ed; edge *next;
} E[500000],*newE=E;
struct node{
	edge *son; int dfn,low,money,goin,f; bool instack; node *belong;
	void tarjan(){
		static int index=0;
		static node *stack[500000],**top=stack;
		*top++=this; instack=true;
		low=dfn=++index;
		edge *e;
		for(e=son;e;e=e->next)
			if(!e->ed->dfn){
				e->ed->tarjan();
				if(e->ed->low<low) low=e->ed->low;
			}
			else if(e->ed->instack&&e->ed->dfn<low) low=e->ed->dfn;
		if(low==dfn){
			while(true){
				top--;
				(*top)->belong=this;
				(*top)->instack=false;
				if(*top==this) break;
				if((*top)->son){
					for(e=(*top)->son;e->next;e=e->next);
					e->next=son;
					son=(*top)->son;
				}
				money+=(*top)->money;
			}
			edge **pre=&son;
			for(e=son;e;e=e->next)
				if(e->ed->belong==this)
					*pre=e->next;
				else
					pre=&e->next;
		}
	}
	void getgoin(){
		if(goin++) return;
		for(edge* e=son;e;e=e->next)
			(e->ed=e->ed->belong)->getgoin();
	}
	void getf(){
		if(--goin) return;
		f+=money;
		int res=0; node* v;
		for(edge* e=son;e;e=e->next){
			if((v=e->ed)->f<f) v->f=f;
			v->getf();
		}
	}
} V[500000];
int main(){
	scanf("%u%u",&N,&M);
	while(M--){
		scanf("%u%u",&a,&b);
		*newE=(edge){V+b,V[a].son},V[a].son=newE++;
	}
	for(int i=1;i<=N;i++) scanf("%u",&V[i].money);
	for(int i=1;i<=N;i++) if(!V[i].dfn) V[i].tarjan();
	scanf("%u%u",&S,&P);
	V[S].belong->getgoin();
	V[S].belong->getf();
	int Ans=0;
	while(P--){
		scanf("%u",&a);
		if(Ans<V[a].belong->f) Ans=V[a].belong->f;
	}
	printf("%u\n",Ans);
}
