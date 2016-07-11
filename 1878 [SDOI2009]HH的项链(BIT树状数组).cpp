#include <cstdio>
#include <algorithm>
using namespace std;
typedef unsigned short data;
struct interval{
	data L,R,Ans;
	inline void read(){
		scanf("%hu%hu",&L,&R);
	}
} s[200000],*t[200000];
inline bool cmp(const interval* a,const interval* b){
	return a->R < b->R;
}
data T[50001],last[1000001],N,i;
int M,j,a[50001];
inline void Add(int l,int r){
	for(l++;l<=N;l+=l&-l) T[l]++;
	for(r++;r<=N;r+=r&-r) T[r]--;
}
inline data Query(data x){
	data ret=0;
	for(;x;x-=x&-x) ret+=T[x];
	return ret;
}
int main(){
	scanf("%hu",&N);
	for(i=1;i<=N;i++) scanf("%u",a+i);
	scanf("%u",&M);
	for(j=0;j<M;j++) s[j].read(),t[j]=s+j;
	sort(t,t+M,cmp);
	for(i=0,j=0;j<M;j++){
		while(i<t[j]->R){
			i++;
			Add(last[a[i]],i);
			last[a[i]]=i;
		}
		t[j]->Ans=Query(t[j]->L);
	}
	for(j=0;j<M;j++) printf("%hu\n",s[j].Ans);
}
