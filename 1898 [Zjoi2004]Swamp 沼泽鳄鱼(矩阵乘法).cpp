#include <cstdio>
const int N=50,P=10000;
int n,m,s,e,k,nf;
bool a[N][N],flag[N],A,O;
int b[13][N][N],ans[2][N],opt[2][N][N];
struct fish{
	int t,p[4];
} f[20];
void mulopt(){
	for(int i=0;i<n;i++)
		for(int j=0;j<n;j++){
			opt[!O][i][j]=0;
			for(int k=0;k<n;k++)
				opt[!O][i][j]=(opt[!O][i][j]+opt[O][i][k]*opt[O][k][j])%P;
		}
	O^=1;
}
void mulans(){
	for(int j=0;j<n;j++){
		ans[!A][j]=0;
		for(int i=0;i<n;i++)
			ans[!A][j]=(ans[!A][j]+ans[A][i]*opt[O][i][j])%P;
	}
	A^=1;
}
int main(){
	scanf("%d%d%d%d%d",&n,&m,&s,&e,&k);
	while(m--){
		static int x,y; scanf("%d%d",&x,&y);
		a[x][y]=a[y][x]=1;
	}
	scanf("%d",&nf);
	for(int i=0;i<nf;i++){
		scanf("%d",&f[i].t);
		for(int j=0;j<f[i].t;j++) scanf("%d",f[i].p+j);
	}
	for(int x=0;x<n;x++) b[0][x][x]=1;
	for(int r=1;r<=12;r++){
		for(int x=0;x<n;x++) flag[x]=0;
		for(int i=0;i<nf;i++) flag[f[i].p[r%f[i].t]]=1;
		for(int z=0;z<n;z++) if(!flag[z])
			for(int x=0;x<n;x++)
				for(int y=0;y<n;y++) if(a[y][z])
				 b[r][x][z]=(b[r][x][z]+b[r-1][x][y])%P;
	}
	for(int x=0;x<n;x++)
		for(int y=0;y<n;y++)
			opt[O][x][y]=b[12][x][y];
	ans[A][s]=1;
	for(int t=k/12;t;t>>=1,mulopt())
		if(t&1) mulans();
	for(int x=0;x<n;x++)
		for(int y=0;y<n;y++)
			opt[O][x][y]=b[k%12][x][y];
	mulans();
	printf("%d\n",ans[A][e]);
}
