int Sr,Sb,Sg,i,j,r,b,g,m,M,P,t[61],f[21][21][21],sum,ans;
_Bool book[61];
int a,b,x,y;
#define inc(a,b) a=(a+b)%P
void extended_gcd(const int a,const int b){
	if(!b){ x=1; y=0; return; }
	extended_gcd(b,a%b);
	int t=x; x=y; y=t-a/b*y;
}
#define inv(k) (extended_gcd(k,P),(x%P+P)%P)
inline int work(){
	for(i=1;i<=Sr+Sb+Sg;i++) book[i]=0;
	for(r=0;r<=Sr;r++)
		for(b=0;b<=Sb;b++)
			for(g=0;g<=Sg;g++)
				f[r][b][g]=0;
	f[0][0][0]=1;
	for(i=1;i<=Sr+Sb+Sg;i++) if(!book[i]){
		for(sum=0,j=i;!book[j];sum++,j=t[j]) book[j]=1;
		for(r=Sr;r>=0;r--)
			for(b=Sb;b>=0;b--)
				for(g=Sg;g>=0;g--){
					if(r>=sum) inc(f[r][b][g],f[r-sum][b][g]);
					if(b>=sum) inc(f[r][b][g],f[r][b-sum][g]);
					if(g>=sum) inc(f[r][b][g],f[r][b][g-sum]);
				}
	}
	inc(ans,f[Sr][Sb][Sg]);
}
int main(){
	scanf("%u%u%u%u%u",&Sr,&Sb,&Sg,&M,&P);
	for(i=1;i<=Sr+Sb+Sg;i++) t[i]=i;
	work();
	for(m=M;m;m--){
		for(i=1;i<=Sr+Sb+Sg;i++) scanf("%u",t+i);
		work();
	}
	printf("%u\n",(long long)ans*inv(M+1)%P);
	return 0;
}
