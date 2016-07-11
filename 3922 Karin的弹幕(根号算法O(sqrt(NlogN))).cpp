#include <cstdio>
#include <cmath>
#include <algorithm>
using namespace std;

const int N=70005,S=10;

int n,m,s,d,b,a[N];

int mem[60000005],*newint=mem;

int *t[S][S],len[S][S];

int X,D,L,R;

void modify(int *t,int cur,int beg,int end){
	if(end-beg==1){
		t[cur]=D;
		return;
	}
	int mid=beg+end>>1;
	if(X<mid)
		modify(t,cur<<1,beg,mid);
	else
		modify(t,cur<<1|1,mid,end);
	t[cur]=max(t[cur<<1],t[cur<<1|1]);
}
int query(int *t,int cur,int beg,int end){
	if(end<=L||beg>=R) return 0x80000000;
	if(beg>=L&&end<=R) return t[cur];
	int mid=beg+end>>1;
	return max(query(t,cur<<1,beg,mid),query(t,cur<<1|1,mid,end));
}

void modify(int p,int v){
	a[p]=v;
	for(d=1;d<=s;d++){
		b=p%d;
		X=(p-b)/d;
		D=v;
		modify(t[d][b],1,0,len[d][b]);
	}
}

int main(){
	freopen("in.txt","r",stdin);
	freopen("out.txt","w",stdout);
	scanf("%d",&n);
	s=min(max(1,(int)sqrt(n*log(n)/log(2))),S-5);
	for(int i=0;i<n;i++) scanf("%d",&a[i]);
	for(d=1;d<=s;d++)
		for(b=0;b<d;b++){
			len[d][b]=(n-1-b)/d+1;
			t[d][b]=newint-1;
			newint+=len[d][b]*4;
		}
	for(int i=0;i<n;i++) modify(i,a[i]);
	scanf("%d",&m);
	while(m--){
		int op; scanf("%d",&op);
		if(op==0){
			int p,v; scanf("%d%d",&p,&v); p--;
			modify(p,a[p]+v);
		}
		else{
			int p; scanf("%d%d",&p,&d); p--;
			b=p%d;
			if(d<=s){
				L=(p-b)/d,R=len[d][b];
				printf("%d\n",query(t[d][b],1,0,len[d][b]));
			}
			else{
				int ans=0x80000000;
				for(;p<n;p+=d) ans=max(ans,a[p]);
				printf("%d\n",ans);
			}
		}
	}
}
