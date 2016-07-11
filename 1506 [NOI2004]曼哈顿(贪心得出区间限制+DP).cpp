#include <cstdio>
#include <algorithm>
using namespace std;
const int M=12,N=105,K=105,inf=(int)1e9;
int m,n,k;
char initx[M],inity[N];
int costx[M],costy[N];
bool chanx[M];
int f[K][K];
struct query{
	int x1,y1,x2,y2;
	void read(){
		scanf("%d%d%d%d",&x1,&y1,&x2,&y2);
		x1--;
		x2--;
	}
} seq[K];
struct Seg{
	int l,r;
} seg[2][K*2],*newseg[2];
inline bool cmp(const Seg &a,const Seg &b){
	return a.r<b.r||a.r==b.r&&a.l>b.l;
}
int work(){
	for(int i=0;i<k;i++)
		if(seq[i].x1==seq[i].x2)
			if(seq[i].y1!=seq[i].y2&&chanx[seq[i].x1]!=(seq[i].y1>seq[i].y2)) return inf;
	for(int t=0;t<=1;t++){
		newseg[t]=seg[t];
		for(int i=0;i<k;i++) if(t==0?seq[i].x1<seq[i].x2:seq[i].x1>seq[i].x2){
			if(seq[i].y1==seq[i].y2){
				*newseg[t]++=(Seg){seq[i].y1,seq[i].y2};
				continue;
			}
			bool flag=seq[i].y1>seq[i].y2;
			if(chanx[seq[i].x1]==flag){
				if(chanx[seq[i].x2]==flag)
					*newseg[t]++=(Seg){seq[i].y1,seq[i].y2};
				else
					*newseg[t]++=(Seg){seq[i].y2,seq[i].y2};
			}
			else{
				if(chanx[seq[i].x2]==flag)
					*newseg[t]++=(Seg){seq[i].y1,seq[i].y1};
				else{
					bool ok=0;
					for(int ii=seq[i].x1;ii<=seq[i].x2;ii++) if(chanx[ii]==flag) ok=1;
					for(int ii=seq[i].x2;ii<=seq[i].x1;ii++) if(chanx[ii]==flag) ok=1;
					if(!ok) return inf;
					*newseg[t]++=(Seg){seq[i].y1,seq[i].y1};
					*newseg[t]++=(Seg){seq[i].y2,seq[i].y2};
				}
			}
		}
		for(Seg *p=seg[t];p<newseg[t];p++) if(p->l>p->r) swap(p->l,p->r);
		sort(seg[t],newseg[t],cmp);
		Seg *tmp=seg[t];
		for(Seg *i=seg[t];i<newseg[t];i++){
			if(tmp>seg[t]&&i->r<=tmp[-1].r) continue;
			*tmp++=*i;
		}
		newseg[t]=tmp;
		for(;tmp>seg[t];tmp--) tmp[0]=tmp[-1];
	}
	for(int i=0;i<=newseg[0]-seg[0];i++)
		for(int j=0;j<=newseg[1]-seg[1];j++)
			f[i][j]=inf;
	f[0][0]=0;
	for(int k=1,x=0,y=0,xx=0,yy=0;k<=n;k++){
		for(;x<newseg[0]-seg[0]&&seg[0][x+1].r<k;x++);
		for(;y<newseg[1]-seg[1]&&seg[1][y+1].r<k;y++);
		for(;xx<=newseg[0]-seg[0]&&seg[0][xx+1].l<=k;xx++);
		for(;yy<=newseg[1]-seg[1]&&seg[1][yy+1].l<=k;yy++);
		for(int i=xx;i>=0;i--)
			for(int j=yy;j>=0;j--)
				f[i][j]=min(f[i][j],
					min(
					f[min(i,x)][j]+(inity[k]==0?0:costy[k]),
					f[i][min(j,y)]+(inity[k]==1?0:costy[k])));
	}
	return f[newseg[0]-seg[0]][newseg[1]-seg[1]];
}
int main(){
	scanf("%d%d",&m,&n);
	scanf("%s",initx);
	for(int i=0;i<m;i++) initx[i]=initx[i]=='W';
	scanf("%s",inity+1);
	for(int j=1;j<=n;j++) inity[j]=inity[j]=='N';
	for(int i=0;i<m;i++) scanf("%d",&costx[i]);
	for(int j=1;j<=n;j++) scanf("%d",&costy[j]);
	scanf("%d",&k);
	for(int i=0;i<k;i++) seq[i].read();
	int ans=inf;
	for(int sta=0;sta<1<<m;sta++){
		int tot=0;
		for(int i=0;i<m;i++){
			chanx[i]=sta>>i&1;
			if(chanx[i]!=initx[i])
				tot+=costx[i];
		}
		tot+=work();
		if(tot<ans) ans=tot;
	}
	if(ans<inf){
		puts("possible");
		printf("%d\n",ans);
	}
	else
		puts("impossible");
}
