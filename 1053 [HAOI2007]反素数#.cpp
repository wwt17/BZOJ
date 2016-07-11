#include <cstdio>
#include <cstdlib>
template<class T>
inline bool mini(T &a,T b){
	return a>b?(a=b,true):false;
}
#define maxN 65
#define ll unsigned long long
const int prime[10]={2,3,5,7,11,13,17,19,23,29};
ll power[10][maxN];
ll DFS(int sum,int i){
	if(sum==1) return 1;
	ll Ret=0x7FFFFFFFFFFFFFFFLL;
	for(int j=sum;j>1;--j)
		if(!(sum%j))
		if(!mini(Ret,power[i][j-1]*DFS(sum/j,i+1)))
			break;
	return Ret;
}
int main(){
	for(int i=0;i<10;i++){
		power[i][0]=1;
		for(int j=1;j<maxN;j++)
			power[i][j]=power[i][j-1]*prime[i];
	}
	/*
	int l=0,r=32,mid;
	while(l<=r){
		mid=(l+r)>>1;
		if(DFS(mid,0)<=N)
			r=mid;
		else
			l=mid+1;
	}
	*/
	freopen("out.txt","w",stdout);
	ll a[maxN],i=0,j;
	for(int N=1;N<maxN;N++){
		a[i]=DFS(N,0);
		printf("N=%u %I64u\n",N,a[i]);
		for(j=i;j&&a[j-1]>a[i];j--);
		a[j]=a[i];
		i=j+1;
	}
	for(j=0;j<i;j++) printf("%I64u,",a[j]);
}
