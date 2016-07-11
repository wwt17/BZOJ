#include <cstdio>
const int W=30,P=10086;
int n,Base[W];
inline bool add(int x){
	for(int j=W-1;j>=0;j--) if(x&1<<j){
		if(Base[j]) x^=Base[j];
		else{
			Base[j]=x;
			return 1;
		}
	}
	return 0;
}
inline int power(int a,int s){
	int ans=1;
	for(;s;s>>=1,a=a*a%P)
		if(s&1) ans=ans*a%P;
	return ans;
}
int main(){
	scanf("%d",&n);
	for(int i=0;i<n;i++){
		static int x; scanf("%d",&x);
		add(x);
	}
	int q;
	while(scanf("%d",&q)!=EOF){
		int ans=0,cnt=0;
		for(int j=W-1;j>=0;j--){
			if(Base[j]){
				cnt++;
				if(q&1<<j){
					ans=ans<<1|1;
				}
				else
					ans=ans<<1;
			}
		}
		printf("%d\n",(ans%P*power(2,n-cnt)+1)%P);
	}
}
