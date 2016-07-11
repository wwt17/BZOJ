#include <cstdio>
struct node{
	node *belong;
	node():belong(this){}
	void correct(){
		if(belong==this) return;
		belong->correct();
		belong=belong->belong;
	}
	bool link(node* y){
		correct();
		y->correct();
		if(belong==y->belong) return false;
		belong->belong=y->belong;
		return true;
	}
} cow[10000],language[30001];
int n,m,k,l,ans; bool ok,f[30001];
int main(){
	scanf("%u%u",&n,&m);
	ans=n;
	for(int i=0;i<n;i++){
		scanf("%u",&k);
		if(k) ok=true;
		while(k--){
			scanf("%u",&l);
			if(!f[l]) ans++,f[l]=true;
			if(cow[i].link(language+l)) ans--;
		}
	}
	printf("%u\n",ans-ok);
}
