#include <cstdio>
const int Base=100000000;
struct big{
	int len,a[20];
	void get(){
		static char s[105];
		scanf("%s",s);
		a[len=0]=0;
		char *c=s;
		while(*c) c++;
		int w=1;
		while(c-->s){
			a[len]+=(*c-'0')*w;
			w*=10;
			if(w==Base){
				a[++len]=0;
				w=1;
			}
		}
		if(len&&!a[len]) len--;
	}
	void println(){
		printf("%d",a[len]);
		for(int i=len-1;i>=0;i--) printf("%08d",a[i]);
		putchar('\n');
	}
	bool operator == (int x){
		return len==0&&a[0]==x;
	}
	void operator = (int x){
		a[len=0]=x;
	}
	void operator /= (int x){
		int t=0;
		for(int i=len;i>=0;i--){
			t*=Base;
			t+=a[i];
			a[i]=t/x;
			t%=x;
		}
		while(len&&!a[len]) len--;
	}
	bool odd(){
		return a[0]&1;
	}
	void operator += (big &b){
		int t=0;
		for(;len<b.len;a[++len]=0);
		for(int i=0;i<=b.len;i++){
			t+=a[i]+b.a[i];
			a[i]=t%Base;
			t/=Base;
		}
		a[++len]=0;
		for(int i=b.len+1;t;i++){
			t+=a[i];
			a[i]=t%Base;
			t/=Base;
		}
		while(len&&!a[len]) len--;
	}
} n,p,q;
void calc(){
	if(n==0){
		p=0;
		q=1;
		return;
	}
	bool tmp=n.odd();
	n/=2;
	calc();
	if(tmp)
		p+=q;
	else
		q+=p;
}	
int main(){
	int t; scanf("%d",&t);
	while(t--){
		n.get();
		calc();
		p.println();
	}
}
