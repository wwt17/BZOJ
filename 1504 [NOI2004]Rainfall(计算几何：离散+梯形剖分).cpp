#include <cstdio>
#include <cmath>
#include <algorithm>
using namespace std;
typedef double db;
const int N=12;
int n,cnt;
db w,tott,volume,ans,mid,tim[512],*newtim=tim,loc[512][N][2],tmp[N*N*4],*newtmp;
struct Line{
	db k,b; int w;
} line[N*2],*newline;
bool cmp(const Line &x,const Line &y){
	return x.k*mid+x.b<y.k*mid+y.b;
}
struct Unb{
	db x,l,v;
	void addtim(){
		if(!v) return;
		db xx=x,vv=v,t=0,tt;
		for(;;){
			if(vv>0)
				tt=t+(w-xx-l)/vv;
			else
				tt=t-xx/vv;
			if(tt>=tott) return;
			*newtim++=tt;
			xx+=(tt-t)*vv;
			vv*=-1;
			t=tt;
		}
	}
	void addloc(int i){
		if(!v){
			for(int j=0;j<cnt;j++)
				loc[j][i][0]=x,loc[j][i][1]=v;
			return;
		}
		db xx=x,vv=v,t=0,tt;
		for(int j=0;j<cnt-1;){
			if(vv>0)
				tt=t+(w-xx-l)/vv;
			else
				tt=t-xx/vv;
			for(;j<cnt&&tim[j]<tt-1e-7;j++)
				loc[j][i][0]=xx+(tim[j]-t)*vv,
				loc[j][i][1]=vv;
			if(tt>=tott) return;
			xx+=(tt-t)*vv;
			vv*=-1;
			t=tt;
		}
	}
} unb[N];
int main(){
	scanf("%d%lf%lf%lf",&n,&w,&tott,&volume);
	*newtim++=0;
	*newtim++=tott;
	for(int i=0;i<n;i++){
		scanf("%lf%lf%lf",&unb[i].x,&unb[i].l,&unb[i].v);
		if(unb[i].l==w) unb[i].v=0;
		unb[i].addtim();
	}
	cnt=newtim-tim;
	sort(tim,newtim);
	for(int i=0;i<n;i++) unb[i].addloc(i);
	for(int j=0;j<cnt-1;j++){
		newline=line;
		*newline++=(Line){0,0,0};
		*newline++=(Line){0,w,0};
		for(int i=0;i<n;i++){
			*newline++=(Line){loc[j][i][1],loc[j][i][0]-loc[j][i][1]*tim[j],1};
			*newline++=(Line){loc[j][i][1],loc[j][i][0]-loc[j][i][1]*tim[j]+unb[i].l,-1};
		}
		newtmp=tmp;
		*newtmp++=tim[j];
		*newtmp++=tim[j+1];
		for(int i=0;i<newline-line;i++)
			for(int ii=i+1;ii<newline-line;ii++)
				if(abs(line[i].k-line[ii].k)>1e-8){
					db t=(line[ii].b-line[i].b)/(line[i].k-line[ii].k);
					if(t>tim[j]&&t<tim[j+1])
						*newtmp++=t;
				}
		sort(tmp,newtmp);
		for(int jj=0;jj<newtmp-tmp-1;jj++){
			mid=(tmp[jj]+tmp[jj+1])/2;
			sort(line,newline,cmp);
			int cov=0;
			for(int i=0;i<newline-line-1;i++){
				cov+=line[i].w;
				if(!cov) ans+=(tmp[jj+1]-tmp[jj])*(line[i+1].k*mid+line[i+1].b-line[i].k*mid-line[i].b);
			}
		}
	}
	printf("%.2lf\n",ans*volume);
}
