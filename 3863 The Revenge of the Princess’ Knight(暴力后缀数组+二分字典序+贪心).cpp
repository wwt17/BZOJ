#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;
typedef pair<int,int> pii;

const int N=1005;

int n,k;
char s[N*2];
int sa[N*2],height[N];
int d[N];

bool cmp(const int i,const int j){
	return strcmp(s+i,s+j)<0;
}

pii seq[N*N],*top;

int q[N],deg[N];

void Main(){
	scanf("%d%d",&n,&k);
	scanf("%s",s);
	for(int i=0;i<n;i++) s[i+n]=s[i];
	for(int i=0;i<=n*2;i++) sa[i]=i;
	s[n*2]=0;
	sort(sa,sa+n*2+1,cmp);
	for(int i=1,j=1;i<=n*2;i++) if(sa[i]<n){
		sa[j++]=sa[i];
	}
	sa[0]=n;
	height[1]=0;
	for(int i=2;i<=n;i++){
		int j;
		for(j=0;j<n&&s[sa[i-1]+j]==s[sa[i]+j];j++);
		height[i]=j;
	}
	top=seq;
	for(int i=1;i<=n;i++)
		for(int j=height[i]+1;j<=n;j++)
			*top++=pii(i,j);
	pii *l=seq-1,*r=top;
	while(r-l>1){
		pii *mid=l+(r-l>>1);
		int now;
		for(int i=1;i<mid->first;i++) d[sa[i]]=n;
		now=mid->second;
		for(int i=mid->first;i<=n;i++)
			d[sa[i]]=now,now=min(now,height[i+1]);
		
		int head=0,tail=0;
		for(int i=0;i<n;i++){
			deg[i]=d[i];
			if(deg[i]==0) q[tail++]=i;
		}
		while(head<tail){
			int u=q[head++];
			for(int v=0;v<n;v++) if(u>=v&&u<=v+d[v]||u<v&&u+n<=v+d[v]){
				if(!--deg[v]) q[tail++]=v;
			}
		}
		
		if(n-tail<k){
			l=mid;
			continue;
		}
		
		bool ok=false;
		for(int i=0;i<n;i++){
			int cnt=0;
			for(int x=0,y=0,j=0;x<n;){
				for(;j<=x;j++) y=max(y,j+d[j]);
				if(x==y){
					cnt=N;
					break;
				}
				cnt++;
				x=y;
			}
			if(cnt<=k) ok=true;
			d[n]=d[0];
			for(int j=0;j<n;j++) d[j]=d[j+1];
		}
		if(ok)
			r=mid;
		else
			l=mid;
	}
	for(int j=0;j<r->second;j++) putchar(s[sa[r->first]+j]); putchar('\n');
}

int main(){
	freopen("in.txt","r",stdin);
	freopen("wwt.txt","w",stdout);
	int T; scanf("%d",&T);
	while(T--) Main();
}
