#include <cstdio>
#include <cstring>
#define N 52
#define M 2001
#define INF 0x7FFFFFFF
template<class T>
bool tension(T &a,const T &b)
	{ return b<a?(a=b,true):false; }
template<class T>
bool relax(T &a,const T &b)
	{ return a<b?(a=b,true):false; }
int n,m;
inline bool relaxDP(int *a,int *b){
	bool updated=false;
	/*
	for(int i=m;i>=0;i--)
		for(int j=0;i+j<=m;j++)
			updated|=relax(a[i+j],a[i]+b[j]);
	*/
	for(int i=m-1;i>=0;i--) if(a[i] || i==0)
		for(int j=1;i+j<=m;j++)
			if(b[j] && relax(a[i+j],a[i]+b[j]))
				updated=true;
	int maxv=0;
	for(int i=0;i<=m;i++)
		if(a[i]<=maxv)
			a[i]=0;
		else
			maxv=a[i];
	return updated;
}
struct equipment{
	equipment *son,*next;
	int money,energy,maxsum,needsum,f[M],g[M];
	equipment():maxsum(INF){}
	void init();
	void dfs(int sum);
} e[N];
void equipment::init(){
	for(equipment *u=son;u;u=u->next){
		u->init();
		money+=u->money*u->needsum;
		//energy+=u->energy*u->needsum;
		tension(maxsum,u->maxsum/u->needsum);
	}
}
void equipment::dfs(int sum){
	for(equipment *u=son;u;u=u->next)
		u->dfs(maxsum * u->needsum);
	static int h[M];
	memset(h,0,(m+1)*sizeof(h[0]));
	for(equipment *u=son;u;u=u->next){
		relaxDP(h,u->f);
		for(int i=0;i<u->needsum;i++)
			if(!relaxDP(g,u->g))
				break;
	}
	bool updated=true;
	for(int i=maxsum-sum;i>=0;i--){
		for(int j=money*i;j<=m;j++)
			relax(f[j],h[j-money*i]+energy*i);
		if(updated)
			updated=relaxDP(h,g);
	}
	if(money<=m)
		relax(g[money],energy);
}
int main(){
	int i;
	scanf("%u%u",&n,&m);
	for(i=1;i<=n;i++){
		scanf("%d ",&e[i].energy);
		if(getchar()=='B')
			scanf("%d%d",&e[i].money,&e[i].maxsum);
		else{
			int C,j; scanf("%u",&C);
			while(C--){
				scanf("%u",&j);
				scanf("%u",&e[j].needsum);
				e[j].next=e[i].son;
				e[i].son=&e[j];
			}
		}
	}
	for(i=1;i<=n;i++) if(!e[i].needsum) break;
	e[i].init();
	e[i].dfs(0);
	int Ans=0;
	for(int j=0;j<=m;j++) relax(Ans,e[i].f[j]);
	printf("%d\n",Ans);
}
