#include <cstdio>
#include <algorithm>
using namespace std;
const int N=200005,Q=200000,T=1<<19;
inline int getint(){
	char c;
	while((c=getchar())<'0'||c>'9'); int a=c-'0';
	while((c=getchar())>='0'&&c<='9') a=a*10+c-'0';
	return a;
}
inline void println(int a){
	static char s[10]; char *top=s;
	while(a) *top++=a%10,a/=10;
	if(top>s)
		do putchar('0'+*--top); while(top>s);
	else
		putchar('0');
	putchar('\n');
}
int n,q,m,base;
struct query{
	int l,r,ans;
} s[Q],*ord[Q];
inline bool cmp(const query *a,const query *b){
	return a->r<b->r;
}
int a[N],t[T];
int main(){
	n=getint(); q=getint();
	for(int i=1;i<=n;i++) if(m<(a[i]=getint())) m=a[i];
	m++;
	for(base=1;base<=m;base<<=1);
	for(int i=0;i<q;i++){
		s[i].l=getint();
		s[i].r=getint();
		ord[i]=s+i;
	}
	sort(ord,ord+q,cmp);
	for(int i=0,j=0;i<q;i++){
		query *cur=ord[i];
		while(j<cur->r){
			j++;
			int x=base+a[j];
			t[x]=j;
			while(x>>=1) t[x]=min(t[x<<1],t[x<<1|1]);
		}
		int x=1;
		while(x<base)
			if(t[x<<1]<cur->l)
				x=x<<1;
			else
				x=x<<1|1;
		cur->ans=x-base;
	}
	for(int i=0;i<q;i++) println(s[i].ans);
}
