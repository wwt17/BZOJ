#include <cstdio>
typedef long long ll;
const int base=100000000,Len=1005;
int n,d;
int a[Len],b[Len];
void print(int a[]){
	printf("%d",a[*a]);
	for(int i=*a-1;i>=1;i--) printf("%08d",a[i]);
}
void set(int a[],ll b){
	*a=0;
	while(b){
		a[++*a]=b%base;
		b/=base;
	}
}
void mul(int a[],ll b){
	ll x=0;
	for(int i=1;i<=*a;i++){
		x+=a[i]*b;
		a[i]=x%base;
		x/=base;
	}
	while(x){
		a[++*a]=x%base;
		x/=base;
	}
}
int mod(int a[],ll b){
	ll x=0;
	for(int i=*a;i;i--){
		x=x*base+a[i];
		x%=b;
	}
	return x;
}
void div(int a[],ll b){
	ll x=0;
	for(int i=*a;i;i--){
		x=x*base+a[i];
		a[i]=x/b;
		x%=b;
	}
	while(*a&&a[*a]==0) --*a;
}
void eli(int d){
	while(mod(a,d)==0&&mod(b,d)==0){
		div(a,d);
		div(b,d);
	}
}
int main(){
	while(scanf("%d%d",&n,&d)!=EOF){
		set(a,(n+4LL)*(n+4LL));
		mul(a,d*(d-1)/2);
		set(b,9);
		for(int i=1;i<=d;i++)
			mul(b,n);
		eli(3);
		for(int d=2;d*d<=n;d++) if(n%d==0){
			eli(d);
			while(n%d==0) n/=d;
		}
		if(n>1)
			eli(n);
		print(a);
		if(*b==1&&b[1]==1); else putchar('/'),print(b);
		puts("");
	}
}
