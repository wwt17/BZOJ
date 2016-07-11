#include <cstdio>
#include <cstring>
#include <cmath>
const double eps=1e-8;
const int inf=100000;
template<class T>
inline void tension(T &a,const T b){
	if(b<a) a=b;
}
int m,n,i,j,k;
struct point{
	double x,y;
	inline void read(){
		scanf("%lf%lf%lf",&x,&x,&y);
	}
	bool operator!=(const point &B){
		return x!=B.x||y!=B.y;
	}
} rec[500],ned[500];
inline double cross(point &A,point &B,point &C){
	return (B.x-A.x)*(C.y-A.y)-(B.y-A.y)*(C.x-A.x);
}
int dist[500][500];
int main(){
	scanf("%u%u",&m,&n);
	for(i=0;i<m;i++) rec[i].read();
	for(i=0;i<n;i++) ned[i].read();
	for(i=0;i<m;i++)
		for(j=0;j<m;j++){
			if(rec[i]!=rec[j])
				for(k=0;k<n;k++){
					double s=cross(rec[i],rec[j],ned[k]);
					if(!(s<-eps||s<eps&&
					fabs(
					fabs(rec[i].x-ned[k].x)+
					fabs(rec[j].x-ned[k].x)-
					fabs(rec[i].x-rec[j].x))
					<eps)) break;
				}
			else
				for(k=0;k<n;k++)
					if(rec[i]!=ned[k]) break;
			if(k<n) dist[i][j]=inf; else
				dist[i][j]=1;
		}
	int Ans=inf;
	for(k=0;k<m;k++)
		for(i=0;i<m;i++) if(dist[i][k]!=inf)
			for(j=0;j<m;j++) if(dist[k][j]!=inf)
				tension(dist[i][j],dist[i][k]+dist[k][j]);
	for(i=0;i<m;i++)
		for(j=0;j<=i;j++)
			tension(Ans,i!=j?dist[i][j]+dist[j][i]:dist[i][j]);
	if(Ans==inf) puts("-1"); else printf("%u\n",Ans);
}
