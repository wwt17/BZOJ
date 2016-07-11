#include <cstdio>
#include <algorithm>
using namespace std;
typedef long long ll;

const int N=55,mo=19921228;
inline void inc(int &a,const ll b){
	a=(a+b)%mo;
}

const int sizeV=2+N*2,sizeE=N*N;
typedef int capType;
const capType inf=(int)1e9+7;
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

int n,k,m;

bool del[N][N];

node a[N],b[N];

int C[N*N][N*N];
int f[N][N];

int main(){
	scanf("%d%d",&n,&k);
	scanf("%d",&m);
	while(m--){
		int x,y; scanf("%d%d",&x,&y);
		del[x][y]=true;
	}
	for(int i=1;i<=n;i++) for(int j=1;j<=n;j++) if(!del[i][j])
		addedge(&a[i],&b[j],inf);
	for(int i=1;i<=n;i++){
		addedge(S,&a[i],(n+1)+1);
		addedge(&b[i],T,(n+1));
	}
	int res=maxflow();
	int nn=n-res%(n+1),mm=n*2-res/(n+1)-nn,ss=max(max(nn,mm),nn*mm);
	printf("%d %d\n",nn,mm);
	for(int i=0;i<=ss;i++)
		for(int j=0;j<=i;j++)
			C[i][j]=(!j?1:C[i-1][j-1]+C[i-1][j])%mo;
	for(int i=0;i<=nn;i++) for(int j=0;j<=mm;j++){
		f[i][j]=C[i*j][k];
		for(int ii=0;ii<=nn;ii++) for(int jj=0;jj<=mm;jj++) if(ii!=i||jj!=j){
			(f[i][j]-=1LL*f[ii][jj]*C[i][ii]%mo*C[j][jj]%mo)%=mo;
		}
	}
	printf("%d\n",(f[nn][mm]+mo)%mo);
}
