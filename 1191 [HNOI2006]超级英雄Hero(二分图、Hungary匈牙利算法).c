#include <stdio.h>
int n,m,i,a[1000][2],pre[1000];
_Bool used[1000];
_Bool extend(const int i){
	if(i==-1) return 1;
	int k,j;
	for(k=0;k<2;k++) if(!used[j=a[i][k]]){
		used[j]=1;
		if(extend(pre[j])){
			pre[j]=i;
			return 1;
		}
	}
	return 0;
}
int main(){
	scanf("%u%u",&n,&m);
	for(i=0;i<m;i++) scanf("%u%u",a[i],a[i]+1);
	memset(pre,-1,n*sizeof(pre[0]));
	for(i=0;i<m;i++){
		memset(used,0,n);
		if(!extend(i)) break;
	}
	printf("%u\n",i);
}
