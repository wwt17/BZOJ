#define SIZE 301
#define C 101
int N,M,i,j,k,Q,x,y,yy,c,xl,xr,yl,yr,ans,t[SIZE][SIZE][C],a[SIZE][SIZE];
char opt;
inline int Query(int x,int y){
	int ret=0;
	for(;x;x-=x&-x)
		for(yy=y;yy;yy-=yy&-yy)
			ret+=t[x][yy][c];
	return ret;
}
int main(){
	scanf("%u%u",&N,&M);
	for(i=1;i<=N;++i){
		for(j=1;j<=M;++j){
			scanf("%u",&a[i][j]);
			t[i][j][a[i][j]]++;
			if((k=j+(j&-j))<=M)
				for(c=1;c<C;++c)
					t[i][k][c]+=t[i][j][c];
		}
	}
	for(i=1;i<=N;++i)
		if((k=i+(i&-i))<=M)
			for(j=1;j<=M;++j)
				for(c=1;c<C;++c)
					t[k][j][c]+=t[i][j][c];
	scanf("%u",&Q);
	while(Q--)
		if(scanf("\n"),getchar()&1){
			scanf("%u%u%u",&i,&j,&c);
			for(x=i;x<=N;x+=x&-x)
				for(yy=j;yy<=M;yy+=yy&-yy)
					t[x][yy][a[i][j]]--,
					t[x][yy][c]++;
			a[i][j]=c;
		}else{
			scanf("%u%u%u%u%u",&xl,&xr,&yl,&yr,&c); xl--; yl--;
			printf("%u\n",Query(xr,yr)-Query(xl,yr)-Query(xr,yl)+Query(xl,yl));
		}
}
