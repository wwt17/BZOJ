#include <cstdio>
#include <algorithm>
#define SIZE 100001
#define INF 0x7FFFFFFF 
inline void maxi(int &a,const int b){if(a<b)a=b;}
inline void read(int &a){
	char c;for (c=getchar();c<'0'||'9'<c;c=getchar()); a=c-'0';
	for (c=getchar();'0'<=c&&c<='9';c=getchar()) a=a*10+(c-'0');
}
inline void write(int a){
	if (a>9) write(a/10); putchar('0'+a%10);
}
#define writeln(a) (write(a),putchar('\n'))

int N,i,j,X[SIZE],t[SIZE],B,a[SIZE],ans[SIZE],s[SIZE];
inline int find(int k){
	int x=0;
	for(int b=B;b;b>>=1)
		if((x|b)<=N&&k>t[x|b]) k-=t[x|=b];
	return x+1;
}
inline void dec(int x){
	for(;x<=N;x+=x&-x) --t[x];
}
int main(){
	read(N);
	for(B=1;B<=N;B<<=1); B>>=1;
	for(i=1;i<=N;++i) read(X[i]);
	for(i=1;i<=N;++i){
		++t[i];
		if(i+(i&-i)<=N) t[i+(i&-i)]+=t[i];
	}
	for(i=N;i;--i){
		j=find(X[i]+1);
		a[j]=i;
		dec(j);
	}
	s[j=1]=INF;
	for(i=1;i<=N;++i)
		if(j==(ans[a[i]]=&(*std::lower_bound(s+1,s+j,a[i])=a[i])-s))
			s[++j]=INF;
	int Ans=0;
	for(i=1;i<=N;++i){
		maxi(Ans,ans[i]);
		writeln(Ans);
	}
}
