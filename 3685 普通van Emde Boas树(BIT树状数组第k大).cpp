#include <cstdio>
inline int getint(){
	char c; bool f=false;
	while((c=getchar())<'0'||c>'9') if(c=='-') f^=1; int a=c-'0';
	while((c=getchar())>='0'&&c<='9') a=a*10+c-'0'; if(f) a=-a;
	return a;
}

const int N=1e6+5;
int base,n,m,cnt,x,s;
bool exist[N];
int t[N];

void add(int x,int d){
	for(;x<=n;x+=x&-x) t[x]+=d;
}
int query(int x){
	int s=0;
	for(;x;x-=x&-x) s+=t[x];
	return s;
}
int kth(int k){
	int x=0;
	for(int b=base;b;b>>=1)
		if(x+b<=n&&t[x+b]<k)
			k-=t[x+=b];
	return x+1;
}

int main(){
	n=getint(),m=getint();
	for(base=1;base<n;base<<=1);
	while(m--)
		switch(getint()){
			case 1:
				if(!exist[x=getint()+1]){
					exist[x]=1;
					add(x,1);
					cnt++;
				}
				break;
			case 2:
				if(exist[x=getint()+1]){
					exist[x]=0;
					add(x,-1);
					cnt--;
				}
				break;
			case 3:
				printf("%d\n",cnt?kth(1)-1:-1);
				break;
			case 4:
				printf("%d\n",cnt?kth(cnt)-1:-1);
				break;
			case 5:
				printf("%d\n",(s=query(getint()  ))     ?kth(s  )-1:-1);
				break;
			case 6:
				printf("%d\n",(s=query(getint()+1))!=cnt?kth(s+1)-1:-1);
				break;
			case 7:
				printf("%d\n",exist[getint()+1]?1:-1);
				break;
		}
}
