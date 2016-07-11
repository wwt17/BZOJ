#include <cstdio>
int n,sum,l,r,x;
struct group{
	int s,e,d;
	inline void read(){
		scanf("%d%d%d",&s,&e,&d);
		if(l>s) l=s;
		if(r<e) r=e;
		sum+=(e-s)/d+1;
	}
	inline int calc(){
		return s>x?0:((e<x?e:x)-s)/d+1;
	}
	inline bool ok(){
		return s<=r&&r<=e&&(r-s)%d==0;
	}
} g[200000];
int main(){
	int t; scanf("%d",&t);
	while(t--){
		scanf("%d",&n);
		sum=0;
		l=0x7fffffff;
		r=0;
		for(int i=0;i<n;i++) g[i].read();
		if(!(sum&1)){ puts("Poor QIN Teng:("); continue; }
		l--;
		while(l+1<r){
			x=l+(r-l)/2;
			sum=0;
			for(int i=0;i<n;i++) sum+=g[i].calc();
			if(sum&1)
				r=x;
			else
				l=x;
		}
		sum=0;
		for(int i=0;i<n;i++) sum+=g[i].ok();
		printf("%d %d\n",r,sum);
	}
}
