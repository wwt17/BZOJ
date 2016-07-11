#include <cstdio>
#include <cstdlib>
const int N=100001,M=500001;
int getint(){
	char c;
	while((c=getchar())<'0'||c>'9'); int a=c-'0';
	while((c=getchar())>='0'&&c<='9') a=a*10+(c-'0');
	return a;
}
int n,m;
struct node;
struct edge{
	node *ed;
	edge *next;
} E[M<<1],*newE=E+2;
unsigned w[M];
struct node{
	edge *son;
	bool vis;
	void dfs(edge *pre){
		vis=true;
		for(edge *e=son;e;e=e->next) if(!e->ed->vis)
			e->ed->dfs(e);
		unsigned t=0;
		for(edge *e=son;e;e=e->next) t^=w[(e-E)>>1];
		w[(pre-E)>>1]^=t;
	}	
} V[N];
unsigned base[32];
int main(){
	freopen(".in","r",stdin);
	freopen(".out","w",stdout);
	n=getint(); m=getint();
	for(int i=1;i<=m;i++){
		node *u=V+getint(),*v=V+getint();
		*newE=(edge){v,u->son},u->son=newE++;
		*newE=(edge){u,v->son},v->son=newE++;
		w[i]=rand();
	}
	V[1].dfs(E);
	int q=getint(),cnt=0;
	while(q--){
		int k=getint();
		bool connected=true;
		for(int i=0;i<32;i++) base[i]=0;
		while(k--){
			int x=w[getint()^cnt];
			for(int i=31;i>=0;i--) if(x>>i&1)
				if(base[i]) x^=base[i]; else{
					base[i]=x;
					break;
				}
			if(!x) connected=false;
		}
		puts(connected?"Connected":"Disconnected");
		cnt+=connected;
	}
}
