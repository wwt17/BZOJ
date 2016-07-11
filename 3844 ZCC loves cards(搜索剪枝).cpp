#include <cstdio>
#include <algorithm>
using namespace std;

int n,k,L,R,r,a[25],b[15],c[15],ok[256];

void dfs3(int i,int val,int d){
	if(i>k){
		ok[val]+=d;
		return;
	}
	dfs3(i+1,val,d);
	dfs3(i+1,val^b[i],d);
}

void dfs2(int i){
	if(i>k){
		for(int i=1;i<=k;i++) b[i+k]=b[i];
		for(int i=1;i<=k*2;i++) c[i]=c[i-1]^b[i];
		for(int i=0;i<k;i++)
			for(int j=i+1;j-i<=k;j++){
				ok[c[i]^c[j]]++;
			}
		for(r=L-1;ok[r+1];r++);
		if(r>R) R=r;
		for(int i=0;i<k;i++)
			for(int j=i+1;j-i<=k;j++){
				ok[c[i]^c[j]]--;
			}
		return;
	}
	for(int j=i;j<=k;j++){
		swap(b[i],b[j]);
		dfs2(i+1);
		swap(b[i],b[j]);
	}
}

void dfs(int loc,int cnt){
	if(cnt>k){
		dfs3(1,0,1);
		for(r=L-1;r<=R&&ok[r+1];r++);
		if(r>R){
			dfs3(1,0,-1);
			dfs2(1);
		}
		else
			dfs3(1,0,-1);
		return;
	}
	for(int i=loc;i<=n;i++){
		b[cnt]=a[i];
		dfs(i+1,cnt+1);
	}
}

int main(){
	while(scanf("%d%d%d",&n,&k,&L)!=EOF){
		for(int i=1;i<=n;i++) scanf("%d",&a[i]);
		R=L-1;
		dfs(1,1);
		if(R==L-1) R=0;
		printf("%d\n",R);
	}
}
