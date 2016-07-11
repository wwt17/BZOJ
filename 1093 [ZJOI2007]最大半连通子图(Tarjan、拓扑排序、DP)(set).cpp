#include <cstdio>
#include <queue>
#include <set>
using namespace std;
int N,M,P,a,b,index;
struct node;
struct edge{
	node *ed; edge *next;
} E[1000000],*newE=E;
typedef set<node*>::iterator sit;
struct node{
	edge *son;
	int dfn,low;
	bool instack;
	node *belong;
	int num,ans,sum,goin;
	set<node*> E;
	node():sum(1){}
	void tarjan();
	inline void renew(node* v);
} V[100001],*i,*stack[100001],**top=stack;
void node::tarjan(){
	low=dfn=++index; *top++=this; instack=true;
	edge *e;
	for(e=son;e;e=e->next)
		if(!e->ed->dfn){
			e->ed->tarjan();
			if(e->ed->low<low) low=e->ed->low;
		}
		else
			if(e->ed->instack&&e->ed->dfn<low)
				low=e->ed->dfn;
	if(low==dfn){
		node** tmp=top;
		do{
			top--;
			(*top)->belong=this;
			num++;
			(*top)->instack=false;
		} while(*top!=this);
		do{
			tmp--;
			for(e=(*tmp)->son;e;e=e->next) if(e->ed->belong!=this)
				E.insert(e->ed->belong);
		} while(*tmp!=this);
	}
}
queue<node*> Q;
vector<node*> S;
inline void node::renew(node* v){
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
		for(sit t=i->E.begin();t!=i->E.end();t++)
			(*t)->goin++;
	for(i=V+1;i<=V+N;i++) if(i->belong==i&&!i->goin)
		Q.push(i);
	while(!Q.empty()){
		i=Q.front(); Q.pop();
		S.push_back(i);
		for(sit t=i->E.begin();t!=i->E.end();t++)
			if(!--(*t)->belong->goin)
				Q.push((*t)->belong);
	}
	for(vector<node*>::reverse_iterator s=S.rbegin();s!=S.rend();s++){
		for(sit t=(*s)->E.begin();t!=(*s)->E.end();t++)
			(*s)->renew(*t);
		(*s)->ans=((*s)->ans+(*s)->num)%P;
		V->renew(*s);
	}
	printf("%u\n%u\n",V->ans,V->sum);
}
