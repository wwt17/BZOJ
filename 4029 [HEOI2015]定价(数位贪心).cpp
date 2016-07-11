#include <cstdio>
#include <algorithm>
using namespace std;

typedef pair<int,int> data;

data ans;

int len(int val){
	int ans=0;
	for(;val;val/=10) ans++;
	return ans;
}

data work(int val,int w){
	int tmp=val;
	for(;tmp%10==0;tmp/=10);
	data ans;
	if(tmp%10==5)
		ans=data(2*len(tmp)-1,val*w);
	else
		ans=data(2*len(tmp),val*w);
	if(w>1)
		ans=min(ans,data(2*(len(val)+1)-1,(val*10+5)*(w/10)));
	return ans;
}

int main(){
	int T; scanf("%d",&T);
	while(T--){
		int l,r; scanf("%d%d",&l,&r); l--,r++;
		ans=data(100,0);
		int w=1;
		for(;l/10!=r/10;l/=10,r/=10,w*=10){
			for(int x=l%10+1;x<=9;x++)
				ans=min(ans,work(l/10*10+x,w));
			for(int x=r%10-1;x>=0;x--)
				ans=min(ans,work(r/10*10+x,w));
		}
		for(int x=l%10+1;x<=r%10-1;x++)
			ans=min(ans,work(l/10*10+x,w));
		printf("%d\n",ans.second);
	}
}
