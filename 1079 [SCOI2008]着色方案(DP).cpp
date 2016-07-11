//f[a,b,c,d,e,x] <= f[a-1,b,c,d,e,0],f[a+1,b-1,c,d,e,1],f[a,b+1,c-1,d,e,2],...
#include <cstdio>
const int P=1000000007;
int k,ci,sum[5],max[6],i[5],f[16][16][16][16][16][5];
void work(int d){
	if(d==-1){
		int x,y;
		for(x=0;x<5;x++){
			int &ans=f[i[0]][i[1]][i[2]][i[3]][i[4]][x];
			for(y=0;y<5;y++) if(i[y]){
				i[y]--;
				if(y) i[y-1]++;
				ans=(ans+(long long)f[i[0]][i[1]][i[2]][i[3]][i[4]][y]*(i[y]+(y!=x-1)))%P;
				i[y]++;
				if(y) i[y-1]--;
			}
			//printf("f[%u,%u,%u,%u,%u][%u]=%u\n",i[0],i[1],i[2],i[3],i[4],x,ans);
		}
		return;
	}
	for(i[d]=0;i[d]<=max[d];i[d]++)
		work(d-1);
}
int main(){
	scanf("%u",&k);
	while(k--) scanf("%u",&ci),sum[--ci]++;
	for(int d=4;d>=0;d--) max[d]=max[d+1]+sum[d],f[0][0][0][0][0][d]=1;
	work(4);
	printf("%u\n",f[sum[0]][sum[1]][sum[2]][sum[3]][sum[4]][0]);
}
