#include <cstdio>
#define sizeT 262144
inline void read(int &a){
	char c;
	for (c=getchar();c<'0'||'9'<c;c=getchar()); a=c-'0';
	for (c=getchar();'0'<=c&&c<='9';c=getchar()) a=a*10+(c-'0');
}
inline void read(long long &a){
	char c;
	for (c=getchar();c<'0'||'9'<c;c=getchar()); a=c-'0';
	for (c=getchar();'0'<=c&&c<='9';c=getchar()) a=a*10+(c-'0');
}
#define read2(a,b) (read(a),read(b))
#define read3(a,b,c) (read2(a,b),read(c))
inline void write(int a){
	if (a>9) write(a/10); putchar('0'+a%10);
}
#define writeln(a) (write(a),putchar('\n'))

int P,N,Base,s,t,c;
struct data{
	long long mult,plus,sum;
	data():mult(1){}
} T[sizeT];
int len;
#define add(a,b) (((a)+(b))%P)
#define mul(a,b) (((a)*(b))%P)
#define addi(a,b) ((a)=add(a,b))
#define muli(a,b) ((a)=mul(a,b))
void printT();
inline void sumi(long long &c,const data &x){
	c=(c*x.mult+mul(x.plus,len))%P;
}
inline void update(int i){
	T[i].sum=add(T[i<<1].sum,T[i<<1^1].sum);
}
inline void downdata(const int i){
	muli(T[i<<1].mult,T[i].mult); muli(T[i<<1].plus,T[i].mult); addi(T[i<<1].plus,T[i].plus); sumi(T[i<<1].sum,T[i]);
	muli(T[i<<1^1].mult,T[i].mult); muli(T[i<<1^1].plus,T[i].mult); addi(T[i<<1^1].plus,T[i].plus); sumi(T[i<<1^1].sum,T[i]);
	T[i].mult=1; T[i].plus=0;
}
inline bool ok(int i){ return Base<i&&i<=Base+N; }
void correct(int i){
	if (i>>=1){ len<<=1,correct(i);len>>=1,downdata(i); }
}
long long suml,sumr;
inline void multi(data &x){
	muli(x.mult,c);
	muli(x.plus,c);
	muli(x.sum,c);
}
void Mult(){
	suml=0,sumr=0;
	for (len=1,correct(ok(s+=Base-1)?s:0),len=1,correct(ok(t+=Base+1)?t:0);s^t^1;s>>=1,addi(T[s].sum,suml),t>>=1,addi(T[t].sum,sumr)){
		if (~s&1) addi(suml,T[s^1].sum*(c-1)),multi(T[s^1]);
		if ( t&1) addi(sumr,T[t^1].sum*(c-1)),multi(T[t^1]);
	}
	for (addi(suml,sumr);s>>=1;addi(T[s].sum,suml));
}
inline void plusi(data &x){
	addi(x.plus,c);
	addi(x.sum,c*len);
}
void Plus(){
	suml=0,sumr=0;
	for (len=1,correct(ok(s+=Base-1)?s:0),len=1,correct(ok(t+=Base+1)?t:0),len=1;s^t^1;len<<=1,s>>=1,addi(T[s].sum,suml),t>>=1,addi(T[t].sum,sumr)){
		if (~s&1) addi(suml,c*len),plusi(T[s^1]);
		if ( t&1) addi(sumr,c*len),plusi(T[t^1]);
	}
	for (addi(suml,sumr);s>>=1;addi(T[s].sum,suml));
}
int Sum(){
	suml=0,sumr=0;
	for (len=1,correct(ok(s+=Base-1)?s:0),len=1,correct(ok(t+=Base+1)?t:0),len=1;s^t^1;len<<=1,s>>=1,t>>=1){
		if (~s&1) addi(suml,T[s^1].sum);
		if ( t&1) addi(sumr,T[t^1].sum);
	}
	return add(add(suml,sumr),P);
}

int main(){
	read2(N,P);
	for (Base=1;Base<N;Base<<=1); Base--;
	int i;
	for (i=1;i<=N;++i) read(T[Base+i].sum),T[Base+i].sum%=P;
	for (i=Base;i;--i) update(i);
	int M;read(M);while (M--)
		switch (getchar()){
			case '1':read3(s,t,c);Mult();break;
			case '2':read3(s,t,c);Plus();break;
			case '3':read2(s,t);writeln(Sum());
		}
}
