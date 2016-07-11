#include <cstdio>
#include <algorithm>
#include <map>
using namespace std;

typedef double real;

const int N=10,M=50,STS=120000;

int n,m,ex[M],ey[M];
int lg[1<<N];
real fac[M];
int cnt[1<<N][1<<N];

typedef long long state;

int sts;
state st[STS];
real f[M][STS];
struct edge{
	edge *next;
	int ed;
	real w;
} E[STS*M],*newE=E;
edge *son[STS];
int del[STS];

map<state,int> id;

void dfs(int i=0,state s=0){
	if(i==n){
		st[id[s]=sts++]=s;
		return;
	}
	for(int j=0;j<i;j++) if((s>>4*j&15)==j){
		dfs(i+1,s|(state)j<<4*i);
	}
	dfs(i+1,s|(state)i<<4*i);
}

int main(){
	scanf("%d%d",&n,&m);
	for(int i=1;i<=m;i++){
		scanf("%d%d",&ex[i],&ey[i]);
		ex[i]--;
		ey[i]--;
	}
	for(int i=0;i<=m;i++) fac[i]=i?fac[i-1]*i:1;
	for(int i=0;i<n;i++) lg[1<<i]=i;
	for(int s=0;s<1<<n;s++)
		for(int t=0;t<1<<n;t++) if(!(s&t)){
			for(int e=1;e<=m;e++) if(s>>ex[e]&1&&t>>ey[e]&1||s>>ey[e]&1&&t>>ex[e]&1)
				cnt[s][t]++;
		}
	dfs();
	for(int r=1;r<sts;r++){
		state s=st[r];
		static int flag[N];
		for(int j=0;j<n;j++){
			flag[j]=0;
			flag[s>>4*j&15]|=1<<j;
		}
		del[r]=0;
		for(int x=0;x<n;x++) if(flag[x])
			for(int y=x+1;y<n;y++) if(flag[y]) if(cnt[flag[x]][flag[y]]){
				state t=s;
				for(int tmp=flag[y];tmp;tmp-=tmp&-tmp){
					int k=lg[tmp&-tmp];
					t+=(x-(t>>4*k&15))<<4*k;
				}
				del[r]+=cnt[flag[x]][flag[y]];
				*newE=(edge){son[r],id[t],cnt[flag[x]][flag[y]]},son[r]=newE++;
			}
	}
	state init=0;
	for(int j=0;j<n;j++) init+=(state)j<<4*j;
	f[0][id[init]]=1;
	for(int i=0;i<m;i++){
		for(int r=1;r<sts;r++) if(f[i][r]){
			int left=m-i-del[r];
			if(left<0) continue;
			f[i+1][r]+=f[i][r]*left;
			for(edge *e=son[r];e;e=e->next){
				f[i+1][e->ed]+=f[i][r]*e->w;
			}
		}
	}
	real ans=0;
	for(int i=0;i<=m;i++) ans+=f[i][0]*i*fac[m-i];
	for(int i=1;i<=m+1;i++) ans/=i;
	printf("%.6lf\n",ans);
}
