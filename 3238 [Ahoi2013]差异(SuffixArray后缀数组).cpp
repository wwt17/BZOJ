#include <cstdio>
#include <cstring>
const int N=500005,M=27;
char s[N];
int n,*SA,*Rank,Height[N],mem[4][N],sum[M];
void DA(int n,int m,char *s,int *SA,int *&Rank,int *sa,int *key1,int *sum){
	s[n]=0;
	int i,p=0;
	memset(sum,0,sizeof(*sum)*m);
	for(i=0;i<=n;i++) sum[Rank[i]=s[i]]++;
	for(i=1;i<m;i++) sum[i]+=sum[i-1];
	for(i=n;i>=0;i--) SA[--sum[Rank[i]]]=i;
	for(int len=1;len<=n&&p<=n;m=p,len<<=1){
		p=0;
		for(i=n-len;i<=n;i++) sa[p++]=i;
		for(i=1;i<=n;i++) if(SA[i]>=len) sa[p++]=SA[i]-len;
		memset(sum,0,sizeof(*sum)*m);
		for(i=0;i<=n;i++) sum[key1[i]=Rank[sa[i]]]++;
		for(i=1;i<m;i++) sum[i]+=sum[i-1];
		for(i=n;i>=0;i--) SA[--sum[key1[i]]]=sa[i];
		p=1;
		int *rank=sa;
		rank[SA[0]]=0;
		for(i=1;i<=n;i++) rank[SA[i]]=
			Rank[SA[i-1]]==Rank[SA[i]]&&Rank[SA[i-1]+len]==Rank[SA[i]+len]
			?p-1:p++;
		sa=Rank;
		Rank=rank;
	}
}
void getHeight(int n,char *s,int *SA,int *Rank,int *Height){
	for(int i=0,h=0;i<n;Height[Rank[i++]]=h)
		for(h?h--:0;s[SA[Rank[i]-1]+h]==s[i+h];h++);
}
int q[N],*top=q;
int main(){
	scanf("%s",s);
	for(n=0;s[n];n++) s[n]-='a'-1;
	DA(n,M,s,SA=mem[0],Rank=mem[1],mem[2],mem[3],sum);
	getHeight(n,s,SA,Rank,Height);
	for(int i=0;i<n;i++) s[i]+='a'-1;
	for(int i=1;i<=n;i++){
		printf("%d\n",Height[i]);
		puts(s+SA[i]);
	}
	long long ans=0,tot=0;
	*top=1;
	for(int i=1;i<=n;i++){
		while(Height[*top]>Height[i]){
			tot-=(long long)Height[*top]*(*top-*(top-1));
			top--;
		}
		*++top=i;
		ans+=tot+=(long long)Height[i]*(i-*(top-1));
	}
	printf("%I64d\n",(long long)(n-1)*(n+1)*n/2-ans*2);
}
