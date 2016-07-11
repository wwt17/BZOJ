/*
第一次写的是shi，复杂度不对的O( ( 10 C 5 )^3 log n )
正解：O( ( 9 C 4 )^3 log n )
强制最高位为1，把最高位转移到后面去 
*/
#include <cstdio>
#include <algorithm>
using namespace std;
const int S=128,mo=30031;
int n,k,p,A,O,s,st[S],opt[2][S][S],ans[2][S];
int main(){
	scanf("%d%d%d",&n,&k,&p);
	for(int i=0;i<1<<p;i++){
		if(!(i>>(p-1)&1)) continue;
		int cnt=0;
		for(int j=0;j<p;j++) cnt+=i>>j&1;
		if(cnt!=k) continue;
		st[s++]=i;
	}
	for(int i=0;i<s;i++)
		for(int j=0;j<s;j++){
			int x=(st[i]<<1)^(1<<p)^st[j];
			if(x&&(x&-x)==x) opt[O][i][j]=1;
		}
	ans[A][s-1]=1;
	for(n-=k;n;n>>=1){
		if(n&1){
			for(int j=0;j<s;j++){
				ans[!A][j]=0;
				for(int i=0;i<s;i++)
					(ans[!A][j]+=ans[A][i]*opt[O][i][j])%=mo;
			}
			A^=1;
		}
		for(int i=0;i<s;i++)
			for(int j=0;j<s;j++){
				opt[!O][i][j]=0;
				for(int k=0;k<s;k++)
					(opt[!O][i][j]+=opt[O][i][k]*opt[O][k][j])%=mo;
			}
		O^=1;
	}
	printf("%d\n",ans[A][s-1]);
}
