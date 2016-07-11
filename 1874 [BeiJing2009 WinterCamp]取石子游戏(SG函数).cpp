#include <cstdio>
int n,m,a[10],k,b[10],sg[1005];
bool flag[11];
int mov[11];
int main(){
	scanf("%d",&n);
	for(int i=0;i<n;i++){
		scanf("%d",a+i);
		if(k<a[i]) k=a[i];
	}
	scanf("%d",&m);
	for(int j=0;j<m;j++) scanf("%d",b+j);
	for(int i=0;i<=k;i++){
		for(int j=0;j<m;j++) flag[j]=false;
		for(int j=0;j<m&&i>=b[j];j++) flag[sg[i-b[j]]]=true;
		flag[m]=false;
		for(int j=0;j<=m;j++) if(!flag[j]){
			sg[i]=j;
			break;
		}
	}
	int ans=0;
	for(int i=0;i<n;i++) ans^=sg[a[i]];
	if(!ans){ puts("NO"); return 0; }
	puts("YES");
	for(int i=0;i<n;i++)
		for(int j=0;j<m&&a[i]>=b[j];j++)
			if(!(ans^sg[a[i]]^sg[a[i]-b[j]])){
				printf("%d %d\n",i+1,b[j]);
				return 0;
			}
}
