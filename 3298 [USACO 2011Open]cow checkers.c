int M,N,m,n,x,y,cnt,T,f[1000000];
int main(){
	scanf("%u%u",&M,&N);
	scanf("%u",&T);
	while(T--){
		scanf("%u%u",&x,&y);
		for(;m<=x;m++) if(!f[m]){
			f[m]=m+cnt++;
			if(f[m]<M) f[f[m]]=m;
		}
		puts(f[x]==y?"Farmer John":"Bessie");
	}
}
