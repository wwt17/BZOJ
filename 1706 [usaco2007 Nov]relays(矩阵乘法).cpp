#include <cstdio>
#include <algorithm>
#define sizeV 1001
#define INF 1000000001LL
#define ll long long
inline void mini(ll &a,const ll b){if(a>b)a=b;}
int N,T,S,E;
struct node;
struct edge{
	node* ed; edge* next; int w;
	edge(node* _ed,edge* _next,int _w):
		ed(_ed),next(_next),w(_w){}
};
struct node{
	edge* son;
	void addedge(node* ed,int w){
		son=new edge(ed,son,w);
	}
} V[sizeV];
int Nosum,No[201];
ll f[2][201][201],ans[2][201][201]; bool F,A;
#define find(a) std::lower_bound(No+1,No+Nosum+1,a)-No
inline void mulf(){
	int i,j,k;
	for(i=1;i<=Nosum;++i)
		for(j=1;j<=Nosum;++j){
			f[!F][i][j]=INF;
			for(k=1;k<=Nosum;++k)
				mini(f[!F][i][j],f[F][i][k]+f[F][k][j]);
		}
	F^=1;
}
inline void mulans(){
	int i,j,k;
	for(i=1;i<=Nosum;++i)
		for(j=1;j<=Nosum;++j){
			ans[!A][i][j]=INF;
			for(k=1;k<=Nosum;++k)
				mini(ans[!A][i][j],ans[A][i][k]+f[F][k][j]);
		}
	A^=1;
}
int main(){
	int i,j;
	scanf("%d%d%d%d",&N,&T,&S,&E);
	int length_i,I1_i,I2_i;
	for(i=1;i<=T;++i){
		scanf("%d%d%d",&length_i,&I1_i,&I2_i);
		V[I1_i].addedge(V+I2_i,length_i);
		V[I2_i].addedge(V+I1_i,length_i);
	}
	for(i=1;i<sizeV;++i) if(V[i].son){
		No[++Nosum]=i;
		for(j=1;j<=Nosum;++j) f[F][Nosum][j]=f[F][j][Nosum]=INF;
		for(edge* e=V[i].son;e;e=e->next)
			if((j=find(e->ed-V))<=Nosum)
				f[F][Nosum][j]=f[F][j][Nosum]=e->w;
	}
	for(i=1;i<=Nosum;++i){
		for(j=1;j<=Nosum;++j) ans[A][i][j]=INF;
		ans[A][i][i]=0;
	}
	for(;N;N>>=1,mulf())
		if(N&1) mulans();
	printf("%lld\n",ans[A][find(S)][find(E)]);
}
	
