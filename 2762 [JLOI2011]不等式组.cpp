#include <cstdio>
#include <cmath>
inline int max(const int a,const int b){ return a>b?a:b; }
inline int min(const int a,const int b){ return a<b?a:b; }
#define Size 4097200
#define Base 3097152
#define SizeN 100010
#define Lbnd -1000000
#define Ubnd  1000000
inline void read(int &a){
	char c;bool f=false;a=0;
	for (c=getchar();(c<'0'||'9'<c)&&c!='-';c=getchar());
	if (c=='-') f=true; else a=a*10+(c-'0');
	for (c=getchar();'0'<=c&&c<='9';c=getchar()) a=a*10+(c-'0');
	if (f) a=-a;
}
int t[Size],l[SizeN],r[SizeN],s=0; bool exist[SizeN];
inline void add(int l,int r,int sum){
	for (l+=Base-1,r+=Base+1;l^r^1;l>>=1,r>>=1){
		if (~l&1) t[l^1]+=sum;
		if  (r&1) t[r^1]+=sum;
	}
}
inline int query(int k){
	int ret=0;
	for (k+=Base;k;k>>=1) ret+=t[k];
	return ret;
}
int main(){
	int N,i,a,b,c,k,d; scanf("%d\n",&N);
	for (i=1;i<=N;++i) switch(getchar()){
		case 'A':read(a),read(b),read(c);
			exist[++s]=true;
			d=min(max(Lbnd,(int)floor((double)(c-b)/a)),Ubnd);
			if (!(a*d+b>c))
				if (!(a*(++d)+b>c)) d-=2;
			if (a<0) l[s]=Lbnd,r[s]=d; else
			if (a>0) l[s]=d,r[s]=Ubnd; else
			if (b<c) l[s]=1,r[s]=0; else l[s]=Lbnd,r[s]=Ubnd;
			add(l[s],r[s],1);
		break;
		case 'D':read(k);
			if (exist[k]){
				add(l[k],r[k],-1);
				exist[k]=false;
			}
		break;
		case 'Q':read(k);
			printf("%d\n",query(k));
	}
}
