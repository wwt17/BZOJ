#include <cstdio>
#include <cstdlib>
#include <cstring>
#define Sp system("pause")
#define Pln printf("\n")
#define chBase 27
#define LenSize 100005
inline int max(const int a,const int b){return a>b?a:b;}
inline int min(const int a,const int b){return a<b?a:b;}
inline bool maxi(int &a,const int b){return b>a?(a=b,true):false;}
inline bool mini(int &a,const int b){return b<a?(a=b,true):false;}
unsigned N,Num=0,Pow[LenSize]; char str[LenSize];
	struct node;
	node *root,*null,*obj;
	inline void swap(node* &a,node* &b){node* tmp=a;a=b;b=tmp;}
	struct node{
		node *c[2],*fa;
		char ch;unsigned hash,size;
		node():fa(null),size(0){c[0]=c[1]=null;}
		node(char _ch,node* Fa):fa(Fa),size(1),ch(_ch){c[0]=c[1]=null;}
		void updata(){
			size=c[0]->size+c[1]->size+1;
			hash=c[0]->hash+ch*Pow[c[0]->size]+c[1]->hash*Pow[c[0]->size+1];
		}
		void downdata(){}
		inline void cnct(bool f,node* x){c[f]=x;x->fa=this;}
		inline bool right(){return fa->c[1]==this;}
		void rotate(bool f){
			node *x=this,*y=fa;
			y->downdata();
			x->downdata();
			y->fa->cnct(y->right(),x);
			y->cnct(f,x->c[!f]);
			x->cnct(!f,y);
			y->updata();
		}
		void splay(){splay(root);}
		void splay(node* &goal){
			node *y,*top=goal->fa;bool f;
			downdata();
			while (fa!=top){
				y=fa;f=y->right();
				if (y->fa==top) rotate(right()); else
				if (f^right()) rotate(!f),rotate(f);
				else y->rotate(f),rotate(f);
			}
			updata();
			goal=this;
		}
		void print() {
			if (this==obj) printf("-> ");
			printf("%c size=%d l=%c r=%c fa=%c\n",
			ch^'@',size,c[0]->ch^'@',c[1]->ch^'@',fa->ch^'@');
		}
		void print(char name[]) { printf("%s ",name); print(); }
		void ptree(int tab) {
			int i;
			for (i=1;i<=tab;++i) printf("| ");
			if (this==null) {printf("null\n");return;}
			if (i==tab+1) print();
			if (c[0]==null&&c[1]==null) return;
			c[0]->ptree(tab+1);
			c[1]->ptree(tab+1);
		}
		void ptree() { printf("\n"); ptree(0); }
		void pliln() { pline(); printf("\n"); }
		void pline() {
			if (this==null) return;
			c[0]->pline();
			printf("%c",ch+'`');
			c[1]->pline();
		}
	};
	node* build(int Size,node* Fa){
		if (Size<=0) return null;
		node* ret=new node(0,Fa);
		ret->size=Size;
		ret->c[0]=build(Size>>1,ret);
		ret->ch=str[Num++]^'`';
		ret->c[1]=build(Size-1-ret->c[0]->size,ret);
		ret->updata();
		return ret;
	}
struct SplayTree{
	SplayTree(){
		root=null=new node;
		null->fa=null->c[0]=null->c[1]=null;
		null->ch=0; null->hash=0;
	}
	SplayTree(int Size){
		SplayTree();
		root=build(Size,null);
		node* x;
		for (x=root;x->c[0]!=null;x=x->c[0])++x->size;
		x->c[0]=new node(0,x);++x->size;
		for (x=root;x->c[1]!=null;x=x->c[1])++x->size;
		x->c[1]=new node(0,x);++x->size;
	}
	node* find(int k){
		node* ret=root;
		int mid;
		while (ret->size&&(ret->downdata(),k!=(mid=ret->c[0]->size+1)))
			ret=(k<mid?ret->c[0]:(k-=mid,ret->c[1]));
		ret->downdata();
		return ret;
	}
	node* select(int L,int R){
		find(L-1)->splay(root);
		find(R+1)->splay(root->c[1]);
		return root->c[1]->c[0];
	}
	void chg(int x,char d){
		find(x)->splay();
		root->ch=d^'`';
		root->updata();
	}
	void ins(int x,char d){
		find(x)->splay();
		node* y=new node(d^'`',null);
		y->cnct(0,root);
		y->cnct(1,root->c[1]); root->c[1]=null; root->updata();
		y->updata();
		root=y;
	}
	int LCQ(int x,int y){
		int l=0,r=root->size-max(x,y)-1,mid,ans=0,h1,h2;
		while (l<=r){
			if (mid=(l+r)/2,(h1=select(x,x+mid)->hash)!=(h2=select(y,y+mid)->hash))
				r=mid-1; else maxi(ans,mid+1),l=mid+1;
		}
		return ans;
	}
};
int main(){
	int M,i;
	scanf("%s",str);
	N=strlen(str);
	for (Pow[0]=i=1;i<LenSize;++i) Pow[i]=Pow[i-1]*chBase;
	SplayTree s(N);++N;
	scanf("%d",&M);
	char opt,d; int x,y;
	while (M--) switch (scanf("\n%c ",&opt),opt){
		case 'Q':scanf("%d %d",&x,&y);++x,++y;
			printf("%d\n",s.LCQ(x,y));
			break;
		case 'R':scanf("%d %c",&x,&d);++x;
			s.chg(x,d);
			break;
		case 'I':scanf("%d %c",&x,&d);++x;
			s.ins(x,d);
	}
}
