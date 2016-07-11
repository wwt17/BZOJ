#include <cstdio>
#include <algorithm>
#include <queue>
using namespace std;

typedef long long ll;

const int N=75,M=N*N*2;

const ll inf=1e15;

int n;

struct vec{
	int x,y;
	vec(ll _x=0,int _y=0):x(_x),y(_y){
	}
	vec rotate(){
		return vec(-y,x);
	}
	int val(){
		return x*y;
	}
};

bool operator == (const vec &a,const vec &b){
	return a.x==b.x&&a.y==b.y;
}

vec operator + (const vec &a,const vec &b){
	return vec(a.x+b.x,a.y+b.y);
}

vec operator - (const vec &a,const vec &b){
	return vec(a.x-b.x,a.y-b.y);
}

int dot(const vec &a,const vec &b){
	return a.x*b.x+a.y*b.y;
}

ll laba[N],labb[N];
int mat[N];
bool visa[N],visb[N];
ll cost[N][N];

bool extend(int u){
	if(!u) return true;
	visa[u]=true;
	for(int v=1;v<=n;v++) if(!visb[v]&&laba[u]+labb[v]==cost[u][v]){
		visb[v]=true;
		if(extend(mat[v])){
			mat[v]=u;
			return true;
		}
	}
	return false;
}

void change(){
	ll delta=inf;
	for(int i=1;i<=n;i++) if(visa[i])
		for(int j=1;j<=n;j++) if(!visb[j])
			delta=min(delta,laba[i]+labb[j]-cost[i][j]);
	for(int i=1;i<=n;i++){
		if(visa[i]) laba[i]-=delta;
		if(visb[i]) labb[i]+=delta;
	}
}

void KM(){
	for(int i=1;i<=n;i++){
		laba[i]=-inf;
		for(int j=1;j<=n;j++)
			laba[i]=max(laba[i],cost[i][j]);
		labb[i]=0;
		mat[i]=0;
	}
	for(int i=1;i<=n;i++)
		for(;;){
			for(int j=1;j<=n;j++) visa[j]=visb[j]=false;
			if(extend(i)) break;
			change();
		}
}

vec w[N][N];

vec calc(vec d){
	for(int i=1;i<=n;i++)
		for(int j=1;j<=n;j++)
			cost[i][j]=-dot(w[i][j],d);
	KM();
	vec ans;
	for(int i=1;i<=n;i++)
		ans=ans+w[mat[i]][i];
	return ans;
}
int work(vec l,vec r){
	vec mid=calc((r-l).rotate());
	if(mid==l||mid==r)
		return l.val();
	return min(work(l,mid),work(mid,r));
}
int Main(){
	scanf("%d",&n);
	for(int i=1;i<=n;i++)
		for(int j=1;j<=n;j++)
			scanf("%d",&w[i][j].x);
	for(int i=1;i<=n;i++)
		for(int j=1;j<=n;j++)
			scanf("%d",&w[i][j].y);
	vec l=calc(vec(1,0)),r=calc(vec(0,1));
	return min(work(l,r),r.val());
}

int main(){
	int T; scanf("%d",&T);
	while(T--)
		printf("%d\n",Main());
}
