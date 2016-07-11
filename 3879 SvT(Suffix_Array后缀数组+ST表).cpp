#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;
typedef long long ll;
const int N=(int)5e5+5,logN=20,K=(int)3e6+5;

int n,len,sa[N],rank[N],base[N],st[logN][N];
char s[N];

bool cmp(int i,int j){
	return rank[i]!=rank[j]?rank[i]<rank[j]:rank[i+len]<rank[j+len];
}

void getsa(int n,int m,char *s,int *sa,int *rank){
	static int tmp[N],sum[N];
	for(int i=0;i<=m;i++) sum[i]=0;
	for(int i=0;i<=n;i++) sum[s[i]]++;
	for(int i=1;i<=m;i++) sum[i]+=sum[i-1];
	for(int i=n;i>=0;i--) sa[--sum[s[i]]]=i;
	for(int i=0;i<=n;i++)
		rank[sa[i]]=i&&s[sa[i-1]]==s[sa[i]]?rank[sa[i-1]]:i;
	for(len=1;len<n;len<<=1){
		int top=0;
		for(int i=n-len;i<=n;i++) tmp[top++]=i;
		for(int i=1;i<=n;i++) if(sa[i]-len>=0) tmp[top++]=sa[i]-len;
		for(int i=0;i<=n;i++) sum[i]=0;
		for(int i=0;i<=n;i++) sum[rank[tmp[i]]]++;
		for(int i=1;i<=n;i++) sum[i]+=sum[i-1];
		for(int i=n;i>=0;i--) sa[--sum[rank[tmp[i]]]]=tmp[i];
		for(int i=0;i<=n;i++)
			tmp[sa[i]]=i&&!cmp(sa[i-1],sa[i])?tmp[sa[i-1]]:i;
		for(int i=0;i<=n;i++) rank[i]=tmp[i];
	}
}

void getheight(int n,char *s,int *sa,int *rank,int *height){
	for(int i=0,h=0;i<n;height[rank[i++]]=h)
		for(h?h--:0;s[sa[rank[i]-1]+h]==s[i+h];h++);
}

int calc(int l,int r){
	int j=base[r-l];
	return min(st[j][r],st[j][l+(1<<j)]);
}

ll outcome;
int k,top,seq[K];
struct data{
	int cnt,val;
} q[N];

int main(){
	int m;
	scanf("%d%d",&n,&m);
	scanf("%s",s);
	for(int i=0;i<n;i++) s[i]-='a'-1;
	getsa(n,26,s,sa,rank);
	getheight(n,s,sa,rank,st[0]);
	for(int j=1;(1<<j)<=n;j++)
		for(int i=1<<j;i<=n;i++)
			st[j][i]=min(st[j-1][i],st[j-1][i-(1<<j-1)]);
	for(int i=2;i<=n;i++) base[i]=base[i>>1]+1;
	while(m--){
		scanf("%d",&k);
		for(int i=0;i<k;i++) scanf("%d",&seq[i]),seq[i]=rank[seq[i]-1];
		sort(seq,seq+k);
		k=unique(seq,seq+k)-seq;
		ll ans=0;
		outcome=0;
		q[top=1]=(data){0,0};
		for(int i=1;i<k;i++){
			int c=1,v=calc(seq[i-1],seq[i]);
			while(v<q[top].val){
				outcome-=(ll)q[top].cnt*q[top].val;
				c+=q[top].cnt;
				top--;
			}
			q[++top]=(data){c,v};
			outcome+=(ll)c*v;
			ans+=outcome;
		}
		printf("%lld\n",ans);
	}
}
