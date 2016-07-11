#include <string.h>
#define bool _Bool
#define false 0
#define true 1
int n,m,i,j,k,s[401],t[403];
int main(){
	scanf("%u%u",&n,&m);
	for(i=0;i<3*m+1;i++) scanf("%u",&j),s[j]++;
	bool found=false;
	for(i=1;i<=n;i++){
		s[i]++;
		for(k=1;k<=n;k++) if(s[k]>=2){
			memcpy(t+1,s+1,n*sizeof(int));
			t[k]-=2;
			for(j=1;j<=n;j++){
				t[j]%=3;
				if(t[j+1]<t[j]||t[j+2]<t[j]) break;
				t[j+1]-=t[j],t[j+2]-=t[j];
			}
			if(j>n){
				if(found) putchar(' '); else found=true;
				printf("%u",i);
				break;
			}
		}
		s[i]--;
	}
	puts(found?"":"NO");
}
