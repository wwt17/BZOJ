#include <cstdio>
#include <algorithm>
using namespace std;

const int N=105,M=10,S=177147,P=20110520;

int pow3[M+2];

int n,m;
char map[N][N];
int maxs,mem[2][S],*F=mem[0],*f=mem[1];

int main(){
	scanf("%d%d",&n,&m);
	for(int i=0;i<n;i++) scanf("%s",map[i]);
	if(m>n){
		for(int i=0;i<m;i++)
			for(int j=0;j<i;j++)
				swap(map[i][j],map[j][i]);
		swap(m,n);
	}
	pow3[0]=1;
	for(int i=1;i<=m+1;i++) pow3[i]=pow3[i-1]*3;
	maxs=pow3[m+1];
	for(int s=0;s<maxs;s++) F[s]=0;
	F[0]=1;
	for(int i=0;i<n;i++){
		for(int j=0;j<m;j++){
			for(int s=0;s<maxs;s++) f[s]=0;
			for(int s=0;s<maxs;s++){
				int t=s/pow3[j]%9,b=t/3,a=t-b*3,ss=s-t*pow3[j];
				if(map[i][j]=='*'){
					if(!a&&!b) f[ss]+=F[s];
				}
				else{
					if(!a&&!b){
						f[ss+pow3[j]]+=F[s];
						f[ss+pow3[j+1]]+=F[s];
						f[ss+8*pow3[j]]+=F[s];
					}
					else
					if(a&&!b){
						f[ss+a*pow3[j+1]]+=F[s];
						if(a==1)
							f[ss+2*pow3[j]]+=F[s];
						else
							f[ss]+=F[s];
					}
					else
					if(b&&!a){
						f[ss+b*pow3[j]]+=F[s];
						if(b==1)
							f[ss+2*pow3[j+1]]+=F[s];
						else
							f[ss]+=F[s];
					}
					else
					if(a==1&&b==1){
						f[ss]+=F[s];
					}
				}
			}
			for(int s=0;s<maxs;s++) f[s]%=P;
			swap(F,f);
		}
		for(int s=0;s<maxs;s++) f[s]=s%3?0:F[s/3];
		swap(F,f);
	}
	printf("%d\n",F[0]);
}
