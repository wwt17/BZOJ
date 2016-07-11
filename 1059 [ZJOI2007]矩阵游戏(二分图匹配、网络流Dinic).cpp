#include <cstdio>
#include <algorithm>
using namespace std;
typedef short capType;
int N;
struct node;
struct edge{
	node *ed; edge *next; capType cap;
} E[80800],*newE=E;
struct node{
	edge *son; node *next; unsigned depth;
	node():son(NULL){}
} *S,*T,r[200],c[200];
void addedge(node *u,node *v,capType cap){
	*newE=(edge){v,u->son,cap}; u->son=newE++;
	*newE=(edge){u,v->son,0  }; v->son=newE++;
}
bool layer(){
	node *u,*head,*tail;
	//clear
	for(u=r;u<r+N;u++) u->depth=0;
	for(u=c;u<c+N;u++) u->depth=0;
	T->depth=0;
	S->depth=1;
	head=tail=S;
	tail->next=NULL;
	for(;head;head=head->next)
		for(edge *e=head->son;e;e=e->next)
			if(e->cap&&!e->ed->depth){
				tail=tail->next=e->ed;
				tail->depth=head->depth+1;
				tail->next=NULL;
				if(tail==T) return true;
			}
	return false;
}
capType flow(node *u,capType F){
	if(u==T) return F;
	capType left=F,Flow; node *v;
	for(edge *e=u->son;e&&left;e=e->next)
		if(e->cap&&(v=e->ed)->depth==u->depth+1
		&&(Flow=flow(v,min(left,e->cap))))
			e->cap-=Flow,E[(e-E)^1].cap+=Flow,left-=Flow;
	if(!(F-=left)) u->depth=0;
	return F;
}
capType maxflow(capType F){
	capType left=F,Flow;
	while(layer())
		while(Flow=flow(S,left))
			left-=Flow;
	return F-left;
}
int main(){
	int Tests,i,j; scanf("%u",&Tests); while(Tests--){
		scanf("%u",&N);
		newE=E;
		S=new node;
		T=new node;
		for(i=0;i<N;i++)
			addedge(S,new(r+i) node,1),
			addedge(new(c+i) node,T,1);
		for(i=0;i<N;i++)
			for(j=0;j<N;j++){
				char ch; while((ch=getchar())<'0');
				if(ch=='1') addedge(r+i,c+j,1);
			}
		puts(maxflow(N)==N?"Yes":"No");
	}
}
