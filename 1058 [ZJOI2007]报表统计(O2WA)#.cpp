#include <cstdio>
#include <cstdlib>
#define inf 0x7fffffff
#define root seq
inline bool mini(int &a,const int b) { return a>b?(a=b,true):false; }
struct Splay *null,*base,*root;
void nullinit();
struct Splay {
	Splay *l,*r,*fa;
	int data,size;
	Splay():l(null),r(null),fa(null),data(0),size(1) {}
	Splay(int Data,Splay* Fa):l(null),r(null),fa(Fa),data(Data),size(1) {}
	inline Splay* updata() {
		size=l->size+r->size+1;
	}
	void zig() {
		Splay *x=this,*y=x->fa,*z=y->fa;
		x->fa=z; (y==z->l?z->l:z->r)=x;
		x->r->fa=y; y->l=x->r;
		x->r=y; y->fa=x;
		y->updata();
	}
	void zag() {
		Splay *x=this,*y=x->fa,*z=y->fa;
		x->fa=z; (y==z->l?z->l:z->r)=x;
		x->l->fa=y; y->r=x->l;
		x->l=y; y->fa=x;
		y->updata();
	}
	Splay* splay() { nullinit(); splay(root); }
	Splay* splayc() { nullinit(); splayc(this); }
	Splay* splayc(Splay* Root) { Splay* tmp=Root; return splay(tmp); }
	Splay* splay(Splay* &Root) {
		Splay *y,*z,*rf=Root->fa;
		while (fa!=rf) {
			y=fa; z=y->fa;
			if (z==null) this==y->l?zig():zag(); else
			if (y==z->l) this==y->l?(y->zig(),zig()):(zag(),zig());
			        else this==y->r?(y->zag(),zag()):(zig(),zag());
		}
		updata();
		return Root=this;
	}
	Splay* ins(int Data) {
		Splay *x=this,*y=fa;
		while (x!=null) {
			++x->size;
			y=x;
			x=(Data<=x->data?x->l:x->r);
		}
		x=(Data<=y->data?y->l:y->r)=new Splay(Data,y);
		return x->splay();
	}
	Splay* closest(int Data) {
		Splay *x=this,*ret;
		int dist=inf,_dist;
		while (x!=null) {
			if (_dist=x->data-Data,abs(_dist)<dist||_dist==-dist)
				ret=x,dist=abs(_dist);
			x=(Data<=x->data?x->l:x->r);
		}
		return ret;
	}
};
void nullinit() { null->l=null->r=null->fa=null; null->size=0; }
#define size 500050
int N,M,i,k,dist=inf,a[size],b[size],h[size<<1],hh[size<<1],t[size];
inline void swap(int i,int j) {
	int tmp=h[i]; h[i]=h[j]; h[j]=tmp;
	tmp=hh[i]; hh[i]=hh[j]; hh[j]=tmp;
	t[hh[i]]=i; t[hh[j]]=j;
}
void up(int i) {
	for (int j;i>1;i=j) {
		j=i>>1;
		if (h[i]<h[j]) swap(i,j);
		else break;
	}
}
void down(int i) {
	for (int j;i<=(h[0]>>1);i=j) {
		j=i<<1;
		if (j+1<=h[0]&&h[j+1]<h[j]) ++j;
		if (h[i]>h[j]) swap(i,j);
		else break;
	}
}
void chan(int i,int k) {
	hh[i]=0;
	h[i]=k;
	down(i);
	up(i);
}
void inse(int k,int i) {
	++h[0];
	h[h[0]]=k;
	hh[h[0]]=i;
	t[i]=h[0];
	up(h[0]);
}
int main() {
	freopen("form.in","r",stdin);
	freopen("form.out","w",stdout);
	scanf("%d%d",&N,&M);
	null=new Splay;
	nullinit();
	seq=null;
	for (i=1;i<=N;++i) {
		scanf("%d",&a[i]);
		b[i]=a[i];
		mini(dist,abs(seq->closest(b[i])->data-b[i]));
		seq->ins(b[i]);
	}
	h[0]=N-1;
	for (i=1;i<N;++i) h[i]=abs(b[i]-a[i+1]),hh[i]=t[i]=i;
	t[N]=0;
	for (i=N-1;i;--i) down(i);
	char opt[14];
	int cnt=0;
	while (M--) {
		scanf("%s",opt);
		switch (opt[4]) {
			case 'R': scanf("%d%d",&i,&k);
				chan(t[i],abs(b[i]-k));
				b[i]=k;
				if (i<N) inse(abs((b[i])-a[i+1]),i);
				mini(dist,abs(k-seq->closest(k)->data));
				seq->ins(k);
				break;
			case 'G': ++cnt; printf("%d\n",h[1]); break;
			case 'S': ++cnt; printf("%d\n",dist); break;
		}
	}
}

