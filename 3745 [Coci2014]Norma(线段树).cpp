#include <cstdio>
char meml;
const int N=500005,mo=(int)1e9;
#define add(x,y) (((x)+(y))%mo)
#define mul(x,y) ((long long)(x)*(y)%mo)
int n,L,R,D,ans;
struct data{
	int covx,covy,addz,len,x,y,z,xy,xz,yz,xyz;
	void coverx(int d){
		covx=d;
		x=mul(d,len);
		xy=mul(d,y);
		xz=mul(d,z);
		xyz=mul(d,yz);
	}
	void covery(int d){
		covy=d;
		y=mul(d,len);
		xy=mul(x,d);
		yz=mul(d,z);
		xyz=mul(xz,d);
	}
	void incz(int d){
		addz=add(addz,d);
		z=add(z,mul(len,d));
		xz=add(xz,mul(x,d));
		yz=add(yz,mul(y,d));
		xyz=add(xyz,mul(xy,d));
	}
} t[1<<20];
void down(int cur){
	data &p=t[cur],&a=t[cur<<1],&b=t[cur<<1|1];
	if(p.covx){
		a.coverx(p.covx);
		b.coverx(p.covx);
		p.covx=0;
	}
	if(p.covy){
		a.covery(p.covy);
		b.covery(p.covy);
		p.covy=0;
	}
	if(p.addz){
		a.incz(p.addz);
		b.incz(p.addz);
		p.addz=0;
	}
}
void update(int cur){
	data &p=t[cur],&a=t[cur<<1],&b=t[cur<<1|1];
	p.x=add(a.x,b.x);
	p.y=add(a.y,b.y);
	p.z=add(a.z,b.z);
	p.xy=add(a.xy,b.xy);
	p.xz=add(a.xz,b.xz);
	p.yz=add(a.yz,b.yz);
	p.xyz=add(a.xyz,b.xyz);
}
void calclen(int cur,int beg,int end){
	t[cur].len=end-beg;
	if(end-beg==1) return;
	int mid=beg+end>>1;
	calclen(cur<<1,beg,mid);
	calclen(cur<<1|1,mid,end);
}
void coverx(int cur,int beg,int end){
	if(R<=beg||L>=end) return;
	if(L<=beg&&R>=end)
		return t[cur].coverx(D);
	down(cur);
	int mid=beg+end>>1;
	coverx(cur<<1,beg,mid);
	coverx(cur<<1|1,mid,end);
	update(cur);
}
void covery(int cur,int beg,int end){
	if(R<=beg||L>=end) return;
	if(L<=beg&&R>=end)
		return t[cur].covery(D);
	down(cur);
	int mid=beg+end>>1;
	covery(cur<<1,beg,mid);
	covery(cur<<1|1,mid,end);
	update(cur);
}
void incz(int cur,int beg,int end){
	if(R<=beg||L>=end) return;
	if(L<=beg&&R>=end)
		return t[cur].incz(1);
	down(cur);
	int mid=beg+end>>1;
	incz(cur<<1,beg,mid);
	incz(cur<<1|1,mid,end);
	update(cur);
}
int a[N],last[N][2];
char memr;
int main(){
	scanf("%d",&n);
	calclen(1,0,n);
	for(R=1;R<=n;R++){
		scanf("%d",&D);
		a[R]=D;
		for(L=R-1;L&&a[L]>D;L=last[L][0]);
		last[R][0]=L;
		coverx(1,0,n);
		for(L=R-1;L&&a[L]<D;L=last[L][1]);
		last[R][1]=L;
		covery(1,0,n);
		L=0;
		incz(1,0,n);
		ans=add(ans,t[1].xyz);
	}
	printf("%d\n",ans);
}
