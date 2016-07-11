#define bool _Bool
#define false 0
#define true 1
int n,i,j,c,maxl;
bool memf[2][1001],*F=memf[0],*f=memf[1],*tmp;
int main(){
	scanf("%u%u%u",&n,&c,&maxl);
	F[c]=true;
	for(i=1;i<=n;i++,tmp=F,F=f,f=tmp){
		scanf("%u",&c);
		for(j=0;j<=maxl;j++) f[j]=false;
		for(j=c;j<=maxl;j++){
			if(F[j-c]) f[j]=true;
			if(F[j]) f[j-c]=true;
		}
	}
	for(j=maxl;j>=0&&!F[j];j--);
	if(j>=0) printf("%u\n",j); else puts("-1");
}
