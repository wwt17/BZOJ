#include <cstdio>
const int N=250001;
struct node;
struct edge{
	node *ed; edge *next;
} E[N<<1],*newE=E;
struct node{
	edge *son; node *pa;
	int st,en;
	void DFS();
} V[N];
int n,m,a,b,len=0,t[N<<1];
void node::DFS(){
	t[st=++len]=1;
	for(edge *e=son;e;e=e->next) if(e->ed!=pa){
		e->ed->pa=this;
		e->ed->DFS();
	}
	t[en=++len]=-1;
}
inline void modify(int x,const int delta){
	for(;x<=len;x+=x&-x) t[x]+=delta;
}
inline int query(int x){
	int ans=0;
	for(;x;x-=x&-x) ans+=t[x];
	return ans;
}
int main(){
	scanf("%d",&n);
	for(int i=1;i<n;i++){
		scanf("%d%d",&a,&b);
		*newE=(edge){V+b,V[a].son},V[a].son=newE++;
		*newE=(edge){V+a,V[b].son},V[b].son=newE++;
	}
	V[1].DFS();
	for(int i=1;i<=len;i++) if(i+(i&-i)<=len) t[i+(i&-i)]+=t[i];
	scanf("%d",&m); m+=n-1;
	while(m--)
		if(scanf("\n"),getchar()=='A'){
			scanf("%d%d",&a,&b);
			if(V[a].pa==V+b){
				modify(V[a].st,-1);
				modify(V[a].en,1);
			}
			else{
				modify(V[b].st,-1);
				modify(V[b].en,1);
			}
		}
		else{
			scanf("%d",&a);
			printf("%d\n",query(V[a].st)-1);
		}
}
