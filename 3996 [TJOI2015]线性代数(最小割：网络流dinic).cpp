#include <cstdio>
#include <algorithm>
using namespace std;
const int N=505;
int getint(){
	char c;
	while((c=getchar())<'0'||c>'9'); int a=c-'0';
	while((c=getchar())>='0'&&c<='9') a=a*10+(c-'0');
	return a;
}
const int sizeV=2+N+N*N,sizeE=N+N*N/2*3;
typedef int capType;
const capType inf=(capType)1e9+7;
#define nonzero(x) bool(x)
struct node;
struct edge{
	node *ed;
	edge *next;
	capType cap;
} E[sizeE<<1],*newE=E;
int labtim;
struct node{
	edge *son;
	int lab,labtim;
} S[2],*T=S+1;
bool layer(){
	static node *q[sizeV];
	int head=0,tail=0;
	labtim++;
	q[tail++]=S;
	S->labtim=labtim;
	S->lab=0;
	while(head!=tail){
		node *u=q[head++];
		for(edge *e=u->son;e;e=e->next) if(nonzero(e->cap)){
			node *v=e->ed;
			if(v->labtim==labtim) continue;
			v->labtim=labtim;
			v->lab=u->lab+1;
			if(v==T)
				return true;
			q[tail++]=v;
		}
	}
	return false;
}
capType flow(node *u,const capType F){
	if(u==T) return F;
	capType left=F;
	for(edge *e=u->son;e&&nonzero(left);e=e->next) if(nonzero(e->cap)){
		node *v=e->ed;
		if(v->labtim!=labtim||v->lab!=u->lab+1) continue;
		capType f=flow(v,min(left,e->cap));
		e->cap-=f;
		E[e-E^1].cap+=f;
		left-=f;
	}
	if(!nonzero(F-left)) u->labtim=0;
	return F-left;
}
capType maxflow(){
	capType ans=0,f;
	while(layer())
		while(nonzero(f=flow(S,inf)))
			ans+=f;
	return ans;
}
void addedge(node *u,node *v,const capType cap0,const capType cap1=0){
	*newE=(edge){v,u->son,cap0},u->son=newE++;
	*newE=(edge){u,v->son,cap1},v->son=newE++;
}

int n;
node a[N],b[N][N];
int B[N][N];

int main(){
	n=getint();
	int ans=0;
	for(int i=1;i<=n;i++) for(int j=1;j<=n;j++) ans+=B[i][j]=getint();
	for(int i=1;i<=n;i++) addedge(S,&a[i],getint());
	for(int i=1;i<=n;i++){
		addedge(&a[i],&b[i][i],inf);
		addedge(&b[i][i],T,B[i][i]);
		for(int j=i+1;j<=n;j++){
			addedge(&a[i],&b[i][j],inf);
			addedge(&a[j],&b[i][j],inf);
			addedge(&b[i][j],T,B[i][j]+B[j][i]);
		}
	}
	ans-=maxflow();
	printf("%d\n",ans);
}
