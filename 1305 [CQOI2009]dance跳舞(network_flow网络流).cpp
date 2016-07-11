#include <cstdio>
#include <algorithm>
using namespace std;
typedef int capType;
int n,m,k,i,j;
struct node;
struct edge{
	node *ed; edge *next; capType cap;
} E[5400],*newE=E,*Ek,*E1,*e;
struct node{
	edge *son; node *next; unsigned depth;
	node():son(NULL){}
} *S=new node,*T=new node,boy[50][2],girl[50][2];
void addedge(node *u,node *v){
	*newE=(edge){v,u->son,0}; u->son=newE++;
	*newE=(edge){u,v->son,0}; v->son=newE++;
}
bool layer(){
	node *u,*head,*tail;
	//clear
	for(int i=0;i<n;i++)
		boy[i][0].depth=boy[i][1].depth=
		girl[i][0].depth=girl[i][1].depth=0;
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
	scanf("%u%u",&n,&k);
	for(i=0;i<n;i++){
		addedge(S,boy[i]);
		addedge(girl[i]+1,T);
	}
	for(Ek=newE,i=0;i<n;i++){
		addedge(boy[i],boy[i]+1);
		addedge(girl[i],girl[i]+1);
	}
	for(E1=newE,i=0;i<n;i++){
		scanf("\n");
		for(j=0;j<n;j++)
			if(getchar()=='Y')
				addedge(boy[i],girl[j]+1);
			else
				addedge(boy[i]+1,girl[j]);
	}
	int l=0,r=n,mid;
	while(l<=r){
		mid=(l+r)>>1;
		e=E;
		while(e<Ek) e++->cap=mid,e++->cap=0;
		while(e<E1) e++->cap=k,e++->cap=0;
		while(e<newE) e++->cap=1,e++->cap=0;
		if(maxflow(n*mid)==n*mid)
			m=mid,l=mid+1;
		else
			r=mid-1;
	}
	printf("%u\n",m);
}
