#include <cstdio>
#include <cstdlib>
#define Sp system("pause")
#define sizeN 15
#define size 1594323
#define llu unsigned long long
#define rep(i,k) for(i=0;i<k;++i)
llu p3[sizeN],f[2][size],Val;
int goin[2][size],*len[2],s,x,y,t,o[sizeN],stack[sizeN],stop;
int N,M,i,j,F; char map[sizeN][sizeN]; int ei,ej;
inline void ins(int p){
	if(!f[F][p])
		*(len[F]++)=p;
	f[F][p]+=Val;
}
inline void write(int k){
	/*
	for(int c=M+1;c;--c){
		switch(k%3){
			case 0: putchar('#'); break;
			case 1: putchar('('); break;
			case 2: putchar(')'); break;
		}
		k/=3;
	}
	*/
}
inline void print(){
	/*
	printf("i=%d j=%d\n",i,j);
	printf("last:\n");
	for(int k=0;k<p3[M+1];++k) printf(" %I64d",f[!F][k]); putchar('\n');
	for(int*k=goin[!F];k<len[!F];++k) putchar(' '),write(*k); putchar('\n');
	printf("pres:\n");
	for(int k=0;k<p3[M+1];++k) printf(" %I64d",f[F][k]); putchar('\n');
	for(int*k=goin[F];k<len[F];++k) putchar(' '),write(*k); putchar('\n');
	Sp;
	*/
}
int main(){
	freopen("city.in","r",stdin);
	freopen("city.out","w",stdout);
	scanf("%d%d",&N,&M);
	for(p3[0]=1,j=1;j<=M+1;++j) p3[j]=p3[j-1]*3;
	for(i=0;i<N;++i){
		scanf("%s",map[i]);
		for(j=0;j<M;++j)
			if(map[i][j]=='.') ei=i,ej=j;
	}
	len[F]=goin[F];
	Val=1;ins(0);
	for(i=0;i<N;++i){
		for(j=0;j<M;++j){
			F^=1; len[F]=goin[F];
			while(goin[!F]<len[!F]--){
				s=*len[!F];
				Val=f[!F][s];
				//write(s); putchar('\n');
				if(!j)
					if(s<p3[M]) s*=3; else
						{ f[!F][*len[!F]]=0; /*printf("exit:\n");print();*/ continue; }
				for(int c=0,z=s;c<=M;++c,z/=3)
					switch(z%3){
						case 1: stack[++stop]=c; break;
						case 2: o[o[c]=stack[stop--]]=c; break;
					}
				x=s/p3[j]%3;
				y=s/p3[j+1]%3;
				switch (map[i][j]){
					case '#': if(!x&&!y) ins(s); break;
					case '-': if( x&&!y) ins(s+x*p3[j]*2); break;
					case '|': if(!x&& y) ins(s-y*p3[j]*2); break;
					case '.': if(!x&&!y){ins(s+p3[j]*7); break;}
					          if(    !y){ins(s),ins(s+x*p3[j]*2);break;}
					          if(!x    ){ins(s),ins(s-y*p3[j]*2);break;}
					s-=x*p3[j]+y*p3[j+1];
					if(x==2&&y==1 || x==1&&y==2 && i==ei&&j==ej) ins(s);
					if(x==1&&y==1){ins(s-p3[o[j+1]]);break;}
					if(x==2&&y==2){ins(s+p3[o[j]]);break;}
				}
				f[!F][*len[!F]]=0;
				print();
			}
		}
	}
	printf("%I64d\n",f[F][0]); scanf("%d"); return 0;
}
