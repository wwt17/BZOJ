#include <cstdio>
#include <cstdlib>
#include <algorithm>
using namespace std;
const int N=20,inf=1<<29;
int n,r1,c1,r2,c2,f[N][N][N][N][3*N][2];
int search(int r1,int c1,int r2,int c2,int step,bool flag){
	if(step==3*n) return inf;
	int &ans=f[r1][c1][r2][c2][step][flag];
	if(ans) return ans;
	if(r1==r2&&c1==c2) return ans=flag?inf:step;
	if(flag){
		ans=inf;
		if(r2){ ans=min(ans,search(r1,c1,r2-1,c2,step+1,!flag));
			if(r2>1) ans=min(ans,search(r1,c1,r2-2,c2,step+1,!flag));
		}
		if(r2<n-1){ ans=min(ans,search(r1,c1,r2+1,c2,step+1,!flag));
			if(r2<n-2) ans=min(ans,search(r1,c1,r2+2,c2,step+1,!flag));
		}
		if(c2){ ans=min(ans,search(r1,c1,r2,c2-1,step+1,!flag));
			if(c2>1) ans=min(ans,search(r1,c1,r2,c2-2,step+1,!flag));
		}
		if(c2<n-1){ ans=min(ans,search(r1,c1,r2,c2+1,step+1,!flag));
			if(c2<n-2) ans=min(ans,search(r1,c1,r2,c2+2,step+1,!flag));
		}
	}
	else{
		ans=0;
		if(r1) ans=max(ans,search(r1-1,c1,r2,c2,step+1,!flag));
		if(r1<n-1) ans=max(ans,search(r1+1,c1,r2,c2,step+1,!flag));
		if(c1) ans=max(ans,search(r1,c1-1,r2,c2,step+1,!flag));
		if(c1<n-1) ans=max(ans,search(r1,c1+1,r2,c2,step+1,!flag));
	}
	return ans;
}
int main(){
	scanf("%d%d%d%d%d",&n,&r1,&c1,&r2,&c2);
	r1--,c1--,r2--,c2--;
	if((r1-r2)*(r1-r2)+(c1-c2)*(c1-c2)==1)
		puts("WHITE 1");
	else
		printf("BLACK %d\n",search(r1,c1,r2,c2,0,0));
}
