#include <iostream>
#include <algorithm>
using namespace std;
const int K=100,B=32;
int k,a[K],base[B];
bool add(int x){
	for(int i=B-1;i>=0;i--) if(x&1<<i)
		if(base[i]) x^=base[i];
		else return base[i]=x,1;
	return 0;
}
int main(){
	cin>>k;
	for(int i=0;i<k;i++) cin>>a[i];
	sort(a,a+k);
	long long ans=0;
	while(k--){
		if(!add(a[k]))
			ans+=a[k];
	}
	cout<<ans<<endl;
}
