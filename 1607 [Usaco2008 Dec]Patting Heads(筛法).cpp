#include <cstdio>
#define sizeN 100001
#define size 1000001
inline void read(int* a){
	char c; for (c=getchar();c<'0'||'9'<c;c=getchar());*a=c-'0';
	for (c=getchar();'0'<=c&&c<='9';c=getchar()) *a=(*a)*10+(c-'0');
}
inline void write(int a){
	if (a>9) write(a/10); putchar('0'+a%10);
}
#define writeln(a) (write(a),putchar('\n'))
int N,Max,i,j,A[sizeN],cnt[size],ans[size];bool vis[size];
int main(){
	read(&N);
	for (i=1;i<=N;++i){read(&A[i]);cnt[A[i]]++;if(Max<A[i])Max=A[i];}
	for (i=1;i<=N;++i) if (!vis[A[i]]){vis[A[i]]=1;
		ans[A[i]]+=cnt[A[i]]-1;
		for (j=A[i]<<1;j<=Max;j+=A[i]) if (cnt[j])
			ans[j]+=cnt[A[i]];
	}
	for (i=1;i<=N;++i) writeln(ans[A[i]]);
}
