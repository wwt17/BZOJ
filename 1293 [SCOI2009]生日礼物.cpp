#include <cstdio>
#include <cstring>
#define size 1000100
#define INF 0xFFFFFFFF
//#define unsigned int
#define int unsigned
inline void maxi(int &a,const int b){if(a<b)a=b;}
inline void mini(int &a,const int b){if(a>b)a=b;}
inline void read(int &a){
	char c;while(c=getchar(),c<'0'||'9'<c);a=c-'0';
	while(c=getchar(),'0'<=c&&c<='9') a=a*10+c-'0';
}

template<typename Type,typename Compare,int datasize>
struct heap{
	Type data[datasize]; unsigned len; Compare cmp;
	heap():len(0){memset(data,0,sizeof(data));};
	#define swap(i,j) {Type tmp=data[i];data[i]=data[j];data[j]=tmp;}
	void up(unsigned i){
		for(unsigned j;i>1&&cmp(data[j=i>>1],data[i]);i=j)
			swap(i,j);
	}
	void down(unsigned i){
		for(unsigned j;(j=i<<1)<=len;i=j){
			if((j^1)<=len&&cmp(data[j],data[j^1])) j^=1;
			if(!cmp(data[i],data[j])) break;
			swap(i,j);
		}
	}
	void push(const Type &x){
		data[++len]=x;
		up(len);
	}
	Type& top(){
		return data[1];
	}
};

struct cmp{
	bool operator()(const unsigned* a,const unsigned* b){return *a>*b;}
};

int N,K,k,f[size],*F=f,Ti,*kind[60],Ans=INF;
#undef int
int main(){
	#define int unsigned
	read(N),read(K);
	heap<unsigned*,cmp,200> Min;
	int max=0,*min;
	for(k=0;k<K;++k){
		read(Ti);
		read(*F);
		Min.push(F);
		maxi(max,*F);
		F++;
		while(--Ti) read(*F++);
		*F++=INF;
	}
	while(N--){
		min=Min.top();
		mini(Ans,max-*min);
		maxi(max,*++Min.top());
		Min.down(1);
		if(max==INF) break;
	}
	printf("%u\n",Ans);
}
