#include <cstdio>
struct trie{
	int fail,son[10];
	int mark;
	double f[1<<8];
} tr[55];
int T,t,n,m,C;
char s[10];
double p[10],e[55][55];
void build(){
	tr[0].fail=0;
	for(int c=0;c<C;c++) tr[0].son[c]=1;
	int q[55],*head=q,*tail=q;
	*tail++=1;
	while(head<tail){
		int u=*head++;
		for(int c=0;c<C;c++) if(tr[u].son[c])
			tr[*tail++=tr[u].son[c]].fail=tr[tr[u].fail].son[c];
		else
			tr[u].son[c]=tr[tr[u].fail].son[c];
	}
	tr[1].fail=1;
}
void calc(int k){
	for(int i=1;i<=t;i++){
		for(int j=1;j<=t+1;j++) e[i][j]=0;
		e[i][i]=e[i][t+1]=1;
		for(int c=0;c<C;c++){
			int kk=k|tr[tr[i].son[c]].mark;
			if(kk==k)
				e[i][tr[i].son[c]]-=p[c];
			else
				e[i][t+1]+=p[c]*tr[tr[i].son[c]].f[kk];
		}
	}
	for(int i=1;i<=t;i++){
		for(int k=t+1;k>=i;k--) e[i][k]/=e[i][i];
		for(int j=1;j<=t;j++) if(j!=i)
			for(int k=t+1;k>=i;k--)
				e[j][k]-=e[i][k]*e[j][i];
	}
	for(int i=1;i<=t;i++)
		tr[i].f[k]=e[i][t+1];
}
int main(){
	scanf("%d",&T);
	while(T--){
		scanf("%d%d%d",&n,&m,&C);
		t=1;
		for(int c=0;c<C;c++) tr[1].son[c]=0;
		for(int i=0;i<n;i++){
			scanf("%s",s);
			int cur=1;
			for(int j=0;j<m;j++){
				if(!tr[cur].son[s[j]-'a']){
					tr[cur].son[s[j]-'a']=++t;
					tr[cur].fail=0;
					for(int c=0;c<C;c++) tr[t].son[c]=0;
					tr[cur].mark=0;
				}
				cur=tr[cur].son[s[j]-'a'];
			}
			tr[cur].mark|=1<<i;
		}
		for(int c=0;c<C;c++) scanf("%lf",&p[c]),p[c]/=10000;
		build();
		for(int u=1;u<=t;u++) tr[u].f[(1<<n)-1]=0;
		for(int k=(1<<n)-2;k>=0;k--)
			calc(k);
		printf("%lf\n",tr[1].f[0]);
	}
}
