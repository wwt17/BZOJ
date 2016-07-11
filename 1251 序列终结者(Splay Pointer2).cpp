#include <cstdio>
inline int max(const int a,const int b){return a>b?a:b;}
inline int min(const int a,const int b){return a<b?a:b;}
inline bool maxi(int &a,const int b){return b>a?(a=b,true):false;}
inline bool mini(int &a,const int b){return b<a?(a=b,true):false;}
int N;
	struct node;
	node *root,*null;
	inline void swap(node* &a,node* &b){node* tmp=a;a=b;b=tmp;}
	struct node{
		node *ch[2],*fa;
		int size,val,Add,Max;
		bool rev;
		node():fa(null),size(0),val(0),Add(0),Max(0),rev(0){
			ch[0]=null;ch[1]=null;
		}
		node(int Val,node* Fa):fa(Fa),size(1),val(Val),Add(0),Max(0),rev(0){
			ch[0]=null;ch[1]=null;
		}
		void init(){node();}
		void updata(){
			size=ch[0]->size+ch[1]->size+1;
			Max=max(val,max(ch[0]->Max,ch[1]->Max));
		}
		void downdata(){
			if (rev){
				swap(ch[0],ch[1]);
				ch[0]->rev^=1;
				ch[1]->rev^=1;
				rev=false;
			}
			if (Add){
				ch[0]->addmark(Add);
				ch[1]->addmark(Add);
				Add=0;
			}
		}
		inline void addmark(int V){
			if (this==null) return;
			val+=V;Add+=V;Max+=V;
		}
		inline void cnct(bool f,node* x){ch[f]=x;x->fa=this;}
		inline bool right(){return fa->ch[1]==this;}
		void rotate(bool f){
			node *x=this,*y=fa;
			y->downdata();
			x->downdata();
			y->fa->cnct(y->right(),x);
			y->cnct(f,x->ch[!f]);
			x->cnct(!f,y);
			y->updata();
		}
		void splay(){splay(root);}
		void splay(node* &goal){
			downdata();
			node *y,*top=goal->fa;bool f;
			while (fa!=top){
				y=fa;f=y->right();
				if (y->fa==top) rotate(right()); else
				if (f^right()) rotate(!f),rotate(f);
				else y->rotate(f),rotate(f);
			}
			updata();
			goal=this;
		}
		void print();
		void print(char[]);
		void printtree(int);
		void printtree();
		void printline();
		void printline(int,bool);
	};
	node* build(int Size,node* Fa){
		if (Size<=0) return null;
		node* ret=new node(0,Fa);
		ret->size=Size;
		ret->ch[0]=build(Size>>1,ret);
		ret->ch[1]=build(Size-1-ret->ch[0]->size,ret);
		return ret;
	}
struct SplayTree{
	SplayTree(){
		root=null=new node;
		null->fa=null->ch[0]=null->ch[1]=null;
		null->Max=0x80000000;
	}
	SplayTree(int Size){
		SplayTree();
		root=build(Size,null);
	}
	node* find(int k){
		node* ret=root;
		int mid;
		while (ret->downdata(),k!=(mid=ret->ch[0]->size+1))
			ret=(k<mid?ret->ch[0]:(k-=mid,ret->ch[1]));
		ret->downdata();
		return ret;
	}
	void select(int L,int R){
		find(L-1)->splay(root);
		find(R+1)->splay(root->ch[1]);
	}
	void plus(int L,int R,int V){
		select(L,R);
		root->ch[1]->ch[0]->addmark(V);
	}
	void reverse(int L,int R){
		select(L,R);
		root->ch[1]->ch[0]->rev^=1;
	}
	int questmax(int L,int R){
		select(L,R);
		return root->ch[1]->ch[0]->Max;
	}
};
inline int getint(){
	char c;bool f=false;int a=0;
	for (c=getchar();(c<'0'||'9'<c)&&c!='-';c=getchar());
	if (c=='-') f=true; else a=a*10+(c-'0');
	for (c=getchar();'0'<=c&&c<='9';c=getchar()) a=a*10+(c-'0');
	if (f) a=-a;
	return a;
}
inline void putint(int a){
	if (a<0) {putchar('-');a=-a;}
	if (a>9) putint(a/10); putchar('0'+a%10);
}
int main(){
	int M,K,L,R,V;N=getint();M=getint();
	SplayTree seq(N+2);
	while (M--){
		K=getint();L=getint()+1;R=getint()+1;
		switch (K){
			case 1:V=getint();seq.plus(L,R,V);break;
			case 2:seq.reverse(L,R);break;
			case 3:putint(seq.questmax(L,R));putchar('\n');
		}
	}
	scanf("%d");
}
