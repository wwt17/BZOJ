#include <cstdio>
#include <algorithm>
using namespace std;
int n,m,Base,l,r;
struct data{
	char Cov; bool Not,f;
	int sum[2],l[2],r[2],Max[2];
	data():Cov(3),Not(false),f(0){
		sum[0]=sum[1]=0;
		l[0]=l[1]=0;
		r[0]=r[1]=0;
		Max[0]=Max[1]=0;
	}
	data& operator +(const data &b);
	inline void cover(const bool k);
	inline void reverse();
	inline void print();
} T[262144],tmp;
inline void update(const int i){
	if(i&&i<Base&&T[i].Cov==3&&!T[i].Not)
		T[i]=T[i<<1]+T[i<<1|1];
}
inline void down(const int i){
	if(T[i].Not){
		T[i<<1].reverse();
		T[i<<1|1].reverse();
		T[i].Not=false;
	}
	if(T[i].Cov!=3){
		T[i<<1].cover(T[i].Cov);
		T[i<<1|1].cover(T[i].Cov);
		T[i].Cov=3;
	}
}
void correct(int i){
	if(i<Base+n&&(i>>=1)) correct(i),down(i);
}
data& data::operator +(const data &b){
	tmp.sum[0]=sum[f]+b.sum[b.f];
	tmp.sum[1]=sum[!f]+b.sum[!b.f];
	tmp.l[0]=sum[!f]?l[f]:l[f]+b.l[b.f];
	tmp.l[1]=sum[f]?l[!f]:l[!f]+b.l[!b.f];
	tmp.r[0]=b.sum[!b.f]?b.r[b.f]:b.r[b.f]+r[f];
	tmp.r[1]=b.sum[b.f]?b.r[!b.f]:b.r[!b.f]+r[!f];
	tmp.Max[0]=max(max(Max[f],b.Max[b.f]),r[f]+b.l[b.f]);
	tmp.Max[1]=max(max(Max[!f],b.Max[!b.f]),r[!f]+b.l[!b.f]);
	return tmp;
}
inline void data::cover(bool k){
	Cov=k;
	Not=false;
	k^=f;
	Max[k]=l[k]=r[k]=sum[k]+=sum[!k];
	Max[!k]=l[!k]=r[!k]=sum[!k]=0;
}
inline void data::reverse(){
	if(Cov==3)
		Not^=1,f^=1;
	else
		cover(Cov^1);
}
int main(){
	scanf("%u%u",&n,&m);
	for(Base=1;Base<n;Base<<=1);
	for(int i=Base;i<Base+n;i++)
		getchar(),T[i].sum[T[i].f]=1,T[i].cover(getchar()&1);
	for(l=(Base-1)>>1,r=(Base+n)>>1;l^r^1;l>>=1,r>>=1)
		for(int i=l+1;i<r;i++) update(i);
	int opt,cnt;
	while(m--)
		switch(scanf("%u%u%u",&opt,&l,&r),opt){
			case 0:
			case 1:
				for(correct(l+=Base-1),correct(r+=Base+1);l^r^1;update(l>>=1),update(r>>=1)){
					if(!(l&1)) T[l^1].cover(opt);
					if(  r&1 ) T[r^1].cover(opt);
				}
				while(l>>=1) update(l);
				break;
			case 2:
				for(correct(l+=Base-1),correct(r+=Base+1);l^r^1;update(l>>=1),update(r>>=1)){
					if(!(l&1)) T[l^1].reverse();
					if(  r&1 ) T[r^1].reverse();
				}
				while(l>>=1) update(l);
				break;
			case 3:
				cnt=0;
				for(correct(l+=Base-1),correct(r+=Base+1);l^r^1;l>>=1,r>>=1){
					if(!(l&1)) cnt+=T[l^1].sum[!T[l^1].f];
					if(  r&1 ) cnt+=T[r^1].sum[!T[r^1].f];
				}
				printf("%u\n",cnt);
				break;
			case 4:
				data suml,sumr;
				for(correct(l+=Base-1),correct(r+=Base+1);l^r^1;l>>=1,r>>=1){
					if(!(l&1)) suml=suml+T[l^1];
					if(  r&1 ) sumr=T[r^1]+sumr;
				}
				printf("%u\n",(suml+sumr).Max[1]);
				break;
		}
}
