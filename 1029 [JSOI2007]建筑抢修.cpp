#include <cstdio>
#include <algorithm>
#include <queue>
inline void read(int &a){
	char c; while(c=getchar(),c<'0'||'9'<c); a=c-'0';
	while(c=getchar(),'0'<=c&&c<='9') a=a*10+c-'0';
}
#define read2(a,b) read(a),read(b)
struct task{
	int T1,T2;
} t[150001];
inline bool cmp(const task &a,const task &b){
	return a.T2<b.T2;
}
int N,i,tot;
int main(){
	read(N);
	for(i=1;i<=N;++i) read2(t[i].T1,t[i].T2);
	std::sort(t+1,t+N+1,cmp);
	std::priority_queue<int> q;
	for(i=1;i<=N;++i)
		if(tot+t[i].T1<=t[i].T2) q.push(t[i].T1),tot+=t[i].T1; else
		if(t[i].T1<q.top()) tot-=q.top(),q.pop(),q.push(t[i].T1),tot+=t[i].T1;
	printf("%u\n",q.size());
}
