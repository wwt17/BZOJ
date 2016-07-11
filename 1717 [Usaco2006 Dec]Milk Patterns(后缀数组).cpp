#include <cstdio>
#include <cstring>
#include <algorithm>
#include <queue>
#define size 20001
inline void maxi(int &a,const int b){if(a<b)a=b;}
int s[size];
int N,*Rank,Height[size],SA[size],tmparray[4][size];
inline bool cmp(const int a,const int b){ return s[a]<s[b]; }
inline bool Cmp(const int *r,const int a,const int b,const int len)
  { return r[a]==r[b]&&r[a+len]==r[b+len]; }
void DA(int* s,int* SA,const int N,int* &Rank,int* sa,int* sum,int* key1){
	s[N]=0;
  int i,len,p,M,*tmp;
	for(i=0;i<=N;++i) SA[i]=i;
	std::sort(SA,SA+N+1,cmp);
	for(p=1,Rank[SA[0]]=0,i=1;i<=N;++i)
    Rank[SA[i]]=s[SA[i]]==s[SA[i-1]]?p-1:p++;
  M=p;
	for(len=1;len<N&&p<=N;M=p,len<<=1){
    for(p=0,i=N-len;i<=N;++i) sa[p++]=i;
		for(i=1;i<=N;++i) if(SA[i]>=len) sa[p++]=SA[i]-len;
		for(i=0;i<=N;++i) key1[i]=Rank[sa[i]];
		memset(sum,0,sizeof(*sum)*M);
		for(i=0;i<=N;++i) ++sum[key1[i]];
		for(i=1;i<M;++i) sum[i]+=sum[i-1];
		for(i=N;i>=0;--i) SA[--sum[key1[i]]]=sa[i];
		for(tmp=Rank,Rank=sa,sa=tmp,p=1,Rank[SA[0]]=0,i=1;i<=N;++i)
			Rank[SA[i]]=Cmp(sa,SA[i-1],SA[i],len)?p-1:p++;
  }
}
void GetHeight(const int* s,int* Height,const int* SA,const int* Rank,const int N){
  int i,j,k=0;
  for(i=0;i<N;Height[Rank[i++]]=k)
    for(k?--k:0,j=SA[Rank[i]-1];s[i+k]==s[j+k];++k);
}
int main(){
  int N,K,i,Ans=0; scanf("%d%d",&N,&K);
  for(i=0;i<N;++i) scanf("%d",s+i);
	DA(s,SA,N,Rank=tmparray[0],tmparray[1],tmparray[2],tmparray[3]);
  GetHeight(s,Height,SA,Rank,N);
  std::deque<int*> q;
  --K;
  for(i=0;i<=N;++i){
    while(!q.empty()&&*q.back()>Height[i]) q.pop_back();
    q.push_back(Height+i);
    if(Height+(i-K)==q.front()) q.pop_front();
    if(i>K&&!q.empty()) maxi(Ans,*q.front());
  }
  printf("%d\n",Ans);
}
