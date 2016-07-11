#include <cstdio>
const int N=155;
int p,q,r,ans;
bool a[N][N][N],b[N][N][N];
int f[N][N][N];
struct data{
	int loc,h;
} s[N],*end;
inline int min(const int a,const int b){
	return a<b?a:b;
}
inline void renew(const int a){
	if(ans<a) ans=a;
}
#define REP \
for(int i=1;i<=p;i++)\
for(int j=1;j<=q;j++)\
for(int k=1;k<=r;k++)
void calc(int p,int q,int r){
	for(int i=1;i<=p;i++)
	for(int j=1;j<=q;j++){
	*(end=s)++=(data){0,0};
	for(int k=1;k<=r;k++){
		if(b[i][j][k]){
			int t=min(f[i-1][j][k],f[i][j-1][k]);
			f[i][j][k]=t+b[i-t][j-t][k];
		}
		else
			f[i][j][k]=0;
		int l=k;
		while(end[-1].h>f[i][j][k]){
			end--;
			renew(end->h*(k-end->loc));
			if(end->loc<l) l=end->loc;
		}
		*end++=(data){l,f[i][j][k]};
	}
	while(end[-1].h){
		end--;
		renew(end->h*(r+1-end->loc));
	}
	}
}
int main(){
	scanf("%d%d%d",&p,&q,&r);
	for(int j=1;j<=q;j++)
	for(int i=1;i<=p;i++)
	for(int k=1;k<=r;k++){
		loop:
		switch(getchar()){
			case 'P': a[i][j][k]=0; break;
			case 'N': a[i][j][k]=1; break;
			default: goto loop;
		}
		b[i][j][k]=a[i][j][k];
	}
	calc(p,q,r);
	REP b[j][k][i]=a[i][j][k];
	calc(q,r,p);
	REP b[i][k][j]=a[i][j][k];
	calc(p,r,q);
	printf("%d\n",4*ans);
}
