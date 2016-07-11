#include <cstdio>
#include <algorithm>
#define N 200010
char s[N],*end=s; int rad[N],t[N];
inline bool cmp(const int a,const int b){ return rad[a]<b; }
int main(){
	*end++='@';
	while(*end++='#',(*end=getchar())!='\n'&&*end!=EOF) end++;
	int i,j,k,Ans=0;
	for(i=1;s+i<end;i+=k){
		while(s[i-rad[i]-1]==s[i+rad[i]+1]) rad[i]++;
		for(k=1;k<=rad[i]&&rad[i]-k!=rad[i-k];k++)
			rad[i+k]=std::min(rad[i]-k,rad[i-k]);
		rad[i+k]=std::max(rad[i]-k,0);
	}
	for(i=1,j=2;s+i<end;i++)
		for(;s+j<end&&j<=i+rad[i];j++)
			if(s[j]=='#') t[j]=j-i;
	for(i=end-s-1,j=end-s-2;i;i--)
		for(;j&&j>=i-rad[i];j--)
			t[j]+=i-j;
	for(i=1;s+i<end;i++) if(Ans<t[i]) Ans=t[i];
	printf("%u\n",Ans);
}
