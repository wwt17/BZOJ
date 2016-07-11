#include <cstdio>
#include <cmath>
#define sizeT 232000
unsigned N,i,M,x,l,r,Base;
struct Treetype{
	unsigned long long s;
	unsigned f;
} t[sizeT];
unsigned long long Sum(){
	unsigned long long ret=0;
	for(l+=Base-1,r+=Base+1;l^r^1;l>>=1,r>>=1){
		if(!(l&1)) ret+=t[l^1].s;
		if(  r&1 ) ret+=t[r^1].s;
	}
	return ret;
}
void Modify(const unsigned i){
	if(!t[i].f) return;
	if(i>Base){
		t[i].s=(unsigned)sqrt(t[i].s);
		t[i].f=t[i].s>1;
	}else{
		Modify(i<<1);
		Modify(i<<1^1);
	}
	t[i>>1].s=t[i].s+t[i^1].s;
	t[i>>1].f=t[i].f||t[i^1].f;
}
inline void update(const unsigned i){
	t[i].s=t[i<<1].s+t[i<<1^1].s;
	t[i].f=t[i<<1].f||t[i<<1^1].f;
}
void Modify(){
	for(l+=Base-1,r+=Base+1;l^r^1;update(l>>=1),update(r>>=1)){
		if(!(l&1)) Modify(l^1);
		if(  r&1 ) Modify(r^1);
	}
	while(l>>=1) update(l);
}
int main(){
	scanf("%u",&N);
	for(Base=1;Base<N;Base<<=1); --Base;
	for(i=Base+1;i<=Base+N;++i) scanf("%u",&t[i].s),t[i].f=t[i].s>1;
	for(l=Base+1,r=Base+N;l||r;l>>=1,r>>=1)
		for(i=l;i<=r;++i){
			t[i>>1].s+=t[i].s;
			t[i>>1].f|=t[i].f;
		}
	scanf("%u",&M);
	while(M--){
		scanf("%u%u%u",&x,&l,&r);
		if(x==1)
			printf("%llu\n",Sum());
		else
			Modify();
	}
}
