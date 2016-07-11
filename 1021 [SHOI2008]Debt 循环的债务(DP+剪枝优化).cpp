#include <cstdio>
const int Kinds=6,Total=1005,value[Kinds]={100,50,20,10,5,1},gcdval[Kinds]={100,50,10,10,5,1};
int x[3],total,a[3][Kinds],sum[2][3],f[Kinds+1][Total][Total];
inline void mini(int &a,const int b){
	if(!a||b<a) a=b;
}
int main(){
	for(int i=0;i<3;i++) scanf("%d",&x[i]);
	for(int i=0;i<3;i++){
		for(int j=0;j<Kinds;j++)
			scanf("%d",&a[i][j]),sum[0][i]+=a[i][j]*value[j];
		total+=sum[0][i];
	}
	sum[1][0]=sum[0][0]+x[2]-x[0];
	sum[1][1]=sum[0][1]+x[0]-x[1];
	sum[1][2]=sum[0][2]+x[1]-x[2];
	if(sum[1][0]<0||sum[1][1]<0||sum[1][2]<0)
		return puts("impossible"),0;
	f[Kinds][sum[0][0]][sum[0][1]]=1;
	for(int k=Kinds-1;k>=0;k--)
		for(int i=sum[1][0]%gcdval[k];i<=total;i+=gcdval[k])
			for(int j=sum[1][1]%gcdval[k];i+j<=total;j+=gcdval[k]) if(f[k+1][i][j]){
				for(int p=0;p<=a[0][k];p++)
					for(int q=0;p+q<=a[0][k];q++)
						mini(f[k][i-(p+q)*value[k]][j+p*value[k]],f[k+1][i][j]+p+q);
				for(int p=0;p<=a[1][k];p++)
					for(int q=0;p+q<=a[1][k];q++)
						mini(f[k][i+p*value[k]][j-(p+q)*value[k]],f[k+1][i][j]+p+q);
				for(int p=0;p<=a[2][k];p++)
					for(int q=0;p+q<=a[2][k];q++)
						mini(f[k][i+p*value[k]][j+q*value[k]],f[k+1][i][j]+p+q);
				for(int p=0;p<=a[1][k];p++)
					for(int q=0;q<=a[2][k];q++)
						mini(f[k][i+(p+q)*value[k]][j-p*value[k]],f[k+1][i][j]+p+q);
				for(int p=0;p<=a[0][k];p++)
					for(int q=0;q<=a[2][k];q++)
						mini(f[k][i-p*value[k]][j+(p+q)*value[k]],f[k+1][i][j]+p+q);
				for(int p=0;p<=a[0][k];p++)
					for(int q=0;q<=a[1][k];q++)
						mini(f[k][i-p*value[k]][j-q*value[k]],f[k+1][i][j]+p+q);
			}
	if(f[0][sum[1][0]][sum[1][1]])
		printf("%d\n",f[0][sum[1][0]][sum[1][1]]-1);
	else
		puts("impossible");
}
