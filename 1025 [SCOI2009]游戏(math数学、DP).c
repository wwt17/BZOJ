int N,i,j,k;
_Bool flag[1001];
long long f[1001];
int main(){
	scanf("%u",&N);
	for(j=0;j<=N;j++) f[j]=1;
	for(i=2;i<=N;i++) if(!flag[i]){
		for(j=i<<1;j<=N;j+=i) flag[j]=1;
		for(j=N;j;j--)
			for(k=i;k<=j;k*=i)
				f[j]+=f[j-k];
	}
	printf("%llu\n",f[N]);
}
