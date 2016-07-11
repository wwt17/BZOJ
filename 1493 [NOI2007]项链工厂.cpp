#include <cstdio>
#include <cstdlib>
#include <cstring>
#define SizeT 2024300
typedef int color;
int N,c,Q,Base,R=0;bool flipped=false;
struct data{
	color cl,cr,f;int sl,sr,len;
	data():cl(0),sl(0),sr(0),cr(0),f(0),len(0){}
	void paint(color c){
		cl=cr=c;sl=sr=len;f=1;
	}
} t[SizeT];
inline int loca(int i){
	--i;
	if (flipped) i=-i;i=(i-R)%N; if (i<0) i+=N; if (i>N) i-=N;
	++i;
	return i;
}
inline data merge(const data &a,const data &b){
	if (!b.len) return a;
	if (!a.len) return b;
	data c;
	c.cl=a.cl;c.sl=a.sl;
	c.cr=b.cr;c.sr=b.sr;
	c.f=a.f+b.f;
	c.len=a.len+b.len;
	if (a.cr==b.cl){
		c.f--;
		if (c.sl==a.len&&c.sr==b.len)
			c.sl=c.sr=c.len;
	}
	return c;
}
inline void updata(int i){
	t[i]=merge(t[i<<1],t[(i<<1)+1]);
}
inline void downdata(int i){
	if (t[i].f==1)
		t[i<<1].paint(t[i].cl),
		t[(i<<1)+1].paint(t[i].cr);
}
inline void correct(int i){
	if (i==1) return;
	correct(i>>1);
	downdata(i>>1);
}
inline void replace(int i,color c){
	correct(i);
	t[i].cl=t[i].cr=c;
	for (i>>=1;i;i>>=1) updata(i);
}
inline void swap(int i,int j){
	correct(i+=Base);
	correct(j+=Base);
	color c1=t[i].cl,c2=t[j].cl;
	replace(i,c2);
	replace(j,c1);
}
inline void paint(int i,int j,const color c){
	if (i>j) { paint(i,N,c);paint(1,j,c); return; }
	for (correct(i+=Base-1),correct(j+=Base+1);i^j^1;updata(i>>=1),updata(j>>=1)){
		if (!(i&1)) t[i^1].paint(c);
		if   (j&1)  t[j^1].paint(c);
	}
	for (;i;updata(i>>=1));
}
inline data copy(int i,int j){
	data L,R;
	for (correct(i+=Base-1),correct(j+=Base+1);i^j^1;i>>=1,j>>=1){
		if (!(i&1)) L=merge(L,t[i^1]);
		if   (j&1)  R=merge(t[j^1],R);
	}
	return merge(L,R);
}
inline color count(int i,int j){
	return ((i<=j)?copy(i,j):merge(copy(i,N),copy(1,j))).f;
}
inline color count(){
	data tmp=copy(1,N);
	return tmp.f-(tmp.f>1&&tmp.cr==tmp.cl);
}
inline void read(int &a){
	char c;bool f=false;a=0;
	for (c=getchar();(c<'0'||'9'<c)&&c!='-';c=getchar());
	if (c=='-') f=true; else a=a*10+(c-'0');
	for (c=getchar();'0'<=c&&c<='9';c=getchar()) a=a*10+(c-'0');
	if (f) a=-a;
}
inline void write(int a){
	if (a<0) {putchar('-');a=-a;}
	if (a>9) write(a/10); putchar('0'+a%10);
}
inline void writeln(int a){
	write(a); putchar('\n');
}
int main(){
	read(N),read(c);
	for (Base=1;Base<N;Base<<=1);Base--;
	int i,j,x;
	for (i=Base+1;i<=Base+N;++i)
		read(x),
		t[i].cl=t[i].cr=x,
		t[i].sl=t[i].sr=t[i].f=t[i].len=1;
	for (i=Base;i;--i) updata(i);
	for (read(Q);Q;--Q)
		switch(getchar()){
			case 'R':read(i);
				flipped?R-=i:R+=i;break;
			case 'F':
				flipped^=1;getchar();break;
			case 'S':read(i),read(j);
				swap(loca(i),loca(j));break;
			case 'P':read(i),read(j),read(x);flipped?i^=j,j^=i,i^=j:0;
				paint(loca(i),loca(j),x);break;
			case 'C':if (getchar()!='S')
				writeln(count());
			else{read(i),read(j);flipped?i^=j,j^=i,i^=j:0;
				writeln(count(loca(i),loca(j)));}
		}
}
