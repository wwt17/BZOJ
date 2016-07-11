#include <cstdio>
#include <queue>
using namespace std;
int N,M,P,a,b,index;
struct node;
struct edge{
	node *ed; edge *next;
} E[1000000],*newE=E;
struct node{
	edge *son;
	int dfn,low;
	bool instack,done;
	node *belong;
	int num,ans,sum,goin;
	node():sum(1){}
	void tarjan();
	inline void renew(node* v);
} V[100001],*i,*stack[100001],**top=stack;
void node::tarjan(){
	low=dfn=++index; *top++=this; instack=true;
	edge *e,**pre;
	for(e=son;e;e=e->next)
		if(!e->ed->dfn){
			e->ed->tarjan();
			if(e->ed->low<low) low=e->ed->low;
		}
		else
			if(e->ed->instack&&e->ed->dfn<low)
				low=e->ed->dfn;
	if(low==dfn){
		do{
			top--;
			(*top)->belong=this;
			num++;
			if(*top!=this&&(*top)->son){
				for(e=(*top)->son;e->next;e=e->next);
				e->next=son;
				son=(*top)->son;
			}
			(*top)->instack=false;
		} while(*top!=this);
		for(pre=&son,e=son;e;e=e->next)
			if(e->ed->belong==this)
				*pre=e->next;
			else
				pre=&e->next;
	}
}
queue<node*> Q;
vector<node*> S;
inline void node::renew(node* v){
	if(v->done) return;
	v->done=true;
	if(ans>v->ans) return;
	if(ans<v->ans){ ans=v->ans; sum=v->sum; return; }
	sum=(sum+v->sum)%P;
}
int main(){
	scanf("%u%u%u",&N,&M,&P);
	while(M--){
		scanf("%u%u",&a,&b);
		*newE=(edge){V+b,V[a].son},V[a].son=newE++;
	}
	for(i=V+1;i<=V+N;i++) if(!i->dfn)
		i->tarjan();
	for(i=V+1;i<=V+N;i++) if(i->belong==i)
		for(edge *e=i->son;e;e=e->next)
			(e->ed=e->ed->belong)->goin++;
	for(i=V+1;i<=V+N;i++) if(i->belong==i&&!i->goin)
		Q.push(i);
	while(!Q.empty()){
		i=Q.front(); Q.pop();
		S.push_back(i);
		for(edge *e=i->son;e;e=e->next)
			if(!--e->ed->belong->goin)
				Q.push(e->ed->belong);
	}
	for(vector<node*>::reverse_iterator i=S.rbegin();i!=S.rend();i++){
		for(edge* e=(*i)->son;e;e=e->next)
			(*i)->renew(e->ed);
		for(edge* e=(*i)->son;e;e=e->next)
			e->ed->done=false;
		(*i)->ans=((*i)->ans+(*i)->num)%P;
		V->renew(*i);
		(*i)->done=false;
	}
	printf("%u\n%u\n",V->ans,V->sum);
}
