#include <cstdio>
#include <algorithm>
struct node;
struct edge{
	node* ed; edge* next;
	edge(node* _ed,edge* _next):
		ed(_ed),next(_next){}
};
int cnt=0;
struct node{
	edge* son; bool flag; node *belong,*_belong;
	node():son(NULL),flag(false),belong(this),_belong(this){
	}
	inline edge* addedge(node* ed){
		return son=new edge(ed,son);
	}
	void DFS(){
		if(flag) return; flag=true; cnt++;
		for(edge* e=son;e;e=e->next)
			e->ed->DFS();
	}
	void correct(){
		if(this==belong) return;
		belong->correct();
		belong=belong->belong;
	}
	inline bool connected_with(node* v){
		correct();
		v->correct();
		return belong==v->belong;
	}
	inline bool link_to(node* v){
		if(connected_with(v)) return false;
		belong->belong=v->belong;
		return true;
	}
} V[101];
struct bedge{
	edge* e[2]; int c;
	bedge(node* a,node* b,int _c):c(_c){
		e[0]=a->addedge(b);
		e[1]=b->addedge(a);
	}
	inline bool connected(){
		return e[0]->ed->connected_with(e[1]->ed);
	}
	inline bool link(){
		return e[0]->ed->link_to(e[1]->ed);
	}
};
inline bool cmp(const bedge* a,const bedge* b){
	return a->c < b->c;
}
int n,m,i,j,a,b,c,sum,ans=1;
bedge *t[1000]; bool chose[1000];
#define copy() for(node* v=V+1;v<=V+n;v++) v->belong=v->_belong;
#define recopy() for(node* v=V+1;v<=V+n;v++) v->_belong=v->belong;
void search(const int now){
	if(now==i){
		for(int k=j;k<i;k++) if(chose[k]&&!t[k]->link())
			{ copy(); return; }
		cnt++;
		copy(); return;
	}
	if(sum&&!t[now]->connected()){
		sum--;
		chose[now]=true;
		search(now+1);
		chose[now]=false;
		sum++;
	}
	if(i-now!=sum)
		search(now+1);
}
int main(){
	scanf("%u%u",&n,&m);
	for(i=0;i<m;i++){
		scanf("%u %u %u",&a,&b,&c);
		t[i]=new bedge(V+a,V+b,c);
	}
	V[1].DFS();
	if(cnt<n){ puts("0"); goto end; }
	std::sort(t,t+m,cmp);
	for(i=0;i<m;){
		for(j=i++;i<m&&t[i-1]->c==t[i]->c;i++);
		copy();
		sum=0;
		for(int k=j;k<i;k++) if(t[k]->link()) ++sum;
		cnt=0;
		copy();
		search(j);
		ans=ans*cnt%31011;
		for(int k=j;k<i;k++) t[k]->link();
		recopy();
	}
	printf("%u\n",ans);
	end:;
}
