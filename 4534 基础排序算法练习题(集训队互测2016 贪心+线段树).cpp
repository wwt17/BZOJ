#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef double db;
typedef pair<int,int> pii;
#define eprintf(...) fprintf(stderr,__VA_ARGS__)

const int N=1505,M=1000005;

int n,m,q;

pii seq[M];

int sum[N],a[N],loca[N],b[N],locb[N];

set<int> s;

struct seg{
	int d,mi;
	void add(int D){
		d+=D;
		mi+=D;
	}
} t[N*4];

void down(int cur){
	t[cur<<1].add(t[cur].d);
	t[cur<<1|1].add(t[cur].d);
	t[cur].d=0;
}

void update(int cur){
	t[cur].mi=min(t[cur<<1].mi,t[cur<<1|1].mi);
}

void add(int cur,int beg,int end,int L,int R,int D){
	if(end<=L||beg>=R) return;
	if(beg>=L&&end<=R){
		t[cur].add(D);
		return;
	}
	down(cur);
	int mid=(beg+end)>>1;
	add(cur<<1,beg,mid,L,R,D);
	add(cur<<1|1,mid,end,L,R,D);
	update(cur);
}

int query(int cur,int beg,int end,int L,int R){
	if(end<=L||beg>=R) return N;
	if(beg>=L&&end<=R)
		return t[cur].mi;
	down(cur);
	int mid=(beg+end)>>1;
	return min(query(cur<<1,beg,mid,L,R),query(cur<<1|1,mid,end,L,R));
}

int main(){
	scanf("%d%d%d",&n,&m,&q);
	for(int i=1;i<=m;i++) scanf("%d%d",&seq[i].first,&seq[i].second);
	for(int i=1;i<=n;i++) b[i]=i;
	for(int i=2;i<=n;i++) s.insert(i);
	for(int i=m;i>=1;i--){
		while(true){
			set<int>::iterator loc=s.upper_bound(seq[i].first);
			if(loc==s.end()||*loc>seq[i].second) break;
			int x=*loc;
			swap(b[x-1],b[x]);
			s.erase(x);
			if(x-1>1&&b[x-2]<b[x-1]) s.insert(x-1);
			if(x<n&&b[x]<b[x+1]) s.insert(x+1);
		}
	}
	for(int i=1;i<=n;i++) locb[b[i]]=i;
	while(q--){
		for(int i=0;i<N;i++) sum[i]=0;
		for(int i=1;i<=n;i++){
			scanf("%d",&a[i]);
			sum[a[i]]++;
		}
		for(int i=1;i<N;i++) sum[i]+=sum[i-1];
		for(int i=n;i>=1;i--)
			a[i]=sum[a[i]]--;
		for(int i=1;i<=n;i++) loca[a[i]]=i;
		for(int i=1;i<=n*4;i++) t[i]=(seg){0,0};
		bool ok=true;
		for(int i=n;i>=1;i--){
			if(loca[i]<locb[i]){
				add(1,0,n,loca[i]-1,locb[i]-1,-1);
				if(query(1,0,n,loca[i]-1,locb[i]-1)<0){
					ok=false;
					break;
				}
			}
			else{
				add(1,0,n,locb[i]-1,loca[i]-1,+1);
			}
		}
		puts(ok?"AC":"WA");
	}
}
