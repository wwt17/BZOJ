#include <cstdio>
const double eps=1e-9;
int maxcnt=20;
const int inf=10000000;
int n,m;
double minw=inf,maxw=-inf;
struct node;
struct edge{
	node *ed; edge *next; double w,W;
} E[10000];
struct node{
	edge *son; double dist; node* next; bool inq; int cnt;
} V[3001];
int main(){
	scanf("%u%u",&n,&m);
	if(n<maxcnt) maxcnt=n;
	for(edge* e=E;e<E+m;e++){
		static int i,j;
		scanf("%u%u%lf",&i,&j,&e->w);
		if(e->w<minw) minw=e->w;
		if(e->w>maxw) maxw=e->w;
		e->ed=V+j;
		e->next=V[i].son;
		V[i].son=e;
	}
	double l=minw,r=maxw,mid;
	while(r-l>eps){
		mid=(l+r)/2;
		bool ok=true;
		for(edge* e=E;e<E+m;e++)
			e->W=e->w-mid;
		for(node* v=V+1;v<=V+n;v++)
			v->dist=(double)n*(maxw-mid);
		V[1].dist=0;
		for(node* v=V+1;v<V+n;v++) v->next=v+1,v->inq=true,v->cnt=1;
		V[n].inq=true;
		V[n].next=NULL;
		for(node *head=V+1,*tail=V+n;head;head->inq=false,head=head->next)
			for(edge* e=head->son;e;e=e->next)
				if(head->dist+e->W<e->ed->dist){
					e->ed->dist=head->dist+e->W;
					if(!e->ed->inq){
						if(++e->ed->cnt==maxcnt){
							ok=false;
							goto out;
						}
						tail=tail->next=e->ed;
						tail->inq=true;
						tail->next=NULL;
					}
				}
		out: (ok?l:r)=mid;
	}
	printf("%.8lf\n",r);
}
