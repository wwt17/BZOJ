#include <cstdio>

const int N=100005;

int n,m,a[N],last[N],pred[N],succ[N];

struct tree{
	tree *l,*r;
	int Max;
} mem[30000005],*newtree=mem;
struct tree2{
	tree2 *l,*r;
	tree *a;
	tree2():l(NULL),r(NULL),a(NULL){
	}
} *root;
int L2,R2,L,R,x,y,val;
void cover(tree *&cur,int beg,int end){
	if(!cur) cur=newtree++;
	if(L<=beg&&R>=end){
		if(val>cur->Max) cur->Max=val;
		return;
	}
	int mid=beg+end>>1;
	if(L<mid) cover(cur->l,beg,mid);
	if(R>mid) cover(cur->r,mid,end);
}
void cover(tree2 *&cur,int beg,int end){
	if(!cur) cur=new tree2;
	if(L2<=beg&&R2>=end){
		cover(cur->a,1,n+1);
		return;
	}
	int mid=beg+end>>1;
	if(L2<mid) cover(cur->l,beg,mid);
	if(R2>mid) cover(cur->r,mid,end);
}
void query(tree *cur){
	int beg=1,end=n+1;
	while(cur){
		if(cur->Max>val) val=cur->Max;
		if(end-beg==1) return;
		int mid=beg+end>>1;
		if(y<mid){
			end=mid;
			cur=cur->l;
		}
		else{
			beg=mid;
			cur=cur->r;
		}
	}
}
void query(tree2 *cur){
	int beg=1,end=n+1;
	while(cur){
		query(cur->a);
		if(end-beg==1) return;
		int mid=beg+end>>1;
		if(x<mid){
			end=mid;
			cur=cur->l;
		}
		else{
			beg=mid;
			cur=cur->r;
		}
	}
}

int main(){
	scanf("%d%d",&n,&m);
	for(int i=1;i<=n;i++){
		scanf("%d",&a[i]);
		pred[i]=last[a[i]];
		succ[last[a[i]]]=i;
		last[a[i]]=i;
	}
	for(int i=1;i<=n;i++){
		if(!succ[i]) succ[i]=n+1;
		L2=pred[i]+1;
		R2=i+1;
		L=i;
		R=succ[i];
		val=a[i];
		cover(root,1,n+1);
	}
	val=0;
	while(m--){
		scanf("%d%d",&x,&y);
		x=(x+val)%n+1;
		y=(y+val)%n+1;
		if(x>y){
			int t=x; x=y; y=t;
		}
		val=0;
		query(root);
		printf("%d\n",val);
	}
}
