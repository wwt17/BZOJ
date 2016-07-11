#include <cstdio>
inline void read(int &a){
	char c; while((c=getchar())<'0'||c>'9'); a=c-'0';
	while((c=getchar())>='0'&&c<='9') a=a*10+c-'0';
}
template<typename Type,typename Compare,int datasize>
struct Heap{
	#define size_t unsigned
	Type data[datasize+1]; size_t len; Compare cmp;
	Heap():len(0){}
	#define swap(i,j) {\
		Type tmp=data[i];data[i]=data[j];data[j]=tmp;\
		data[i]->inh=i;data[j]->inh=j;\
	}
	void up(size_t i){
		for(size_t j;i>1&&cmp(data[j=i>>1],data[i]);i=j)
			swap(i,j);
	}
	void down(size_t i){
		for(size_t j;(j=i<<1)<=len;i=j){
			if((j^1)<=len&&cmp(data[j],data[j^1])) j^=1;
			if(!cmp(data[i],data[j])) break;
			swap(i,j);
		}
	}
	void push(const Type &x){
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
	inline bool empty(){
		return !len;
	}
	#undef size_t
};
struct node;
struct edge{
	node* ed; edge* next;
} E[2000000],*newE=E;
struct node{
	edge* son; int col; short inh;
} V[10001];
struct cmp{
	bool operator()(const node* a,const node* b){
		return a->col < b->col;
	}
};
Heap<node*,cmp,10000> h;
int main(){
	int N,M,a,b,i,Ans=0; read(N),read(M);
	while(M--){
		read(a),read(b);
		*newE=(edge){V+b,V[a].son}; V[a].son=newE++;
		*newE=(edge){V+a,V[b].son}; V[b].son=newE++;
	}
	node *u,*v;
	for(i=1;i<=N;i++) h.push(V+i);
	while(!h.empty()){
		u=h.top(); h.pop();
		if(Ans<u->col) Ans=u->col;
		for(edge* e=u->son;e;e=e->next)
			if((v=e->ed)->inh) v->col++,h.up(v->inh);
	}
	printf("%u\n",++Ans);
}
