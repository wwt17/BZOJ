#include <cstdio>
#include <algorithm>
using namespace std;
typedef long long ll;
const int mo=(int)1e9+7;

int n,k,L;
int ans;

int val[15];
ll inv[15];

void dfs(int i,int last,int s,int c){
	if(i==n){
		val[i]=k;
		ll p1=1,p2=1;
		for(int j=1;j<i;j++){
			p1=p1*max(0,L-max(1,val[i]-val[j])+1)%mo;
			p2=p2*max(0,L-max(1,val[i]-val[j]+1)+1)%mo;
		}
		s=s*(p1+mo-p2)%mo;
		if((ans+=s)>=mo) ans-=mo;
		return;
	}
	for(val[i]=last;val[i]<=k+1;val[i]++){
		ll ss=s;
		ll p1=1,p2=1;
		for(int j=1;j<i;j++){
			p1=p1*max(0,L-max(1,val[i]-val[j])+1)%mo;
			p2=p2*max(0,L-max(1,val[i]-val[j]+1)+1)%mo;
		}
		if(val[i]==k+1)
			ss=ss*p1%mo;
		else
			ss=ss*(p1+mo-p2)%mo;
		int cc=val[i]==last?c+1:1;
		ss=ss*(i-1)%mo*inv[cc]%mo;
		dfs(i+1,val[i],ss,cc);
	}
}

int Main(){
	scanf("%d%d%d",&n,&k,&L);
	ans=0;
	val[1]=0;
	dfs(2,1,1,0);
	return ans;
}

int main(){
	inv[1]=1;
	for(int i=2;i<15;i++) inv[i]=ll(mo-mo/i)*inv[mo%i]%mo;
	int T; scanf("%d",&T);
	while(T--) printf("%d\n",Main());
}
