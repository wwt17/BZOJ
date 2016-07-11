#include <cstdio>
#include <algorithm>
using namespace std;

const int N=12005,S=125,b=31;
int n,m,s;

inline int getint(){
	char c;
	while((c=getchar())<'0'); int a=c-'0';
	while((c=getchar())>='0'&&c<='9') a=a*10+c-'0';
	return a;
}

int a[N];

struct trie{
	trie *son[2];
} mem[N*(N/S+2)/2*32],mem2[N*32],*newtrie=mem,*p[N/S+2][N];
int q[N/S+2][N];

trie *insert(trie *last,int b,int a){
	trie *cur=newtrie++;
	if(last) *cur=*last;
	else cur->son[0]=cur->son[1]=NULL;
	trie *tmp=cur;
	while(b--){
		trie *t=newtrie++;
		if(cur->son[a>>b&1]) *t=*cur->son[a>>b&1];
		else t->son[0]=t->son[1]=NULL;
		cur=cur->son[a>>b&1]=t;
	}
	return tmp;
}

int query(trie *cur,int b,int a){
	int ans=0;
	while(b--)
		if(cur->son[a>>b&1]){
			cur=cur->son[a>>b&1];
			ans|=(a>>b&1)<<b;
		}
		else{
			cur=cur->son[(a>>b&1)^1];
			ans|=((a>>b&1)^1)<<b;
		}
	return ans;
}

int main(){
	scanf("%d%d",&n,&m);
	for(s=0;s*s<n;s++);
	s+=15;
	for(int i=1;i<=n;i++) a[i]=a[i-1]^getint();
	for(int i=0;i*s<=n;i++){
		p[i][i*s]=insert(NULL,b,a[i*s]);
		for(int j=i*s+1;j<=n;j++){
			q[i][j]=max(q[i][j-1],query(p[i][j-1],b,~a[j])^a[j]);
			p[i][j]=insert(p[i][j-1],b,a[j]);
		}
	}
	int ans=0;
	while(m--){
		newtrie=mem2;
		int l=(getint()%n+ans%n)%n+1,r=(getint()%n+ans%n)%n+1;
		if(l>r) swap(l,r);
		l--;
		ans=0;
		int k=l/s+1;
		if(r<k*s){
			trie *now=insert(NULL,b,a[l]);
			for(int j=l+1;j<=r;j++){
				ans=max(ans,query(now,b,~a[j])^a[j]);
				now=insert(now,b,a[j]);
			}
		}
		else{
			ans=q[k][r];
			trie *now=p[k][r];
			for(int j=l;j<k*s;j++){
				ans=max(ans,query(now,b,~a[j])^a[j]);
				now=insert(now,b,a[j]);
			}
		}
		printf("%d\n",ans);
	}
}
