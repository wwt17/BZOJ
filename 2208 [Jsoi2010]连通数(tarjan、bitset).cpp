#include <cstdio>
#include <queue>
#include <bitset>
using namespace std;
int N,Ans;
struct node{
	bitset<2000> c; int dfn,low,gout,cnt; bool instack; node *belong;
	void tarjan();
} V[2000];
void node::tarjan(){
	static int index=0;
	static node *stack[2000],**top=stack;
	*top++=this; instack=true;
	low=dfn=++index;
	int j;
	for(j=0;j<N;j++) if(c[j])
		if(!V[j].dfn){
			V[j].tarjan();
			if(V[j].low<low) low=V[j].low;
		}
		else if(V[j].instack&&V[j].dfn<low) low=V[j].dfn;
	if(low==dfn){
		while(true){
			top--;
			(*top)->belong=this;
			(*top)->instack=false;
			cnt++;
			if(*top==this) break;
			for(j=0;j<N;j++) if((*top)->c[j])
				c[j]=true;
		}
		c[this-V]=true;
	}
}
int main(){
	scanf("%u",&N);
	for(int i=0;i<N;i++){
		scanf("\n");
		for(int j=0;j<N;j++)
			V[i].c[j]=getchar()&1;
	}
	for(int i=0;i<N;i++) if(!V[i].dfn)
		V[i].tarjan();
	queue<node*> q;
	for(int i=0;i<N;i++) if(V[i].belong==V+i){
		for(int j=0;j<N;j++) if(V[i].c[j]) V[i].c[j]=false,V[i].c[V[j].belong-V]=true;
		for(int j=0;j<N;j++) if(V[i].c[j])
			V[i].gout++;
		if(!--V[i].gout)
			q.push(V+i);
	}
	while(!q.empty()){
		node *u=q.front(); q.pop();
		int sum=0;
		for(int j=0;j<N;j++) if(u->c[j]) sum+=V[j].cnt;
		Ans+=sum*u->cnt;
		for(int i=0;i<N;i++) if(V[i].belong==V+i&&V[i].c[u-V]&&i!=u-V){
			V[i].c|=u->c;
			if(!--V[i].gout)
				q.push(V+i);
		}
	}
	printf("%u\n",Ans);
}
