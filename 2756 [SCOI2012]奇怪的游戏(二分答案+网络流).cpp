#include <cstdio>
#include <algorithm>
#include <queue>
using namespace std;
const int N=40,M=N*N*4;
typedef long long data;
const data inf=(data)1e16;
int n,m,newE,te;
struct node;
struct edge{
	int next; node *ed; data cap;
} E[M*2+2];
struct node{
	int depth,son;
	node():son(0){}
} S[2],*T=S+1,V[N][N];//define nodes
inline void addedge(node *u,node *v,int c1=inf,int c2=0){
	E[newE].next=u->son,E[newE].ed=v,E[newE].cap=c1,u->son=newE++;
	E[newE].next=v->son,E[newE].ed=u,E[newE].cap=c2,v->son=newE++;
}
bool layer(){
	//clear
	for(int i=0;i<n;i++)
		for(int j=0;j<m;j++)
			V[i][j].depth=0;
	T->depth=0;
	queue<node*> q; node *u,*v;
	for(q.push(S),S->depth=1;!q.empty();q.pop())
		for(int e=(u=q.front())->son;e;e=E[e].next)
			if(E[e].cap&&!(v=E[e].ed)->depth){
				q.push(v),v->depth=u->depth+1;
				if(v==T) return true;
			}
	return false;
}
data flow(node* x,data F){
	if(x==T) return F;
	data left=F,Flow; node* y;
	for(int e=x->son;e&&left;e=E[e].next)
		if(E[e].cap&&x->depth+1==(y=E[e].ed)->depth&&(Flow=flow(y,min(left,E[e].cap))))
			E[e].cap-=Flow,E[e^1].cap+=Flow,left-=Flow;
	if(!(F-=left)) x->depth=0;
	return F;
}
int a[N][N];
long long sum[2];

inline bool check(long long h){
	int nowE=2;
	for(;nowE<te;){
		E[nowE++].cap=inf;
		E[nowE++].cap=0;
	}
	for(int i=0;i<n;i++)
		for(int j=0;j<m;j++){
			E[nowE++].cap=h-a[i][j];
			E[nowE++].cap=0;
		}
	long long ans=((long long)h*n*m-(sum[0]+sum[1]))/2,f;
	while(layer()){
		while(f=flow(S,inf))
			ans-=f;
	}
	return !ans;
}

int main(){
	freopen("2756.in","r",stdin);
	freopen("2756.out","w",stdout);
	int t; scanf("%d",&t);
	while(t--){
		scanf("%d%d",&n,&m);
		long long l=0,r=(long long)1e10;
		sum[0]=sum[1]=0;
		S->son=T->son=0;
		for(int i=0;i<n;i++)
			for(int j=0;j<m;j++){
				scanf("%d",&a[i][j]);
				sum[(i^j)&1]+=a[i][j];
				l=max(l,(long long)a[i][j]);
				V[i][j].son=0;
			}
		newE=2;
		for(int i=0;i<n;i++)
			for(int j=0;j<m;j++)
				if((i^j)&1){
					if(j+1<m) addedge(&V[i][j+1],&V[i][j]);
					if(i+1<n) addedge(&V[i+1][j],&V[i][j]);
				}
				else{
					if(j+1<m) addedge(&V[i][j],&V[i][j+1]);
					if(i+1<n) addedge(&V[i][j],&V[i+1][j]);
				}
		te=newE;
		for(int i=0;i<n;i++)
			for(int j=0;j<m;j++)
				if((i^j)&1)
					addedge(&V[i][j],T);
				else
					addedge(S,&V[i][j]);
		l--;
		if((n*m)&1){
			long long h=sum[0]>sum[1]?sum[0]-sum[1]:sum[1]-sum[0];
			if(h<=l||!check(h))
				puts("-1");
			else
				printf("%I64d\n",(long long)h*n*m-(sum[0]+sum[1])>>1);
		}
		else{
			if(sum[0]!=sum[1])
				puts("-1");
			else{
				while(r-l>1){
					long long h=l+r>>1;
					if(check(h))
						r=h;
					else
						l=h;
				}
				printf("%I64d\n",(long long)r*n*m-(sum[0]+sum[1])>>1);
			}
		}
	}
	scanf("\n");
}
