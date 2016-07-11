#include <cstdio>
#include <algorithm>
using namespace std;
typedef pair<int,int> pii;

const int N=500005,M=N;
int n,m,tt,t[N],ans[M],ord[N],*top=ord;
pii a[N];
struct que{
	int x,y1,y2,id;
	bool operator < (const que &b) const{
		return x<b.x;
	}
} q[M<<1];

int main(){
	scanf("%d%d",&n,&m);
	for(int i=0;i<n;i++){
		scanf("%d%d",&a[i].first,&a[i].second);
		*top++=a[i].second;
	}
	sort(a,a+n);
	sort(ord,top);
	top=unique(ord,top);
	tt=top-ord;
	for(int i=0;i<n;i++)
		a[i].second=lower_bound(ord,top,a[i].second)-ord+1;
	for(int i=0;i<m;i++){
		int a,b,c,d;
		scanf("%d%d%d%d",&a,&b,&c,&d);
		a--,b--;
		b=upper_bound(ord,top,b)-ord;
		d=upper_bound(ord,top,d)-ord;
		q[i<<1]=(que){a,b,d,-i-1};
		q[i<<1|1]=(que){c,b,d,i+1};
	}
	sort(q,q+(m<<1));
	for(int i=0,j=0;i<m<<1;i++){
		for(;j<n&&a[j].first<=q[i].x;j++)
			for(int x=a[j].second;x<=tt;x+=x&-x) t[x]++;
		int now=0;
		for(int x=q[i].y1;x;x-=x&-x) now-=t[x];
		for(int x=q[i].y2;x;x-=x&-x) now+=t[x];
		if(q[i].id<0) ans[-q[i].id]-=now;
		else ans[q[i].id]+=now;
	}
	for(int i=1;i<=m;i++) printf("%d\n",ans[i]);
}
