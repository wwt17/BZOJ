#include <cstdio>
const int N=110;
int n,len;
struct node *null,*a[N],*b[N],*c[N];
struct node{
	node *son[2];
	int st,en;
	void dfs(){
		if(this==null) return;
		st=len;
		len++;
		son[0]->dfs();
		son[1]->dfs();
		en=len;
		int cnt[2];
		for(int i=0;i<2;i++) cnt[i]=son[i]->en-son[i]->st;
		bool flag=0;
		for(int i=0;;i++){
			if(!cnt[i&1^1]){
				c[en-i]=this;
				for(int j=i+1;j<en-st;j++)
					c[en-j]=a[son[i&1]->st+(en-st-j)];
				bool ok=1;
				if(flag){
					for(int j=st+1;j<=en;j++) if(c[j]>b[j]) ok=0;
				}
				if(ok){
					for(int j=st+1;j<=en;j++) b[j]=c[j];
				}
			}
			if(!cnt[i&1]) break;
			cnt[i&1]--;
			c[en-i]=a[son[i&1]->en-(i>>1)];
		}
		for(int i=st+1;i<=en;i++) a[i]=b[i];
	}
} V[N];
int main(){
	scanf("%d",&n);
	null=new node;
	for(int i=0;i<=n;i++) V[i].son[0]=V[i].son[1]=null;
	for(int i=1;i<=n;i++){
		int d; scanf("%d",&d);
		V[d%100].son[d/100]=V+i;
	}
	V[0].dfs();
	for(int i=1;i<=len;i++) printf("%d ",a[i]-V);
}
