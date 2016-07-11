#include <cstdio>
inline int min(const int a,const int b){
	return a<b?a:b;
}
int N,M,C[15],P[15],L[15],x,y,c,g; bool ok;
void extgcd(int a,int b){
	if(!b){
		if(c%a) ok=false; else ok=true,x=c/a; y=0;
		g=a>0?a:-a;
		return;
	}
	extgcd(b,a%b);
	if(!ok) return;
	int t=x; x=y; y=t-a/b*y;
}
#define solve(a,C) ( c=C,extgcd(a,M),(x%(M/g)+M/g)%(M/g))
int main(){
	scanf("%d",&N);
	for(int i=0;i<N;i++){
		scanf("%d%d%d",C+i,P+i,L+i);
		if(M<C[i]) M=C[i];
		C[i]--;
	}
	for(;;M++){
		for(int i=0;i<N;i++)
			for(int j=i+1;j<N;j++){
				int k=solve(P[i]-P[j],C[j]-C[i]);
				if(ok&&k<=min(L[i],L[j])) goto out;
			}
		printf("%u\n",M);
		return 0;
		out:;
	}
}
