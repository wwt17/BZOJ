#include <cstdio>
const int N=3000000;
int n,k,x,y,a,f,v[N],next[N];
bool occupied[N];
int belong(int i){
	if(v[i]==i) return i;
	return v[i]=belong(v[i]);
}
int main(){
	scanf("%d%d",&n,&k);
	for(int i=0;i<n;i++) next[i]=i+1;
	next[n-1]=0;
	while(k--){
		scanf("%d%d%d%d",&x,&y,&a,&f);
		while(y--){
			f=(f+a)%n;
			int last=occupied[(f?f:n)-1]?(f?f:n)-1:f,cur=f;
			for(int cnt=x;cnt;occupied[cur]=true,cur=next[cur],cnt--)
				if(occupied[cur]){
					belong(cur);
					for(;last!=cur;last=next[last]) v[last]=v[cur];
					last=v[cur];
					cur=next[last];
				}
			if(occupied[cur])
				for(;last!=cur;last=next[last]) v[last]=cur;
			else
				for(;last!=cur;last=next[last]) v[last]=(cur?cur:n)-1;
		}
	}
	for(int i=0;;i++) if(!occupied[i]){
		printf("%d\n",i);
		return 0;
	}
}
