#include <cstdio>
#include <cstring>
#include <cmath>
#include <algorithm>
#include <list>
#include <complex>
using namespace std;

int n,m,k,base;
char type,sn[61000],sm[61000];

const double pi=acos(-1);
typedef complex<double> comp;

comp w[2][1<<17],a[1<<17];
int rev[1<<17],b[(1<<17)+100];

void init(){
	for(int i=0;i<base;i++){
		int t=0;
		for(int j=1;j<base;j<<=1) (t<<=1)|=bool(i&j);
		rev[i]=t;
	}
	for(int i=0;i<base;i++){
		double x=cos(2*pi*i/base),y=sin(2*pi*i/base);
		w[0][i]=comp(x,y);
		w[1][i]=comp(x,-y);
	}
}

void FFT(comp *a,int f){
	for(int i=0;i<base;i++) if(i<rev[i]) swap(a[i],a[rev[i]]);
	for(int i=1;i<base;i<<=1)
		for(int j=0;j<base;j+=i<<1)
			for(int k=0,l=0,d=base/i/2;k<i;k++,l+=d){
				comp x=a[j+k],y=w[f][l]*a[j+i+k];
				a[j+k]=x+y;
				a[j+i+k]=x-y;
			}
	if(f) for(int i=0;i<base;i++) a[i]/=base;
}

bool flag[105][105];

const int dx[4]={-1,1,0,0},dy[4]={0,0,-1,1};
int stamp,used[105][105],X[105][105],Y[105][105];
bool extend(int x,int y){
	if(!x&&!y) return true;
	for(int d=0;d<4;d++){
		int xx=x+dx[d],yy=y+dy[d];
		if(xx<=0||xx>n||yy<=0||yy>m||flag[xx-1][yy-1]||used[xx][yy]==stamp) continue;
		used[xx][yy]=stamp;
		if(extend(X[xx][yy],Y[xx][yy])){
			X[xx][yy]=x;
			Y[xx][yy]=y;
			return true;
		}
	}
	return false;
}

struct seq{
	int len,q[600000],f[1<<12*2];
} mem[2],*f=mem,*F=mem+1;
void ins(const int s,const int a){
	if(!F->f[s]) F->q[F->len++]=s;
	if(a>F->f[s]) F->f[s]=a;
}

int main(){
	scanf("%s%s%d %c",sm,sn,&k,&type);
	if(type=='B'){
		int l=strlen(sn);
		for(int i=0;i<l;i++) a[i]=sn[l-1-i]-'0';
		for(base=1;base<l*2;base<<=1);
		init();
		FFT(a,0);
		for(int i=0;i<base;i++) a[i]=a[i]*a[i];
		FFT(a,1);
		int x=0;
		for(int i=0;i<base;i++){
			x+=round(a[i].real());
			b[i]=x%10;
			x/=10;
		}
		l=base;
		while(x){
			b[l++]=x%10;
			x/=10;
		}
		for(int i=0;i<l;i++)
			if(b[i]==0)
				b[i]=9;
			else{
				b[i]--;
				break;
			}
		x=0;
		for(int i=l-1;i>=0;i--){
			x=x*10+b[i];
			b[i]=x/3;
			x%=3;
		}
		while(l&&!b[l-1]) l--;
		for(int i=l-1;i>=0;i--) printf("%d",b[i]); puts("");
	}
	else{
		sscanf(sn,"%d",&n);
		sscanf(sm,"%d",&m);
		for(int i=0;i<k;i++){
			int x,y; scanf("%d%d",&x,&y);
			flag[--x][--y]=1;
		}
		if(type=='A'){
			int ans=0;
			for(int i=0;i<n;i++)
				for(int j=0;j<m;j++) if((i+j&1)&&!flag[i][j]){
					stamp++;
					ans+=extend(i+1,j+1);
				}
			printf("%d\n",ans);
		}
		else
		if(type=='C'){
			ins(0,100);
			swap(f,F);
			for(int i=0;i<n;i++,swap(f,F)){
				for(int j=0;j<m;j++,swap(f,F)){
					for(int s;f->len;f->f[s]=0){
						s=f->q[--f->len];
						int a=s>>j*2&3,b=s>>(j+1)*2&3;
						if(flag[i][j]){
							if(a==0&&b==0)
								ins(s,f->f[s]);
							continue;
						}
						int t=s^(a<<j*2)^(b<<(j+1)*2);
						if(a<b) swap(a,b);
						if(b){
							if(a==2&&b==2)
								ins(t,f->f[s]-1);
							continue;
						}
						switch(a){
							case 0:
								ins(t,f->f[s]);
								ins(t|(0+2*4)<<j*2,f->f[s]+1);
								ins(t|(1+1*4)<<j*2,f->f[s]+1);
								ins(t|(2+0*4)<<j*2,f->f[s]+1);
								break;
							case 1:
								ins(t,f->f[s]);
								break;
							case 2:
								ins(t|(0+1*4)<<j*2,f->f[s]);
								ins(t|(1+0*4)<<j*2,f->f[s]);
								break;
						}
					}
					continue;
					printf("i=%d j=%d",i,j);
					for(int l=0;l<F->len;l++){
						printf(" (");
						for(int k=0;k<m+1;k++) printf("%d",F->q[l]>>k*2&3);
						printf(" %d)",F->f[F->q[l]]-100);
					}
					puts("");
				}
				for(int s;f->len;f->f[s]=0){
					s=f->q[--f->len];
					if(s<1<<m*2) ins(s<<2,f->f[s]);
				}
			}
			printf("%d\n",f->f[0]-100);
		}
	}
}
