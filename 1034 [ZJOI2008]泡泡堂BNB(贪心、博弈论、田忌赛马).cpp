#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;
#define N 100000 
int n,i,l,r,A[N],B[N],C[N];
inline void Add(int l,int r,const int c){
	if(r<0||l>r) return; if(l<0) l=0;
	C[l]+=c; C[r+1]-=c;
}
int Solve(int A[N],int B[N]){
	memset(C,0,sizeof(C[0])*n);
	for(i=0;i<n;i++){
		l=lower_bound(B,B+n,A[i])-B;
		r=upper_bound(B,B+n,A[i])-B;
		Add(i-l+1,i,2);
		Add(i-r+1,i-l,1);
	}
	int Sum=0,Ans=0;
	for(i=0;i<n;i++) Ans=max(Ans,Sum+=C[i]);
	return Ans;
}
int main(){
	scanf("%u",&n);
	for(i=0;i<n;i++) scanf("%u",A+i);
	for(i=0;i<n;i++) scanf("%u",B+i);
	sort(A,A+n);
	sort(B,B+n);
	printf("%u %u\n",Solve(A,B),n*2-Solve(B,A));
}
