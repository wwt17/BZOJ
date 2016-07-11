#include <stdio.h>
#include <ctype.h>
#define maxn 100001
typedef long long data;
int N,a[maxn];
data b[maxn],c[maxn];
inline int lowbit(const int x){return x&-x;}
void update(data* a,int x,const data w){
	for (;x<=N;x+=lowbit(x)) a[x]+=w;
}
data query(data* a,int x){
	data ret=0;
	for (;x;x-=lowbit(x)) ret+=a[x];
	return ret;
}
inline int getint(){
	char c;for (c=getchar();!isdigit(c);c=getchar());
	int a=c-'0';for (c=getchar();isdigit(c);c=getchar()) a=a*10+(c-'0');
	return a;
}
inline void write(data a){
	if (a>9) write(a/10); putchar('0'+a%10);
}
#define writeln(a) (write(a),putchar('\n'))
int main(){
	int i,M;
	scanf("%d%d",&N,&M);
	for (i=1;i<=N;++i) a[i]=b[i]=getint(),c[i]=b[i]*i;
	int ii;
	for (i=1;i<=N;++i) if ((ii=i+lowbit(i))<=N) b[ii]+=b[i],c[ii]+=c[i];
	data x; char ch;
	while (M--){
		while (!isalpha(ch=getchar()));
		if (ch=='M')
		{i=getint();a[i]+=x=getint()-a[i];update(b,i,x);update(c,i,x*i);}
		else {i=getint();writeln(query(b,i)*(i+1)-query(c,i));}
	}
	return 0;
}
