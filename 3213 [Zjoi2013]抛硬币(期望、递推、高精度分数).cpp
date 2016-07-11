/*
f[i]=1+p*f[i+1]+(1-p)*f[j]
 f[i+1]
=(f[i]-1-(b-a/b)*f[j])*b/a
=f[i]*b/a-f[j]*(b-a)/a-b/a
若把f全都变反，则ans=f[n]
-f[i+1]
=(-f[i]+1-(b-a)/b*-f[j])*b/a

f[i+1]=f[i]*b/a+b/a-(b-a)/a*f[j]
f[i+1]=f[i]*b/(b-a)+b/(b-a)-a/(b-a)*f[j]
*/
#include <cstdio>
#include <algorithm>
using namespace std;
const int N=1005,base=100000000,primes=25,prime[primes]={2,3,5,7,11,13,17,19,23,29,31,37,41,43,47,53,59,61,67,71,73,79,83,89,97};
char s[N];
int fail[N];
struct big{
	int a[300];
	big(int x=0){
		if(x){
			a[0]=1;
			a[1]=x;
		}
		else
			a[0]=0;
	}
	void print(){
		printf("%d",a[a[0]]);
		for(int i=a[0]-1;i>0;i--)
			printf("%08d",a[i]);
	}
};
big operator + (big a,big b){
	if(a.a[0]<b.a[0]) swap(a,b);
	big c=a;
	c.a[++c.a[0]]=0;
	int x=0;
	for(int i=1;i<=b.a[0];i++){
		x+=c.a[i]+b.a[i];
		c.a[i]=x%base;
		x/=base;
	}
	for(int i=b.a[0]+1;x;i++){
		x+=c.a[i];
		c.a[i]=x%base;
		x/=base;
	}
	while(c.a[0]&&!c.a[c.a[0]]) c.a[0]--;
	return c;
}
big operator - (big a,big b){
	big c=a;
	int x=0;
	for(int i=1;i<=b.a[0];i++){
		x+=c.a[i]-b.a[i];
		if(x>=0){
			c.a[i]=x%base;
			x/=base;
		}
		else{
			c.a[i]=(x+base)%base;
			x=-1;
		}
	}
	for(int i=b.a[0]+1;x;i++){
		x+=c.a[i];
		if(x>=0){
			c.a[i]=x%base;
			x/=base;
		}
		else{
			c.a[i]=(x+base)%base;
			x=-1;
		}
	}
	while(c.a[0]&&!c.a[c.a[0]]) c.a[0]--;
	return c;
}
big operator * (big &a,big &b){
	big c;
	c.a[0]=a.a[0]+b.a[0];
	for(int i=1;i<=c.a[0];i++) c.a[i]=0;
	for(int j=1;j<=b.a[0];j++){
		long long x=0;
		for(int i=1;i<=a.a[0];i++){
			x+=(long long)a.a[i]*b.a[j]+c.a[i+j-1];
			c.a[i+j-1]=x%base;
			x/=base;
		}
		for(int i=a.a[0]+j;x;i++){
			x+=c.a[i];
			c.a[i]=x%base;
			x/=base;
		}
	}
	while(c.a[0]&&!c.a[c.a[0]]) c.a[0]--;
	return c;
}
int operator % (big &a,int b){
	long long x=0;
	for(int i=a.a[0];i>0;i--){
		x=x*base+a.a[i];
		x%=b;
	}
	return x;
}
void operator /= (big &a,int b){
	long long x=0;
	for(int i=a.a[0];i>0;i--){
		x=x*base+a.a[i];
		a.a[i]=x/b;
		x%=b;
	}
	while(a.a[0]&&!a.a[a.a[0]]) a.a[0]--;
}
struct frac{
	big a,b;
	frac(big p=0,big q=1):a(p),b(q){
	}
	void print(){
		a.print();
		putchar('/');
		b.print();
	}
	void adjust(){
		for(int i=0;i<primes;i++){
			while(!(a%prime[i]||b%prime[i])){
				a/=prime[i];
				b/=prime[i];
			}
		}
	}
} p[2][2],f[N];
frac operator + (frac a,frac b){
	return frac(a.a*b.b+b.a*a.b,a.b*b.b);
}
frac operator - (frac a,frac b){
	return frac(a.a*b.b-b.a*a.b,a.b*b.b);
}
frac operator * (frac a,frac &b){
	return frac(a.a*b.a,a.b*b.b);
}
int main(){
	int a,b;
	scanf("%d%d",&a,&b);
	p[0][0]=frac(b,a);
	p[0][1]=frac(b-a,a);
	p[1][0]=frac(b,b-a);
	p[1][1]=frac(a,b-a);
	frac e(1,1);
	scanf("%s",s+1);
	fail[1]=0;
	for(int i=2;s[i];i++){
		int j=fail[i-1];
		while(j&&s[j+1]!=s[i]) j=fail[j];
		fail[i]=s[j+1]==s[i]?j+1:0;
	}
	int i;
	s[0]=1;
	for(i=0;s[i+1];i++){
		int j=i;
		while(j&&s[j+1]==s[i+1]) j=fail[j];
		if(s[j+1]!=s[i+1]) j++;
		bool t=s[i+1]!='H';
		//f[i+1]=f[i]*b/a+b/a-(b-a)/a*f[j]
		//f[i+1]=f[i]*b/(b-a)+b/(b-a)-a/(b-a)*f[j]
		f[i+1]=(f[i]+e)*p[t][0]-f[j]*p[t][1];
		f[i+1].adjust();
	}
	f[i].print(),puts("");
}
