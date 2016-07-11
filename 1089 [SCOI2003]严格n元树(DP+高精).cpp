#include <cstdio>
const int Len=505;
struct huge{
	int len,a[Len];
	friend huge operator * (const huge &a,const huge &b){
		huge c;
		c.len=a.len+b.len+2;
		int x=0;
		for(int i=0;i<c.len;i++){
			for(int j=0;j<=i;j++) if(j<a.len&&i-j<b.len)
				x+=a.a[j]*b.a[i-j];
			c.a[i]=x%10;
			x/=10;
		}
		while(c.len&&c.a[c.len-1]==0) c.len--;
		return c;
	}
	friend huge operator - (const huge &a,const huge &b){
		huge c;
		c.len=a.len;
		int x=0;
		for(int i=0;i<a.len;i++){
			x+=a.a[i]-(i<b.len?b.a[i]:0);
			if(x<0){
				c.a[i]=x+10;
				x=-1;
			}
			else{
				c.a[i]=x;
				x=0;
			}
		}
		while(c.len&&c.a[c.len-1]==0) c.len--;
		return c;
	}
	void operator ++ () {
		a[len++]=0;
		int i;
		for(i=0;a[i]==9;i++) a[i]=0;
		a[i]++;
		while(len&&a[len-1]==0) len--;
	}
	void print(){
		if(!len){
			puts("0");
			return;
		}
		printf("%d",a[len-1]);
		for(int i=len-2;i>=0;i--) printf("%d",a[i]);
		puts("");
	}
};
int n,d;
huge f[17];
int main(){
	scanf("%d%d",&n,&d);
	if(d==0) return puts("1"),0;
	f[0].len=1;
	f[0].a[0]=1;
	for(int i=1;i<=d;i++){
		f[i].len=1;
		f[i].a[0]=1;
		for(int j=0;j<n;j++) f[i]=f[i]*f[i-1];
		++f[i];
	}
	(f[d]-f[d-1]).print();
}
