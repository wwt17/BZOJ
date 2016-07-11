#include <cstdio>
const int N=50005,K=155,mo=10007;
int n,k,S[K][K],fac[K],w[K];

void init(){
	S[0][0]=1;
	for(int i=1;i<=k;i++)
		for(int j=1;j<=k;j++)
			S[i][j]=(S[i-1][j-1]+j*S[i-1][j])%mo;
	fac[0]=1;
	for(int i=1;i<=k;i++) fac[i]=fac[i-1]*i%mo;
	for(int i=0;i<=k;i++) w[i]=S[k][i]*fac[i]%mo;
}

struct node{
	node *son,*next;
	int f[K],g[K];
	void dfs1(){
		f[0]=1;
		for(node *v=son;v;v=v->next){
			v->dfs1();
			for(int i=0;i<=k;i++)
				f[i]+=v->f[i]+(i?v->f[i-1]:0);
		}
		for(int i=0;i<=k;i++) f[i]%=mo;
	}
	void dfs2(){
		for(node *v=son;v;v=v->next){
			for(int i=0;i<=k;i++)
				g[i]=f[i]+mo*2-v->f[i]-(i?v->f[i-1]:0);
			for(int i=0;i<=k;i++)
				(v->f[i]+=g[i]+(i?g[i-1]:0))%=mo;
			v->dfs2();
		}
	}
	int calc(){
		int ans=0;
		for(int i=0;i<=k;i++)
			ans=(ans+w[i]*f[i])%mo;
		return ans;
	}
} V[N];

void read(){
	int L,now,A,B,Q;
	scanf("%d%d%d",&n,&k,&L);
	scanf("%d%d%d%d",&now,&A,&B,&Q);
	for(int i=1;i<n;i++){
		int x=i+1,y=i-(now=(now*A+B)%Q)%(i<L?i:L);
		V[x].next=V[y].son;
		V[y].son=V+x;
	}
}

int main(){
	read();
	init();
	V[1].dfs1();
	V[1].dfs2();
	for(int i=1;i<=n;i++)
		printf("%d\n",V[i].calc());
}
