#include <stdio.h>
#define size 5002
short N,R,i,j,a,ans;
int f[size][size];
int main(){
	scanf("%hd%hd",&N,&R);
	while (N--) scanf("%hd%hd",&i,&j),scanf("%d",&f[i+1][j+1]);
	for (i=1;i<size;++i)
		for (j=1;j<size;++j)
			f[i][j]+=f[i-1][j]+f[i][j-1]-f[i-1][j-1];
	for (i=0;i+R<size;++i)
		for (j=0;j+R<size;++j)
			if ((a=f[i+R][j+R]+f[i][j]-f[i+R][j]-f[i][j+R])>ans)
				ans=a;
	printf("%hd\n",ans);
	return 0;
}
