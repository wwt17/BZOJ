#include <stdio.h>
#include <string.h>
#define P 5000011
inline unsigned getint(){
	char c; while(c=getchar(),c<'0'||'9'<c); unsigned a=c-'0';
	while(c=getchar(),'0'<=c&&c<='9') a=a*10+c-'0'; return a;
}
#define read(a) a=getint()
#define ll long long
typedef int data[32]; data s[100001];
int N,i,K,k,a,h[P],b[32],Ans; ll sum;
int equal(const data a,const data b){
	int k; for(k=1;k<K;++k) if(a[k]!=b[k]) return 0;
	return 1;
}
int main(){
	read(N),read(K); ++N;
	for(b[0]=1,k=1;k<K;++k)
		sum+=b[k]=(ll)b[k-1]*(N<<1)%P;
	b[0]=0;
	sum%=P; sum*=N; sum%=P;
	h[sum]=1;
	for(i=1;i<N;++i){
		read(a);
		memcpy(s[i],s[i-1],K<<2);
		for(k=0;k<K&&a;++k,a>>=1) if(a&1)
			sum+=b[k]-b[k+1],++s[i][k],--s[i][k+1];
		sum%=P;
		if(sum<0) sum+=P;
		int su=sum;
		while(h[su]&&!equal(s[h[su]-1],s[i])) if(++su==P) sum=0;
		if(h[su]){if(Ans<i-h[su]+1) Ans=i-h[su]+1;}
		else h[su]=i+1;
	}
	printf("%d\n",Ans);
	return 0;
}
