#include <cstdio>
template<typename Type,typename Compare,unsigned datasize>
struct Heap_map{
	#define size_t unsigned
	Type data[datasize]; size_t len; Compare cmp;
	Heap_map():len(0){
	}
	Heap_map(Type& x){
		data[x->inh=len=1]=x;
	}
	Heap_map(Type* begin,Type* end):len(end-begin){
		for(Type* i=begin;i<end;i++) data[i->inh=i-begin]=*i;
		for(size_t i=len>>1;i;i--)
			down(i);
	}
	Heap_map(Type begin,Type end){
		for(Type i=begin;i<end;++i) data[i->inh=++len]=begin;
	}
	#define swap(i,j) {\
		Type tmp=data[i];data[i]=data[j];data[j]=tmp;\
		data[i]->inh=i; data[j]->inh=j;\
	}
	void up(size_t i){
		for(size_t j;i>1&&cmp(data[j=i>>1],data[i]);i=j)
			swap(i,j);
	}
	void up(const Type x){ up(x->inh); }
	void down(size_t i){
		for(size_t j;(j=i<<1)<=len;i=j){
			if((j^1)<=len&&cmp(data[j],data[j^1])) j^=1;
			if(!cmp(data[i],data[j])) break;
			swap(i,j);
		}
	}
	void down(const Type x){ down(x->inh); }
	#undef swap
	void adjust(size_t i){
		up(i);
		down(i);
	}
	void adjust(const Type x){ adjust(x->inh); }
	void replace(const Type x,const Type y){
		data[y->inh=x->inh]=y; x->inh=0;
		adjust(y->inh);
	}
	void push(Type &x){
		data[x->inh=++len]=x;
		up(len);
	}
	void pop(){
		data[1]->inh=0;
		(data[1]=data[len--])->inh=1;
		down(1);
	}
	Type& top(){
		return data[1];
	}
	Type& operator[](const size_t i){
		return data[i];
	}
	bool empty(){
		return !len;
	}
	#undef size_t
};
#define P 3000007
int N,M,u,v,Ans;
struct query{
	int num; query *next; int inh;
} *i,a[100001],*t[P];
struct cmp{
	inline bool operator()(const query* a,const query* b){
		return a->next < b->next;
	}
};
Heap_map<query*,cmp,100001> h;
int main(){
	scanf("%u%u",&N,&M);
	for(i=a+1;i<=a+N;i++) scanf("%u",&i->num);
	for(i=a+N;i>a;i--){
		for(v=i->num%P;t[v]&&t[v]->num!=i->num;++v==P?v=0:0);
		i->next=t[v]?t[v]:a+N+1;
		t[v]=i;
	}
	for(i=a+1;i<=a+N;i++)
		for(v=i->num%P;t[v];t[v]=0,++v==P?v=0:0);
	for(i=a+1;i<=a+N;i++){
		for(v=i->num%P;t[v]&&t[v]->num!=i->num;++v==P?v=0:0);
		if(t[v]){
			h.replace(t[v],i);
			t[v]=i;
			continue;
		}
		if(h.len==M){
			for(u=h.top()->num%P;t[u]&&t[u]->num!=h.top()->num;++u==P?u=0:0);
			t[u]=0;
			h[1]=i;
			h.down(1);
		}
		else
			h.push(i);
		t[v]=i;
		Ans++;
	}
	printf("%u\n",Ans);
}
