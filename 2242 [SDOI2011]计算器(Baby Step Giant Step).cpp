#include <cstdio>
#include <cmath>
#include <map>
using namespace std;
int test,kind,y,z,p,C; long long X,Y; bool fail;
void ext_gcd(int a,int b){
	if(!b){
		if(C%a) fail=true;
		else{ X=C/a; Y=0; }
		return;
	}
	ext_gcd(b,a%b);
	if(fail) return;
	long long t=X; X=Y; Y=t-a/b*Y;
}
int BSGS(int a,int c,int p){
	int n=(int)sqrt(p);
	map<int,int> s;
	long long t=1;
	for(int r=0;r<n;r++){
		s.insert(make_pair((int)t,r));
		t=t*a%p;
	}
	C=1; ext_gcd((int)t,p);
	X=(X%p+p)%p;
	for(int k=0;k<=n;k++){
		map<int,int>::iterator it=s.find(c);
		if(it!=s.end())
			return k*n+it->second;
		c=(long long)c*X%p;
	}
	fail=true;
	return -1;
}
int main(){
	scanf("%d%d",&test,&kind);
	int ans;
	while(test--){
		scanf("%d%d%d",&y,&z,&p);
		fail=false;
		switch(kind){
			case 1:
				ans=1;
				for(;z;z>>=1,y=(long long)y*y%p) if(z&1)
					ans=(long long)ans*y%p;
				printf("%d\n",(int)ans);
				break;
			case 2:
				C=z; ext_gcd(y,p);
				if(fail){ puts("Orz, I cannot find x!"); break; }
				X=(X%p+p)%p;
				printf("%d\n",(int)X);
				break;
			case 3:
				ans=BSGS(y,z,p);
				if(fail){ puts("Orz, I cannot find x!"); break; }
				printf("%d\n",ans);
		}
	}
}
