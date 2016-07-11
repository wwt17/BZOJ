#include <cstdio>
#include <cmath>
#include <algorithm>
using namespace std;
typedef long long ll;

const int N=100005;

int gcd(const int a,const int b){
	return b?gcd(b,a%b):a;
}

int n,s;
int a[N],b[N],c[N];

int t[N*4];

void modify(int loc,int cur=1,int beg=0,int end=n){
	if(end-beg==1){
		t[cur]=a[loc];
		return;
	}
	int mid=(beg+end)>>1;
	if(loc<mid)
		modify(loc,cur<<1,beg,mid);
	else
		modify(loc,cur<<1|1,mid,end);
	t[cur]=gcd(t[cur<<1],t[cur<<1|1]);
}

int get(int g,int cur=1,int beg=0,int end=n){
	if(t[cur]%g==0) return end;
	if(end-beg==1)
		return beg;
	int mid=(beg+end)>>1;
	int x=get(g,cur<<1,beg,mid);
	if(x<mid)
		return x;
	else
		return get(g,cur<<1|1,mid,end);
}

void rebuild(int st){
	st*=s;
	int sum=0;
	int en=st;
	for(;en<n&&en<st+s;en++) c[en]=b[en]=sum^=a[en];
	sort(c+st,c+en);
}

int main(){
	freopen("in","r",stdin);
	freopen("out","w",stdout);
	scanf("%d",&n);
	s=min(max(1,(int)sqrt(n*log(n)/log(2))),n);
	for(int i=0;i<n;i++) scanf("%d",&a[i]),modify(i);
	for(int i=0;i*s<n;i++) rebuild(i);
	int q; scanf("%d",&q);
	while(q--){
		static char type[10]; scanf("%s",type);
		if(type[0]=='M'){
			int i; scanf("%d",&i);
			scanf("%d",&a[i]);
			modify(i);
			rebuild(i/s);
		}
		else{
			ll x; scanf("%lld",&x);
			int ans=-1;
			for(int last=0,g=0,next,sum=0;last<n;last=next){
				/*
				int tmp=0;
				for(int j=0;j<last/s*s;j++) tmp^=a[j];
				if(tmp!=sum)
					printf("err tmp=%d sum=%d\n",tmp,sum);
				*/
				g=gcd(g,a[last]);
				next=get(g);
			//	printf("last=%d next=%d g=%d\n",last,next,g);
				int val=x%g||x/g>0x7fffffff?-1:x/g;
			//	printf("a[%d]=%d val=%d\n",last,a[last],val);
				if(last/s==next/s){
					if(val!=-1)
					for(int j=last;j<next;j++) if((sum^b[j])==val){
						ans=j;
						goto out;
					}
				}
				else{
					if(val!=-1)
					for(int j=last;j<(last/s+1)*s;j++) if((sum^b[j])==val){
						ans=j;
						goto out;
					}
					sum^=b[last/s*s+s-1];
					for(int j=(last/s+1)*s;j+s<=next;j+=s){
						if(val!=-1&&*lower_bound(c+j,c+j+s,sum^val)==(sum^val)){
							for(;;j++) if((sum^b[j])==val){
								ans=j;
								goto out;
							}
						}
						sum^=b[j+s-1];
					}
					if(val!=-1)
					for(int j=next/s*s;j<next;j++) if((sum^b[j])==val){
						ans=j;
						goto out;
					}
				}
			}
			out:;
			if(ans==-1)
				puts("no");
			else
				printf("%d\n",ans);
		}
	}
}
