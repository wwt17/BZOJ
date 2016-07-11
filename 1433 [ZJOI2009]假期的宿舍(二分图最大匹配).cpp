#include <cstdio>
const int N=51;
int n,pre[N];
bool insch[N],stay[N],know[N][N],used[N];
bool extend(int u){
	if(!u) return true;
	for(int v=1;v<=n;v++) if(know[u][v]&&!used[v]){
		used[v]=true;
		if(extend(pre[v])){
			pre[v]=u;
			return true;
		}
	}
	return false;
}
int main(){
	int T,b; scanf("%d",&T);
	#define getbool() (scanf("%d",&b),b)
	while(T--){
		scanf("%d",&n);
		for(int i=1;i<=n;i++) insch[i]=getbool(),pre[i]=0;
		for(int i=1;i<=n;i++) stay[i]=!getbool()||!insch[i];
		for(int i=1;i<=n;i++)
			for(int j=1;j<=n;j++)
				know[i][j]=(getbool()||i==j)&&insch[j];
		bool ok=true;
		for(int i=1;i<=n;i++) if(stay[i]){
			for(int j=1;j<=n;j++) used[j]=false;
			if(!extend(i)) ok=false;
		}
		puts(ok?"^_^":"T_T");
	}
	scanf("\n");
}
