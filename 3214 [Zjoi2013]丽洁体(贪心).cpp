#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;
const int N=50005;
int ans;
int t[N],a[N],b[N];
void read(int *s){
	*s=0;
	char ch='?'; int x=0;
	while(ch!='\n'){
		ch=getchar();
		if(ch==' '||ch=='\n') s[++*s]=x,x=0;
		else if(ch!='\r') x=x*27+ch-'@';
	}
}
int work(int s[],int a[],bool cpy){
	int res=0;
	int *t=s+1,*b=a+1;
	for(;b<a+*a+1;b++){
		for(;t<s+*s+1&&*t!=*b;t++)
			res++;
		if(t==s+*s+1)
			return N;
		t++;
	}
	if(cpy){
		memmove(s+1,t,(s+*s+1-t)*sizeof(int));
		*s=s+*s+1-t;
	}
	return res;
}
int main(){
	#define rev(s) reverse(s+1,s+*s+1)
	read(t);
	read(a);
	ans+=work(t,a,1);
	read(b);
	read(a);
	rev(a);
	rev(t);
	ans+=work(t,a,1);
	rev(t);
	int tmp=N;
	for(int *s=t;s<t+*t;s++)
		if(s[1]==b[1]){
			int tm=s[0];
			s[0]=t+*t-s;
			int res=work(s,b,0);
			s[0]=tm;
			if(res==N) break;
			tmp=min(tmp,res);
		}
	printf("%d\n",ans+tmp);
}
