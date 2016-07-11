#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;
const int N=100005,T=2<<18,M=27,inf=0x7fffffff;

int n,Base,sum[N]; long long num[N];

void DA(int n,int m,char *s,int *SA,int *&Rank,int *sa,int *sum){
	int i,p=0;
	s[n]=0;
	memset(sum,0,sizeof(*sum)*m);
	for(i=0;i<=n;i++) sum[Rank[i]=s[i]]++;
	for(i=1;i<m;i++) sum[i]+=sum[i-1];
	for(i=n;i>=0;i--) SA[--sum[Rank[i]]]=i;
	for(int len=1;len<=n&&p<=n;len<<=1,m=p){
		p=0;
		for(i=n-len;i<=n;i++) sa[p++]=i;
		for(i=1;i<=n;i++) if(SA[i]>=len) sa[p++]=SA[i]-len;
		memset(sum,0,sizeof(*sum)*m);
		for(i=0;i<=n;i++) sum[Rank[sa[i]]]++;
		for(i=1;i<m;i++) sum[i]+=sum[i-1];
		for(i=n;i>=0;i--) SA[--sum[Rank[sa[i]]]]=sa[i];
		int *rank=sa;
		p=1;
		rank[SA[0]]=0;
		for(i=1;i<=n;i++) rank[SA[i]]=
			Rank[SA[i-1]]==Rank[SA[i]]&&Rank[SA[i-1]+len]==Rank[SA[i]+len]
			?p-1:p++;
		sa=Rank;
		Rank=rank;
	}
}
void getHeight(int n,char *s,int *Height,int *SA,int *Rank){
	for(int i=0,h=0;i<n;Height[Rank[i++]]=h)
		for(h?h--:0;s[SA[Rank[i]-1]+h]==s[i+h];h++);
}

struct str{
	char s[N];
	int SA[N],mem[2][N],*Rank,t[T];
	void work(){
		DA(n,M,s,SA,Rank=mem[0],mem[1],sum);
		getHeight(n,s,t+Base,SA,Rank);
		for(int l=Base>>1,r=(Base+n+1)>>1;l^r^1;l>>=1,r>>=1)
			for(int i=l+1;i<r;i++) t[i]=min(t[i<<1],t[i<<1|1]);
	}
	int query(int l,int r){
		int ans=inf;
		for(l+=Base,r+=Base+1;l^r^1;l>>=1,r>>=1){
			if(!(l&1)&&ans>t[l^1]) ans=t[l^1];
			if( (r&1)&&ans>t[r^1]) ans=t[r^1];
		}
		return ans;
	}
} S[2];

int main(){
	int q; scanf("%d%d%s",&n,&q,S[0].s);
	for(Base=1;Base<n;Base<<=1);
	for(int i=0;i<n;i++) S[1].s[n-1-i]=S[0].s[i]-='a'-1;
	S[0].work();
	S[1].work();
	int *Height=S[0].t+Base,l,r,lh,rh; long long x,y,a,b;
	for(int i=1;i<=n;i++) num[i]=num[i-1]+n-S[0].SA[i]-Height[i];
	while(q--){
		scanf("%lld%lld",&x,&y);
		if(x>num[n]||y>num[n]){ puts("-1"); continue; }
		l=lower_bound(num,num+n+1,x)-num; lh=x-num[l-1]+Height[l];
		r=lower_bound(num,num+n+1,y)-num; rh=y-num[r-1]+Height[r];
		a=min(min(lh,rh),S[0].query(l,r));
		l=S[1].Rank[n-S[0].SA[l]-lh];
		r=S[1].Rank[n-S[0].SA[r]-rh];
		if(l>r) swap(l,r);
		b=min(min(lh,rh),S[1].query(l,r));
		printf("%lld\n",a*a+b*b);
	}
}
