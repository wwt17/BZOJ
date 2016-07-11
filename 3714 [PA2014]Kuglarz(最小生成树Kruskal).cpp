#include <cstdio>
#include <algorithm>
const int N=2005;
inline int getint(){
	char c;
	while((c=getchar())<'0'||c>'9'); int a=c-'0';
	while((c=getchar())>='0'&&c<='9') a=a*10+c-'0';
	return a;
}
int n,belong[N];
inline int get(int x){
	if(x==belong[x]) return x;
	return belong[x]=get(belong[x]);
}
struct edge{
	int a,b,c;
	bool operator < (const edge &A) const{
		return c<A.c;
	}
} E[N*N/2],*newE=E;
long long ans;
int main(){
	n=getint();
	for(int i=0;i<n;i++)
		for(int j=i+1;j<=n;j++)
			*newE++=(edge){i,j,getint()};
	for(int i=0;i<=n;i++) belong[i]=i;
	std::sort(E,newE);
	int cnt=n+1;
	for(edge *e=E;e<newE;e++){
		int x=get(e->a),y=get(e->b);
		if(x==y) continue;
		belong[y]=x;
		ans+=e->c;
		if(--cnt==1) break;
	}
	printf("%lld\n",ans);
}
