#include <cstdio>
int n,m;
struct node;
struct edge{
	node* ed;
	edge* next;
} E[300000],*newE=E;
struct node{
	edge* son; int dfn,low,belong; bool instack;
	void tarjan();
} V[100000];
int ind[100000],sum[100000],kind;
void node::tarjan(){
	static node *s[100000],**top=s;
	static int index=0;
	instack=true;
	*top++=this;
	low=dfn=++index;
	for(edge* e=son;e;e=e->next)
		if(!e->ed->dfn){
			e->ed->tarjan();
			if(e->ed->low<low)
				low=e->ed->low;
		}
		else
			if(e->ed->instack&&e->ed->low<low)
				low=e->ed->low;
	if(low==dfn){
		kind++;
		do
			(*--top)->instack=false,
			sum[(*top)->belong=kind]++;
		while(*top!=this);
	}
}
int main(){
	scanf("%u%u",&n,&m);
	int x,y;
	while(m--){
		scanf("%u%u",&x,&y);
		*newE=(edge){V+y,V[x].son},V[x].son=newE++;
	}
	for(node* u=V+1;u<=V+n;u++) if(!u->dfn)
		u->tarjan();
	for(node* u=V+1;u<=V+n;u++)
		for(edge* e=u->son;e;e=e->next)
			if(u->belong!=e->ed->belong)
				ind[e->ed->belong]++;
	int ans=0; bool s1=false;
	for(int i=1;i<=kind;i++) if(!ind[i]){
		ans++; if(sum[i]==1) s1=true;
	}
	if(ans>1&&s1) ans--;
	printf("%.6lf\n",1.-(double)ans/n);
}
