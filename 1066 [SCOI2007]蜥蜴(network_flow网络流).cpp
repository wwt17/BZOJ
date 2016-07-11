#include <cstdio>
#include <cstdlib>
#include <algorithm>
using namespace std;
#define INF 0x7FFF
typedef short capType;
int r,c,i,j,ii,jj,d;
struct node;
struct edge{
	node *ed; edge *next; capType cap;
} E[321600],*newE=E;
struct node{
	edge *son; node *next; short depth;
	node():son(NULL){}
} *S=new node,*T=new node,map[20][20][2];
void addedge(node *u,node *v,capType cap){
	*newE=(edge){v,u->son,cap}; u->son=newE++;
	*newE=(edge){u,v->son,0  }; v->son=newE++;
}
bool layer(){
	node *u,*head,*tail;
	//clear
	for(i=0;i<r;i++)
		for(j=0;j<c;j++)
			map[i][j][0].depth=map[i][j][1].depth=0;
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
	scanf("%u%u%u",&r,&c,&d);
	for(i=0;i<r;i++){
		scanf("\n");
		for(j=0;j<c;j++){
			addedge(map[i][j],map[i][j]+1,getchar()-'0');
			for(ii=0;ii<r;ii++)
				for(jj=0;jj<c;jj++)
					if(abs(i-ii)+abs(j-jj)<=d)
						addedge(map[i][j]+1,map[ii][jj],INF);
			if(i<d||r-i<=d||j<d||c-j<=d)
				addedge(map[i][j]+1,T,INF);
		}
	}
	int cnt=0;
	for(i=0;i<r;i++){
		scanf("\n");
		for(j=0;j<c;j++) if(getchar()=='L')
			addedge(S,map[i][j],1),cnt++;
	}
	printf("%u\n",cnt-maxflow(cnt));
}
