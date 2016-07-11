#define N 20001
unsigned cnt[N],loc[N][5],t[5*N];
int main(){
	unsigned n,nn,a,i,j,k,x,v;
	scanf("%u",&n); nn=5*n;
	for(i=1;i<=nn;i++)
		scanf("%u",&a),loc[a][cnt[a]++]=i;
	for(i=1;i<=nn;i++)
		for(scanf("%u",&a),k=5;k--;){
			for(v=0,x=loc[a][k]-1;x;x-=x&-x) if(v<t[x]) v=t[x];
			for(v++,x=loc[a][k];x<=nn;x+=x&-x) if(t[x]<v) t[x]=v;
		}
	for(v=0,x=nn;x;x-=x&-x) if(v<t[x]) v=t[x];
	printf("%u\n",v);
}
