#include <cstdio>
#include <algorithm>
#define sizeT 115536
int N,Q,base,i,l,r,max[sizeT],min[sizeT];
inline int maxi(int &a,const int b){if(a<b)a=b;}
inline int mini(int &a,const int b){if(a>b)a=b;}
inline void read(int &a){
	char c;for (c=getchar();c<'0'||'9'<c;c=getchar()); a=c-'0';
	for (c=getchar();'0'<=c&&c<='9';c=getchar()) a=a*10+(c-'0');
}
#define read2(a,b) read(a),read(b)
inline void write(int a){
	if (a>9) write(a/10); putchar('0'+a%10);
}
#define writeln(a) write(a),putchar('\n')
int main(){
	read2(N,Q);
	for(base=1;base<N;base<<=1); --base;
	l=base+1,r=base+N;
	for(i=l;i<=r;++i) read(max[i]),min[i]=max[i];
	for(l>>=1,r>>=1;l&&r;l>>=1,r>>=1)
		for(i=r;i>=l;--i)
			max[i]=std::max(max[i<<1],max[i<<1^1]),
			min[i]=std::min(min[i<<1],min[i<<1^1]);
	int maxs,mins;
	while(Q--){
		read2(l,r);
		maxs=0;mins=0x7fffffff;
		for(l+=base-1,r+=base+1;l^r^1;l>>=1,r>>=1){
			if(!(l&1)) maxi(maxs,max[l^1]),mini(mins,min[l^1]);
			if(  r&1 ) maxi(maxs,max[r^1]),mini(mins,min[r^1]);
		}
		writeln(maxs-mins);
	}
}
