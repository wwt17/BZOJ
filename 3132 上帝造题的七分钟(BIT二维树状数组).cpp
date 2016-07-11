#include <cstdio>
#include <cstdlib>
#define Pln putchar('\n')
#define N 2049
#define M 2049
int n,m;
typedef int data;
typedef data array2[N][M];
array2 a,b,c,d;
inline int lowbit(const int x){return x&-x;}

void add(array2 a,int x,int Y,const data delta){
	int y;
	for (;x<=n;x+=lowbit(x))
		for (y=Y;y<=m;y+=lowbit(y))
			a[x][y]+=delta;
}
void add(int x,int y,const data delta){
	add(a,x,y,delta);
	add(b,x,y,y*delta);
	add(c,x,y,x*delta);
	add(d,x,y,x*y*delta);
}
inline void add(const int x1,const int y1,const int x2,const int y2,const data delta){
	add(x1,y1,delta);
	add(x1,y2+1,-delta);
	add(x2+1,y1,-delta);
	add(x2+1,y2+1,delta);
}

data query(array2 a,int x,const int Y){
	data ret=0; int y;
	for (;x;x-=lowbit(x))
		for (y=Y;y;y-=lowbit(y))
			ret+=a[x][y];
	return ret;
}
data query(const int x,const int y){
	return
		 (x+1)*(y+1)*query(a,x,y)
		-(x+1)*query(b,x,y)
		-(y+1)*query(c,x,y)
		+query(d,x,y);
}
inline data query(const int x1,const int y1,const int x2,const int y2){
	return
		 query(x2,y2)
		-query(x1-1,y2)
		-query(x2,y1-1)
		+query(x1-1,y1-1);
}

inline void read(int &a){
	char c;bool f=false;a=0;
	for (c=getchar();(c<'0'||'9'<c)&&c!='-';c=getchar());
	if (c=='-') f=true; else a=a*10+(c-'0');
	for (c=getchar();'0'<=c&&c<='9';c=getchar()) a=a*10+(c-'0');
	if (f) a=-a;
}

int x1,y1,x2,y2; data delta;
inline void readxy(){
	read(x1),read(y1),read(x2),read(y2);
	int tmp;
	if (x1>x2) tmp=x1,x1=x2,x2=tmp;
	if (y1>y2) tmp=y1,y1=y2,y2=tmp;
}

int main(){
	read(n);read(m);
	for(;;) switch(getchar()){
		case 'L':readxy(),read(delta);
			add(x1,y1,x2,y2,delta);
			break;
		case 'k':readxy();
			printf("%d\n",query(x1,y1,x2,y2));
			break;
		case EOF:goto end;
	}
	end:;
}
