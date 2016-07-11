#include <cstdio>
#include <algorithm>
int N,mid,s[1001],l[1001],r[1001];
int main(){
	scanf("%u",&N);
	for(int i=0;i<N;i++) scanf("%d",s+i);
	std::sort(s,s+N);
	for(mid=0;mid<N&&s[mid]<0;mid++);
	for(int i=N;i>mid;i--) s[i]=s[i-1];
	s[mid]=0;
	for(int i=mid;i>=0;i--)
		for(int j=mid;j<=N;j++){
			if(i==mid&&j==mid){ l[j]=r[i]=0; continue; }
			l[j]=i<mid?l[j]+(N-j+i+1)*(s[i+1]-s[i]):1000000000;
			r[i]=j>mid?r[i]+(N-j+i+1)*(s[j]-s[j-1]):1000000000;
			if(l[j]+(N-j+i)*(s[j]-s[i])<r[i]) r[i]=l[j]+(N-j+i)*(s[j]-s[i]);
			if(r[i]+(N-j+i)*(s[j]-s[i])<l[j]) l[j]=r[i]+(N-j+i)*(s[j]-s[i]);
		}
	printf("%u\n",std::min(l[N],r[0]));
}
