#include <cstdio>
#include <cstdlib>
#include <algorithm>
inline void read(int &a){
	char c;for (c=getchar();c<'0'||'9'<c;c=getchar()); a=c-'0';
	for (c=getchar();'0'<=c&&c<='9';c=getchar()) a=a*10+(c-'0');
}
#define read2(a,b) read(a),read(b)
#define read3(a,b,c) read(a),read(b),read(c)
struct node{
	node* belong;
	void renew(){
		if(belong==this) return;
		belong->renew();
		belong=belong->belong;
	}
} V[501];
struct edge{
	node *x,*y; short v;
	friend bool operator < (const edge &a,const edge &b){
		return a.v<b.v;
	}
	void link(){
		x->renew();y->renew();
		y->belong->belong=x->belong;
	}
} E[5001];
short gcd(const short a,const short b){
	if(!b) return a;
	return gcd(b,a%b);
}
struct frac{
	short a,b;
	frac():a(0),b(1){}
	frac(short _a):a(_a),b(1){}
	void operator = (const frac &tmp){
		a=tmp.a; b=tmp.b;
	}
	inline double val(){return (double)a/b;}
	friend bool operator < (frac &a,frac &b){
		return a.val()<b.val();
	}
	inline void about_sub(){
		short g=gcd(a,b);
		a/=g,b/=g;
	}
	void print(){
		about_sub();
		printf("%d",a);
		if(b!=1) printf("/%d",b);
		putchar('\n');
	}
} ans(0x7fff),now;
int main(){
	int N,M,i,j,x,y,v,s,t;
	read2(N,M);
	for(i=1;i<=M;++i){
		read3(x,y,v);
		E[i]=(edge){V+x,V+y,v};
	}
	read2(s,t);
	std::sort(E+1,E+M+1);
	for(i=1;i<=M;++i){
		for(node* v=V+1;v<=V+N;++v) v->belong=v;
		now.b=E[i].v;
		for(j=i;j<=M;++j){
			E[j].link();
			V[s].renew(),V[t].renew();
			now.a=E[j].v;
			if(V[s].belong==V[t].belong){
				if(now<ans)
					ans=now;
				break;
			}
		}
	}
	if(ans.val()>30000) puts("IMPOSSIBLE");
	else ans.print();
	return 0;
}
