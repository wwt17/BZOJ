#include <cstdio>
#include <cstdlib>
#include <algorithm>
using namespace std;
const int N=100005;
int n,q,L,R,D,x[N],y[N];
#define calc(i,j) (abs(x[i]-x[j])+abs(y[i]-y[j]))
#define calc2(i) (calc(i-1,i+1)-calc(i-1,i)-calc(i,i+1))
struct data{
	int s,m;
} t[N*4];
void modify(int cur,int beg,int end){
	if(end-beg==1){
		t[cur].s=D;
		return;
	}
	int mid=beg+end>>1;
	if(L<=mid)
		modify(cur<<1,beg,mid);
	else
		modify(cur<<1|1,mid,end);
	t[cur].s=t[cur<<1].s+t[cur<<1|1].s;
}
void modify2(int cur,int beg,int end){
	if(end-beg==1){
		t[cur].m=D;
		return;
	}
	int mid=beg+end>>1;
	if(L<=mid)
		modify2(cur<<1,beg,mid);
	else
		modify2(cur<<1|1,mid,end);
	t[cur].m=min(t[cur<<1].m,t[cur<<1|1].m);
}
int query(int cur,int beg,int end){
	if(R<=beg||L>=end) return 0;
	if(L<=beg&&R>=end) return t[cur].s;
	int mid=beg+end>>1;
	return query(cur<<1,beg,mid)+query(cur<<1|1,mid,end);
}
int query2(int cur,int beg,int end){
	if(R<=beg||L>=end) return 0;
	if(L<=beg&&R>=end) return t[cur].m;
	int mid=beg+end>>1;
	return min(query2(cur<<1,beg,mid),query2(cur<<1|1,mid,end));
}
int main(){
	scanf("%d%d",&n,&q);
	for(int i=1;i<=n;i++){
		scanf("%d%d",&x[i],&y[i]);
		L=i;
		D=calc(i,i-1);
		modify(1,0,n);
	}
	for(int i=1;i<=n;i++){
		L=i,D=calc2(i);
		modify2(1,0,n);
	}
	while(q--){
		char c=getchar();
		int i,j;
		if(c=='U'){
			scanf("%d",&i);
			scanf("%d%d",&x[i],&y[i]);
			L=i,D=calc(i,i-1),modify(1,0,n);
			if(i+1<=n)
				L=i+1,D=calc(i,i+1),modify(1,0,n);
			if(i-1>0)
				L=i-1,D=calc2(i-1),modify2(1,0,n);
			L=i,D=calc2(i),modify2(1,0,n);
			if(i+1<=n)
				L=i+1,D=calc2(i+1),modify2(1,0,n);
		}
		else
		if(c=='Q'){
			scanf("%d%d",&i,&j);
			L=i,R=j;
			int ans=query(1,0,n);
			R--;
			if(L<R) ans+=min(0,query2(1,0,n));
			printf("%d\n",ans);
		}
		else
			q++;
	}
}
