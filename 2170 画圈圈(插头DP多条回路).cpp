#include <cstdio>

const int M=12,S=1<<M+1,P=123456791;

int maxs,n,m,in[S],mem[2][S],*f=mem[0],*F=mem[1];

int main(){
	scanf("%d%d",&n,&m);
	maxs=1<<m+1;
	for(int s=1;s<maxs;s++)
		in[s]=in[s>>1]<<1|((in[s>>1]&1)^(s&1));
	f[0]=1;
	for(int i=0;i<n;i++){
		static char map[M+1]; scanf("%s",map);
		for(int j=0;j<m;j++){
			for(int ss=0;ss<maxs;ss++) F[ss]=0;
			for(int s=0;s<maxs;s++){
				int x=s>>j&1,y=s>>j+1&1,ss=s-(x<<j)-(y<<j+1);
				switch(map[j]){
					case '*':
						if(x||y) break;
						if(in[s]>>j&1)
							F[ss]+=f[s];
						break;
					case '#':
						if(x||y) break;
						if(!(in[s]>>j&1))
							F[ss]+=f[s];
						break;
					case '.':
						if(!x&&!y)
							F[ss|3<<j]+=f[s];
						else
						if(x&&y)
							F[ss]+=f[s];
						else{
							F[ss|1<<j]+=f[s];
							F[ss|2<<j]+=f[s];
						}
						break;
				}
			}
			for(int ss=0;ss<maxs;ss++) F[ss]%=P;
			int *tmp=f; f=F; F=tmp;
		}
		for(int s=0;s<maxs;s++) F[s]=s&1?0:f[s>>1];
		int *tmp=f; f=F; F=tmp;
	}
	printf("%d\n",f[0]);
}
