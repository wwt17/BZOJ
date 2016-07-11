#include <cstdio>
#include <algorithm>
using namespace std;
const int N=(int)1e5+5;

int n,m,s,en[N],lef[N],rit[N];
char str[N],a[N*3];
int up[N*3];
#define get(x,y) ((x)+(y)*(n+1))
int work(int l,int r){
	if(l>=r) return 0;
	int bslef[2]={0},bsrit[2]={0},smid=0,inside=0;
	for(int k=1;k<=s;k++){
		for(int now=0,j=en[k-1]+1;j<=en[k];j++)
			if(up[get(r,j)]<=l)
				inside=max(inside,++now);
			else
				now=0;
		for(lef[k]=0;lef[k]<en[k]-en[k-1]&&up[get(r,en[k-1]+lef[k]+1)]<=l;lef[k]++);
		for(rit[k]=0;rit[k]<en[k]-en[k-1]&&up[get(r,en[k  ]-rit[k]  )]<=l;rit[k]++);
		if(lef[k]==en[k]-en[k-1])
			smid+=lef[k];
		else{
			if(lef[k]>lef[bslef[0]]) bslef[1]=bslef[0],bslef[0]=k; else
			if(lef[k]>lef[bslef[1]]) bslef[1]=k;
			if(rit[k]>rit[bsrit[0]]) bsrit[1]=bsrit[0],bsrit[0]=k; else
			if(rit[k]>rit[bsrit[1]]) bsrit[1]=k;
		}
	}
	if(bslef[0]==bsrit[0])
		smid+=max(lef[bslef[0]]+rit[bsrit[1]],lef[bslef[1]]+rit[bsrit[0]]);
	else
		smid+=lef[bslef[0]]+rit[bsrit[0]];
	return max(inside,smid)*(r-l);
}

int Main(){
	scanf("%d%d",&s,&n);
	for(int k=1;k<=s;k++){
		int t; scanf("%d",&t);
		for(int i=1;i<=n;i++){
			scanf("%s",str+1);
			for(int j=1;j<=t;j++)
				a[get(i,en[k-1]+j)]=str[j]-'0';
		}
		en[k]=en[k-1]+t;
	}
	m=en[s];
	for(int j=1;j<=m;j++){
		up[get(0,j)]=0;
		for(int i=1;i<=n;i++){
			if(a[get(i,j)])
				up[get(i,j)]=i;
			else
				up[get(i,j)]=up[get(i-1,j)];
		}
	}
	int ans=0;
	if(n<=m){
		for(int l=0;l<n;l++)
			for(int r=l+1;r<=n;r++)
				ans=max(ans,work(l,r));
	}
	else{
		for(int r=1;r<=n;r++)
			for(int j=1;j<=m;j++)
				ans=max(ans,work(up[get(r,j)],r));
	}
	return ans;
}

int main(){
	int T; scanf("%d",&T);
	while(T--) printf("%d\n",Main());
}
