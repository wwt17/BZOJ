#include <cstdio>
#include <algorithm>
using namespace std;
typedef long long ll;

const int N=55,mo=19921228,phi=9951552,p[2]={2,1873};
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

int q[2],now;
int C[N*N];

ll power(ll a,ll b){
	a%=mo;
	if((b%=phi)<0) b+=phi;
	ll ans=1;
	for(;b;b>>=1,a=a*a%mo)
		if(b&1) ans=ans*a%mo;
	return ans;
}

void mul(int x,int y){
	for(int i=0;i<2;i++) while(x%p[i]==0) x/=p[i],q[i]+=y;
	now=now*power(x,y)%mo;
}
int calc(){
	ll ans=now;
	for(int i=0;i<2;i++) ans=ans*power(p[i],q[i])%mo;
	return ans;
}

int c[N][N];

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
	int nn=n-res%(n+1),mm=n*2-res/(n+1)-nn;
	printf("%d %d\n",nn,mm);
	now=C[k]=1;
	for(int i=k+1;i<=nn*mm;i++){
		mul(i,1);
		mul(i-k,-1);
		C[i]=calc();
	}
	for(int i=0;i<=n;i++)
		for(int j=0;j<=i;j++)
			c[i][j]=(!j?1:c[i-1][j-1]+c[i-1][j])%mo;
	ll ans=0;
	for(int i=0;i<=nn;i++) for(int j=0;j<=mm;j++)
		ans=(ans+((i^nn^j^mm)&1?-1LL:1LL)*C[i*j]*c[nn][i]%mo*c[mm][j]%mo)%mo;
	printf("%d\n",int((ans+mo)%mo));
}
