#include <cstdio>
#include <algorithm>
using namespace std;
const int N=1000000,Q=3000,B=1001;
int n,q;
inline int getint(){
	char c;
	while((c=getchar())<'0'||c>'9'); int a=c-'0';
	while((c=getchar())>='0'&&c<='9') a=a*10+c-'0';
	return a;
}
short a[N];
int R,ord[Q<<1],*otop=ord,delta[Q<<1],sum[Q<<1][B];
struct query{
	int l,r,w; bool ism;
	inline void read(){
		begin: switch(getchar()){
			case 'M': ism=true; break;
			case 'A': ism=false; break;
			default: goto begin;
		}
		*otop++=l=getint()-1;
		*otop++=r=getint();
		w=getint();
	}
	void work(){
		int
			st=lower_bound(ord,otop,l)-ord,
			ed=lower_bound(ord,otop,r)-ord;
		if(ism)
			for(int i=st;i<ed;i++) delta[i]+=w;
		else{
			int ans=0;
			for(int i=st;i<ed;i++)
				if(w<=delta[i]) ans+=sum[i][0]; else
				if(w<delta[i]+B) ans+=sum[i][w-delta[i]];
			printf("%d\n",ans);
		}
	}
} s[Q];
int main(){
	n=getint(); q=getint();
	for(int j=0;j<n;j++) a[j]=getint();
	for(int i=0;i<q;i++) s[i].read();
	sort(ord,otop);
	otop=unique(ord,otop);
	R=otop-ord;
	for(int i=0,j=ord[0];i<R-1;i++){
		for(;j<ord[i+1];j++) sum[i][a[j]]++;
		for(int k=B-1;k;k--) sum[i][k-1]+=sum[i][k];
	}
	for(int i=0;i<q;i++) s[i].work();
}
