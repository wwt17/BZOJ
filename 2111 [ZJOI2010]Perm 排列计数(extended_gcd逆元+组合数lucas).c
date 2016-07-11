/*
tmp=(1<<lg(i+1))-1
if(i-tmp<=(tmp+1)>>1)
	left=(tmp>>1)+(i-tmp);
else
	left=tmp;
right=i-1-left;
f[i]=f[left]*f[right]*C(i-1,left)
*/
#define N 1000001
#define ll long long
int n,i,left,P,tmp[N],f[N],fac[N];
long long x,y,t;
void extended_gcd(const int a,const int b){
	if(!b){ x=1; y=0; return; }
	extended_gcd(b,a%b);
	t=x; x=y; y=t-a/b*y;
}
inline long long inverse(int k){
	extended_gcd(k,P); return (x%P+P)%P;
}
inline int C(int n,int m){
	int ans=1;
	for(;m;n/=P,m/=P){
		int a=n%P,b=m%P;
		if(a<b) return 0;
		ans=(ll)ans*fac[a]%P*inverse((ll)fac[a-b]*fac[b]%P)%P;
	}
	return ans;
}
int main(){
	scanf("%d%d",&n,&P);
	tmp[0]=0;
	fac[0]=1;
	f[0]=1;
	for(i=1;i<=n;i++){
		tmp[i]=tmp[((i+1)>>1)-1]<<1|1;
		fac[i]=(ll)fac[i-1]*i%P;
		left=i-tmp[i]<(tmp[i]+1)>>1?(tmp[i]>>1)+i-tmp[i]:tmp[i];
		f[i]=(ll)f[left]*f[i-1-left]%P*C(i-1,left)%P;
	}
	printf("%d\n",f[n]);
}
