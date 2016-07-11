#include <cstdio>
#include <cstring>
#define size 100002
#define CH 256
char s[size<<1];
int N,*Rank,SA[size<<1],tmparray[4][size<<1];
inline bool cmp(const int *r,const int a,const int b,const int len)
  { return r[a]==r[b]&&r[a+len]==r[b+len]; }
void DA(char* s,int* SA,const int N,int M,int* &Rank,int* sa,int* sum,int* key1){
	s[N]=0;
  int i,len,p=0,*tmp;
	memset(sum,0,sizeof(*sum)*M);
	for(i=0;i<=N;++i) ++sum[Rank[i]=s[i]];
	for(i=1;i<M;++i) sum[i]+=sum[i-1];
	for(i=N;i>=0;--i) SA[--sum[Rank[i]]]=i;
	for(len=1;len<N&&p<=N;M=p,len<<=1){
    for(p=0,i=N-len;i<=N;++i) sa[p++]=i;
		for(i=1;i<=N;++i) if(SA[i]>=len) sa[p++]=SA[i]-len;
		for(i=0;i<=N;++i) key1[i]=Rank[sa[i]];
		memset(sum,0,sizeof(*sum)*M);
		for(i=0;i<=N;++i) ++sum[key1[i]];
		for(i=1;i<M;++i) sum[i]+=sum[i-1];
		for(i=N;i>=0;--i) SA[--sum[key1[i]]]=sa[i];
		for(tmp=Rank,Rank=sa,sa=tmp,p=1,Rank[SA[0]]=0,i=1;i<=N;++i)
			Rank[SA[i]]=cmp(sa,SA[i-1],SA[i],len)?p-1:p++;
  }
}
int main(){
	fgets(s,size,stdin);
	N=strlen(s)-1;
	memcpy(s+N,s,N);
	DA(s,SA,N<<1,CH,Rank=tmparray[0],tmparray[1],tmparray[2],tmparray[3]);
  for(int i=1;i<=N<<1;++i) if(SA[i]<N) putchar(s[SA[i]+N-1]); putchar('\n');
}
