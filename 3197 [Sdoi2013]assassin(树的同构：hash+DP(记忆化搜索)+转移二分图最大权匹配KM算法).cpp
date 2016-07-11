#include <cstdio>
#include <algorithm>
#include <vector>
using namespace std;
typedef long long ll;

const int N=715,M=N*2,mo1=100000007,mo2=999999991,inf=mo1;

ll base1[N*2],base2[N*2];

void initbase(ll base[],int mo,int n){
	base[0]=1;
	base[1]=3;
	for(int i=2;i<=n;i++) base[i]=base[i-1]*base[1]%mo;
}

struct state{
	int len,c1,c2;
	void operator += (const int b){
		c1=(c1*base1[1]+b)%mo1;
		c2=(c2*base2[1]+b)%mo2;
		len++;
	}
	void operator += (const state &b){
		c1=(c1*base1[b.len]+b.c1)%mo1;
		c2=(c2*base2[b.len]+b.c2)%mo2;
		len+=b.len;
	}
	bool operator < (const state &b) const{
		return c1<b.c1||c1==b.c1&&c2<b.c2;
	}
};

int n,m,root,size[N],flag[N][2];
vector<int> g[N];
state st[N];

bool cmp(int u,int v){
	return st[u]<st[v];
}

void addedge(int u,int v){
	g[u].push_back(v);
}
void deledge(int u,int v){
	for(int i=0;i<g[u].size();i++) if(g[u][i]==v){
		g[u].erase(g[u].begin()+i);
		break;
	}
}

void getsize(int u,int fa){
	size[u]=1;
	for(int i=0;i<g[u].size();i++){
		int v=g[u][i];
		if(v==fa) continue;
		getsize(v,u);
		size[u]+=size[v];
	}
}
int getroot(int u){
	for(;;){
		int v=0;
		for(int i=0;i<g[u].size();i++) if(size[g[u][i]]*2>size[u]){
			v=g[u][i];
			break;
		}
		if(!v) break;
		int tmp=size[u];
		size[u]-=size[v];
		size[v]=tmp;
		u=v;
	}
	return u;
}

int f[N][N];

int len,w[N][N],labx[N],laby[N],mat[N];
bool visx[N],visy[N];

bool extend(int u){
	if(!u) return true;
	visx[u]=true;
	for(int v=1;v<=len;v++) if(!visy[v]&&labx[u]+laby[v]==w[u][v]){
		visy[v]=true;
		if(extend(mat[v])){
			mat[v]=u;
			return true;
		}
	}
	return false;
}

void change(){
	int delta=inf;
	for(int i=1;i<=len;i++) if(visx[i])
		for(int j=1;j<=len;j++) if(!visy[j])
			delta=min(delta,labx[i]+laby[j]-w[i][j]);
	for(int i=1;i<=len;i++){
		if(visx[i]) labx[i]-=delta;
		if(visy[i]) laby[i]+=delta;
	}
}

int KM(){
	for(int i=1;i<=len;i++){
		labx[i]=-inf;
		for(int j=1;j<=len;j++) labx[i]=max(labx[i],w[i][j]);
		laby[i]=0;
		mat[i]=0;
	}
	for(int i=1;i<=len;i++)
		for(;;){
			for(int j=1;j<=len;j++) visx[j]=visy[j]=false;
			if(extend(i)) break;
			change();
		}
	int ans=0;
	for(int i=1;i<=len;i++) ans+=labx[i]+laby[i];
	return ans;
}

void dfs(int u,int fa){
	deledge(u,fa);
	st[u]+=1;
	for(int i=0;i<g[u].size();i++)
		dfs(g[u][i],u);
	sort(g[u].begin(),g[u].end(),cmp);
	for(int i=0;i<g[u].size();i++)
		st[u]+=st[g[u][i]];
	st[u]+=2;
}

int calc(int u,int v){
	if(f[u][v]!=-1) return f[u][v];
	f[u][v]=flag[u][0]^flag[v][1];
	for(int l=0,r=l;l<g[u].size();l=r){
		for(;r<g[u].size()&&!cmp(g[u][l],g[u][r]);r++);
		for(int i=l;i<r;i++)
			for(int j=l;j<r;j++)
				calc(g[u][i],g[v][j]);
		len=r-l;
		for(int i=l;i<r;i++)
			for(int j=l;j<r;j++)
				w[i-l+1][j-l+1]=-calc(g[u][i],g[v][j]);
		f[u][v]+=-KM();
	}
	return f[u][v];
}

int main(){
	scanf("%d",&n);
	initbase(base1,mo1,n*2);
	initbase(base2,mo2,n*2);
	for(int i=1;i<=n-1;i++){
		int x,y; scanf("%d%d",&x,&y);
		addedge(x,y);
		addedge(y,x);
	}
	for(int i=1;i<=n;i++) scanf("%d",&flag[i][0]);
	for(int i=1;i<=n;i++) scanf("%d",&flag[i][1]);
	getsize(1,0);
	root=getroot(1);
	for(int i=0;i<g[root].size();i++) if(size[g[root][i]]*2==size[root]){
		int root1=root,root2=g[root][i];
		root=++n;
		deledge(root1,root2);
		deledge(root2,root1);
		addedge(root,root1);
		addedge(root1,root);
		addedge(root,root2);
		addedge(root2,root);
	}
	dfs(root,0);
	for(int i=1;i<=n;i++)
		for(int j=1;j<=n;j++)
			f[i][j]=-1;
	printf("%d\n",calc(root,root));
}
