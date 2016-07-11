#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;
const int N=105,W=1010;
int n,tot,s,w[N],v[N],f[W];
int work(){
	for(int i=0;i<n;i++) scanf("%d%d",&w[i],&v[i]);
	memset(f,0,sizeof(f));
	s=0;
	for(int j=0;j<=30;j++){
		for(int i=0;i<n;i++) if((w[i]&-w[i])>>j&1){
			int t=min(s+w[i],tot);
			for(int k=(s>>j)+2;k<=(t>>j)+1;k++) f[k]=f[k-1];
			s=t;
			for(int k=(s>>j)+1;k>=w[i]>>j;k--)
				f[k]=max(f[k],f[k-(w[i]>>j)]+v[i]);
		}
		for(int k=(s>>j)+2;k<W;k++) f[k]=f[k-1];
		for(int k=0;k<=(s>>j+1)+1;k++)
			f[k]=tot>>j&1?max(f[k<<1],f[k<<1|1]):f[k<<1];
	}
	return f[0];
}
int main(){
	while(scanf("%d%d",&n,&tot),n!=-1)
		printf("%d\n",work());
}
