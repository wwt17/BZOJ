#include <cstdio>
int n,k,m,tot,v[10001];
void correct(int i){
	if(v[i]==i) return;
	correct(v[i]);
	v[i]=v[v[i]];
}
struct edge{
	int a,b,c1,c2;
	inline void read(){
		scanf("%d%d%d%d",&a,&b,&c1,&c2);
	}
	inline void link(){
		correct(a);
		correct(b);
		if(v[a]!=v[b]){
			v[v[a]]=v[b];
			--tot;
		}
	}
} e[20001];
int main(){
	scanf("%d%d%d",&n,&k,&m); m--;
	for(int i=0;i<m;i++) e[i].read();
	int l=-1,r=30000,mid;
	while(l+1<r){
		mid=(l+r)/2;
		int cnt=0;
		for(int i=1;i<=n;i++) v[i]=i; tot=n-1;
		for(int i=0;i<m&&tot;i++) if(e[i].c1<=mid) e[i].link();
		if(n-1-tot<k){ l=mid; continue; }
		for(int i=0;i<m&&tot;i++) if(e[i].c2<=mid) e[i].link();
		if(tot)
			l=mid;
		else
			r=mid;
	}
	printf("%d\n",r);
}
