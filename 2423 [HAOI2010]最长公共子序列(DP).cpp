#include <cstdio>
#include <algorithm>
const int P=100000000;
char X[5005];
typedef std::pair<int,int> pii;
#define len first
#define sum second
pii f[5001];
inline void renew(pii &a,pii b){
	if(a.len<b.len) a=b; else
	if(a.len==b.len) if((a.sum+=b.sum)>=P) a.sum-=P;
}
int main(){
	scanf("%s\n",X+1);
	char y;
	while((y=getchar())!='.'){
		pii cnt(0,1);
		for(int i=1;X[i]!='.';i++){
			pii tmp=f[i];
			if(X[i]==y) renew(f[i],pii(cnt.len+1,cnt.sum));
			renew(cnt,tmp);
		}
	}
	pii ans(0,0);
	for(int i=1;X[i]!='.';i++) renew(ans,f[i]);
	printf("%u\n%u\n",ans.len,ans.sum);
}
