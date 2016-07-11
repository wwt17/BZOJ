#include <cstdio>
const int N=100005;
int n,q,p,m,d,g,a[N];
int nex[N],next[N];
bool vis[N];
int gcd(int a,int b){
	return b?gcd(b,a%b):a;
}
int get(int *a,int i){
	if(a[i]==i) return i;
	return a[i]=get(a,a[i]);
}
void add(int x){
	int y=get(next,(x+d)%n);
	if(x!=y)
		next[x]=y;
	else{
		x=x%g;
		y=get(nex,(x+1)%g);
		if(x!=y)
			nex[x]=y;
	}
}
int work(){
	scanf("%d%d%d%d%d%d",&n,&a[0],&q,&p,&m,&d);
	g=gcd(d,n);
	for(int i=0;i<n;i++) next[i]=i;
	for(int i=0;i<g;i++) nex[i]=i;
	add(a[0]);
	int c=0;
	for(int i=1;i<n;i++){
		c=(1LL*c*q+p)%m;
		int now=c%n;
		int y=get(nex,now%g);
		a[i]=get(next,(now+(y-now%g+g)%g)%n);
		add(a[i]);
	}
	int cnt=0;
	for(int i=0;i<n;i++) cnt+=!(vis[i]=a[i]==i);
	for(int i=0;i<n;i++) if(!vis[i]){
		cnt++;
		for(int j=i;!vis[j];j=a[j]) vis[j]=true;
	}
	return cnt+(a[0]==0?0:-2);
}
int main(){
	int T; scanf("%d",&T);
	while(T--)
		printf("%d\n",work());
}
