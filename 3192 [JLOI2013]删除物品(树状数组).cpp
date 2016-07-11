#include <cstdio>
#include <algorithm>
int N1,N2,begin[200050],*p[200050],t[200050],mid,end,i,j; long long ans=0;
inline void read(int &a){
	char c;for (c=getchar();c<'0'||'9'<c;c=getchar()); a=c-'0';
	for (c=getchar();'0'<=c&&c<='9';c=getchar()) a=a*10+(c-'0');
}
#define read2(a,b) (read(a),read(b))
inline int query(int x){
	int ret=0;
	for(;x;x-=x&-x) ret+=t[x];
	return ret;
}
inline void dec(int x){
	for(;x<end;x+=x&-x) --t[x];
}
inline bool cmp(const int* a,const int* b){
	return *a>*b;
}
int main(){
	read2(N1,N2);
	mid=N1+1;
	end=mid+N2+1;
	for(i=mid-1;i;--i){
		read(begin[i]);
		p[i]=begin+i;
	}
	p[mid]=begin+mid;
	for(i=mid+1;i<end;++i){
		read(begin[i]);
		p[i]=begin+i;
	}
	for(i=1;i<end;++i) t[i]=i&-i;
	dec(mid);
	std::sort(p+1,p+end,cmp);
	for(i=1;i<end;++i){
		j=p[i]-begin;
		ans+=j<mid?query(mid-1)-query(j):query(j-1)-query(mid);
		dec(mid=j);
	}
	printf("%I64d\n",ans);
}
