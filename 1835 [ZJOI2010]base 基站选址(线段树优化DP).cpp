/*
 assume t[j] = f[k-1][j] + w(j,i)
 assume l[j] = max(k){ d[k]<d[j]-s[k] }
 f[k][i] = min(1<=j<i){ f[k-1][j] + w(j,i) } + c[i]
 w(j,i) = sigma(j<k<i&&d[j]<d[k]-s[k]&&d[k]+s[k]<d[i]){ w[k] }
 i->i+1
 for each k meeting d[i]<=d[k]+s[k]<d[i+1]
  t[1..l[k]] += w[k]
 f[k][i] = min(1<=j<i){ t[j] } + c[i]
*/
#include <cstdio>
#include <algorithm>
//#define debug
const int N=20005,T=1<<16,inf=1100000000;
int K,n,base,d[N],c[N],s[N],w[N],ord[N],l[N],f[N];
struct data{
	int cov,min;
} t[T];
#define update(x) t[x].min=std::min(t[x<<1].min,t[x<<1|1].min)+t[x].cov
void modify(int l,int r,int delta){
	if(l>r) return;
	for(l+=base-1,r+=base+1;l^r^1;l>>=1,update(l),r>>=1,update(r)){
		if(!(l&1)) t[l^1].cov+=delta,t[l^1].min+=delta;
		if(  r&1 ) t[r^1].cov+=delta,t[r^1].min+=delta;
	}
	while(l>>=1) update(l);
}
int query(int l,int r){
	if(l>r) return inf;
	int lmin=inf,rmin=inf;
	for(l+=base-1,r+=base+1;l^r^1;lmin+=t[l>>=1].cov,rmin+=t[r>>=1].cov){
		if(!(l&1)) lmin=std::min(lmin,t[l^1].min);
		if(  r&1 ) rmin=std::min(rmin,t[r^1].min);
	}
	lmin=std::min(lmin,rmin);
	while(l>>=1) lmin+=t[l].cov;
	return lmin;
}
inline bool cmp(const int a,const int b){
	return d[a]+s[a]<d[b]+s[b];
}
int main(){
	scanf("%d%d",&n,&K); n++;
	for(base=1;base<n+2;base++);
	for(int i=2;i<n;i++) scanf("%d",d+i); d[n]=d[n-1]+inf;
	for(int i=1;i<n;i++) scanf("%d",c+i); c[n]=0;
	for(int i=1;i<n;i++) scanf("%d",s+i); s[n]=0;
	for(int i=1;i<n;i++) scanf("%d",w+i); w[n]=0;
	for(int i=1;i<=n;i++) ord[i]=i;
	std::sort(ord+1,ord+n+1,cmp);
	for(int i=1;i<=n;i++) l[i]=std::lower_bound(d+1,d+i,d[i]-s[i])-d-1;
	int g=0;
	f[1]=c[1];
	#ifdef debug
	printf("%4d",f[1]);
	#endif
	for(int i=1,j=1;i<n;i++){
		for(;j<=n&&d[ord[j]]+s[ord[j]]<d[i+1];j++)
			g+=w[ord[j]];
		f[i+1]=g+c[i+1];
		#ifdef debug
		printf("%4d",f[i+1]);
		#endif
	}
	int ans=f[n];
	#ifdef debug
	puts("");
	#endif
	for(int k=2;k<=K+1;k++){
		for(int i=1;i<=n;i++) t[base+i]=(data){f[i],f[i]};
		for(int l=base>>1,r=(base+n+1)>>1;l^r^1;l>>=1,r>>=1)
			for(int i=l+1;i<r;i++) t[i].cov=0,update(i);
		f[1]=c[1];
		#ifdef debug
		printf("%4d",f[1]);
		#endif
		for(int i=1,j=1;i<n;i++){
			for(;j<=n&&d[ord[j]]+s[ord[j]]<d[i+1];j++)
				modify(1,l[ord[j]],w[ord[j]]);
			f[i+1]=query(1,i)+c[i+1];
			#ifdef debug
			printf("%4d",f[i+1]);
			#endif
			//modify(1,l[i+1],w[i+1]);
		}
		ans=std::min(ans,f[n]);
		#ifdef debug
		puts("");
		#endif
	}
	printf("%d\n",ans);
	scanf("\n");
}
