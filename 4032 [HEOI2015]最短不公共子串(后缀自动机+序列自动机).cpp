#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;

const int maxL=2015;

int n,m;
char A[maxL],B[maxL];

int trans[maxL*2][26],pa[maxL*2],len[maxL*2];
int tail=1,newnode=2;

int extend(int p,int c){
	int np=newnode++;
	len[np]=len[p]+1;
	for(;p&&trans[p][c]==0;p=pa[p]) trans[p][c]=np;
	if(p==0)
		pa[np]=1;
	else{
		int q=trans[p][c];
		if(len[q]==len[p]+1)
			pa[np]=q;
		else{
			int nq=newnode++;
			len[nq]=len[p]+1;
			memcpy(trans[nq],trans[q],sizeof(trans[q]));
			pa[nq]=pa[q];
			pa[q]=pa[np]=nq;
			for(;p&&trans[p][c]==q;p=pa[p]) trans[p][c]=nq;
		}
	}
	return np;
}

int next[maxL][26];

int f[maxL*2],g[maxL*2];

int main(){
	scanf("%s%s",A+1,B+1);
	n=strlen(A+1);
	m=strlen(B+1);
	for(int i=1;i<=n;i++) A[i]-='a';
	for(int i=1;i<=m;i++) B[i]-='a';
	for(int i=1;i<=m;i++)
		tail=extend(tail,B[i]);
	for(int c=0;c<26;c++) next[m][c]=m+1;
	for(int i=m;i>=1;i--){
		memcpy(next[i-1],next[i],sizeof(next[i]));
		next[i-1][B[i]]=i;
	}
	int ans;
	ans=n+1;
	for(int i=1;i<=n;i++){
		int cur=1;
		for(int j=i;j<=n;j++){
			cur=trans[cur][A[j]];
			if(cur==0){
				ans=min(ans,j-i+1);
				break;
			}
		}
	}
	printf("%d\n",ans==n+1?-1:ans);
	ans=n+1;
	for(int i=1;i<=n;i++){
		int cur=0;
		for(int j=i;j<=n;j++){
			cur=next[cur][A[j]];
			if(cur==m+1){
				ans=min(ans,j-i+1);
				break;
			}
		}
	}
	printf("%d\n",ans==n+1?-1:ans);
	for(int j=0;j<newnode;j++) f[j]=n+1;
	f[1]=0;
	for(int i=1;i<=n;i++){
		for(int j=0;j<newnode;j++) g[j]=f[j];
		for(int j=1;j<newnode;j++){
			int k=trans[j][A[i]];
			g[k]=min(g[k],f[j]+1);
		}
		for(int j=0;j<newnode;j++) f[j]=g[j];
	}
	printf("%d\n",f[0]==n+1?-1:f[0]);
	for(int j=0;j<=m+1;j++) f[j]=n+1;
	f[0]=0;
	for(int i=1;i<=n;i++){
		for(int j=0;j<=m+1;j++) g[j]=f[j];
		for(int j=0;j<=m;j++){
			int k=next[j][A[i]];
			g[k]=min(g[k],f[j]+1);
		}
		for(int j=0;j<=m+1;j++) f[j]=g[j];
	}
	printf("%d\n",f[m+1]==n+1?-1:f[m+1]);
}
