#include <cstdio>
#include <algorithm>
using namespace std;

const int N=(int)1e5+5;

typedef double real;
typedef long long ll;

int n,k;

struct item{
	int x,y,c;
	friend bool operator < (const item &a,const item &b){
		return a.x*b.y<b.x*a.y;
	}
	real val() const{
		return (real)x/y;
	}
} a[N];

real calc(int p){
	real ans=0;
	int i,j,s,t;
	for(i=1,s=p;s>a[i].c;s-=a[i++].c)
		ans+=a[i].val()*((1-a[i].val())*(a[i].c-1)+(1-a[i+1].val()));
	if(s) ans+=a[i].val()*(1-a[i].val())*(s-1);
	for(j=n,t=k-p;t>a[j].c;t-=a[j--].c)
		ans+=(1-a[j].val())*(a[j].val()*(a[j].c-1)+a[j-1].val());
	if(t) ans+=(1-a[j].val())*a[j].val()*(t-1);
	if(s&&t) ans+=a[i].val()*(1-a[j].val());
	return ans;
}

ll tot;

int get(ll s){
	if(s<1) return 0;
	if(s>tot) return n+1;
	int i;
	for(i=1;s>a[i].c;s-=a[i++].c);
	return i;
}

real Main(){
	scanf("%d%d",&n,&k);
	tot=0;
	for(int i=1;i<=n;i++){
		scanf("%d/%d%d",&a[i].x,&a[i].y,&a[i].c),a[i].x=a[i].y-a[i].x,tot+=a[i].c;
		if(a[i].c==0){
			i--;
			n--;
		}
	}
	sort(a+1,a+n+1);
	a[0].x=0;
	a[0].y=1;
	a[n+1].x=1;
	a[n+1].y=1;
	int l=-1,r=k;
	while(r-l>1){
		int mid=(l+r)>>1;
		int u=get(mid),v=get(tot-(k-mid)+2);
		if(a[u].x*a[v].y+a[v].x*a[u].y-a[u].y*a[v].y<0)
			l=mid;
		else
			r=mid;
	}
	return calc(r);
}

int main(){
	int T; scanf("%d",&T);
	while(T--)
		printf("%.6lf\n",(double)Main());
}
