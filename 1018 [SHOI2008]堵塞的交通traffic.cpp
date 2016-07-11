#include <cstdio>
#include <cstring>
#define SizeC 100005
#define SizeT 231100
inline int max(const int a,const int b){return a>b?a:b;}
int C,Base,r1,c1,r2,c2;
struct area{
	bool crs[2][2],cet[2]; int st;
	area(){ memset(this,0,sizeof(area)); }
	void print(){
		printf("%d %d\n%d %d\n %d %d\n",
			crs[0][0],crs[0][1],crs[1][0],crs[1][1],cet[0],cet[1]);
	}
} t[SizeT];
bool f[SizeC][2];
inline area merge(const area &a,const area &b){
	area c;
	int mid=b.st,k,i,j;
	c.st=a.st;
	for (k=0;k<2;++k) if (f[mid][k])
		for (i=0;i<2;++i) if (a.crs[i][k])
			for (j=0;j<2;++j) if (b.crs[k][j])
				c.crs[i][j]=true;
	if (c.cet[0]=a.cet[0]||a.crs[0][0]&&f[mid][0]&&b.cet[0]&&f[mid][1]&&a.crs[1][1])
		for (i=0;i<2;++i)
			for (j=0;j<2;++j)
				c.crs[i][j]=c.crs[i][j]||c.crs[!i][j];
	if (c.cet[1]=b.cet[1]||b.crs[0][0]&&f[mid][0]&&a.cet[1]&&f[mid][1]&&b.crs[1][1])
		for (i=0;i<2;++i)
			for (j=0;j<2;++j)
				c.crs[i][j]=c.crs[i][j]||c.crs[i][!j];
	return c;
}
inline void update(int i){
	t[i]=merge(t[i<<1],t[(i<<1)+1]);
}
inline void build(){
	for (Base=1;Base<C;Base<<=1); --Base;
	int i;
	for (i=Base+C;i>Base;--i) t[i].st=i-Base,t[i].crs[0][0]=t[i].crs[1][1]=1;
	for (;i;--i) t[i].st=t[i>>1].st;
}
inline void renew(bool bo){
	int i;
	if (r1==r2) f[i=max(c1,c2)][r1]=bo,i+=Base;
	else i=c1+Base,t[i].crs[0][1]=t[i].crs[1][0]=t[i].cet[0]=t[i].cet[1]=bo;
	for (i>>=1;i;i>>=1)
		update(i);
}
inline area copy(int l,int r){
	if (l==r) return t[Base+l];
	area L=t[l+=Base],R=t[r+=Base];
	for (;l^r^1;l>>=1,r>>=1){
		if (!(l&1)) L=merge(L,t[l^1]);
		if   (r&1)  R=merge(t[r^1],R);
	}
	return merge(L,R);
}
inline bool query(){
	area mid=copy(c1,c2);
	if (mid.crs[r1][r2]) return true;
	int i,j;
	if (mid.cet[0]=mid.cet[0]||f[c1][0]&&f[c1][1]&&copy(1,c1-1).cet[1])
		for (i=0;i<2;++i)
			for (j=0;j<2;++j)
				mid.crs[i][j]=mid.crs[i][j]||mid.crs[!i][j];
	if (mid.cet[1]=mid.cet[1]||f[c2+1][0]&&f[c2+1][1]&&copy(c2+1,C).cet[0])
		for (i=0;i<2;++i)
			for (j=0;j<2;++j)
				mid.crs[i][j]=mid.crs[i][j]||mid.crs[i][!j];
	return mid.crs[r1][r2];
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
inline void read(char &c){
	while (c=getchar(),c<'A'||'Z'<c);
}
inline void skip(int i){while (i--) getchar();}
int main(){
	read(C);build();
	char opt;
	int cnt=0;
	for (;;) switch(read(opt),opt){
		case 'C':read(r1),read(c1),read(r2),read(c2),r1--,r2--;
			renew(0);break;
		case 'O':read(r1),read(c1),read(r2),read(c2),r1--,r2--;
			renew(1);break;
		case 'A':read(r1),read(c1),read(r2),read(c2),r1--,r2--;if (c1>c2) c1^=c2,c2^=c1,c1^=c2,r1^=r2,r2^=r1,r1^=r2;
			putchar(query()?'Y':'N');putchar('\n');break;
		case 'E':goto end;
	}
	end:;
}
