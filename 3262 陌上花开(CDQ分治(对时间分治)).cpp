#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;
const int N=100001,K=200001;
int n,k,tot,cnt[N],tree[K];
struct point{
	int x,y,z,v,s;
	void read(){
		scanf("%d%d%d",&x,&y,&z);
	}
	bool operator < (point B)const{
		return x<B.x||x==B.x&&(y<B.y||y==B.y&&z<B.z);
	}
	bool operator != (point &B)const{
		return x!=B.x||y!=B.y||z!=B.z;
	}
	bool operator == (point &B)const{
		return x==B.x&&y==B.y&&z==B.z;
	}
} s[N],tmp[N];
void work(point *begin,point *end){
	if(end-begin==1) return;
	point *mid=begin+(end-begin)/2;
	work(begin,mid);
	work(mid,end);
	#define deall() { *t=*l++; for(int x=t->z;x<k;x+=x&-x) tree[x]+=t->s; t++; }
	#define dealr() { *t=*r++; for(int x=t->z;x;x-=x&-x) t->v+=tree[x]; t++; }
	point *l=begin,*r=mid,*t=tmp;
	for(;l<mid&&r<end;)
		if(l->y<=r->y)
			deall()
		else
			dealr()
	while(l<mid) deall();
	while(r<end) dealr();
	for(l=begin;l<mid;l++) for(int x=l->z;x<=k;x+=x&-x) tree[x]-=l->s;
	memcpy(begin,tmp,(end-begin)*sizeof(point));
}
int main(){
	scanf("%d%d",&n,&k); k++;
	for(int i=0;i<n;i++) s[i].read();
	sort(s,s+n);
	for(int i=0;i<n;i++){
		if(!i||s[i]!=s[i-1])
			s[tot++]=s[i];
		s[tot-1].s++;
	}
	for(int i=0;i<tot;i++) s[i].v=s[i].s-1;
	work(s,s+tot);
	/*
	for(int i=0,j;i<n;i=j){
		for(j=i+1;j<n&&s[j]==s[j-1];j++);
		for(int k=i;k<j;k++) s[j].v=j-i-1;
	}
	work(s,s+n);
	*/
	for(int i=0;i<tot;i++) cnt[s[i].v]+=s[i].s;
	for(int i=0;i<n;i++) printf("%d\n",cnt[i]);
	scanf("\n");
}
