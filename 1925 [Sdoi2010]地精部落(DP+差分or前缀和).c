/*
f[i+1][j+1 to i+1][1]+=f[i][j][0]
f[i+1][1 to j][0]+=f[i][j][1]

f[i][j][0]=f[i][i-j+1][1]

f[i+1][j+1 to i+1]+=f[i][i-j+1]
k=i-j+1
f[i+1][i-k+2 to i+1]+=f[i][k]

f[i+1][i-j+2 to i+1]+=f[i][j]
*/
int N,P,i,j,memD[2][4201],*D=memD[0],*d=memD[1],*tmp,f,Ans;
#define inc(a,b) if((a=(a+b)%P)<0) a+=P
int main(){
	scanf("%u%u",&N,&P);
	D[0]=1;
	for(i=1;i<N;tmp=D,D=d,d=tmp,i++){
		for(j=0;j<=i;j++) d[j]=0;
		for(f=0,j=1;j<=i;j++){
			inc(f,D[j-1]);
			inc(d[i-j+1],f);
		}
	}
	for(f=0,j=0;j<i;j++){ inc(f,D[j]); inc(Ans,f); }
	inc(Ans,Ans);
	printf("%d\n",Ans);
}
