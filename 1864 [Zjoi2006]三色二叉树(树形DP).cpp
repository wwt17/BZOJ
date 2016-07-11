#include <cstdio>
#include <algorithm>
using namespace std;
struct node{
	int a[2],b[2];
	node(){
		char c=getchar();
		if(c=='0'){
			a[0]=b[0]=0;
			a[1]=b[1]=1;
		} else
		if(c=='1'){
			node son;
			a[0]=max(son.a[0],son.a[1]);
			a[1]=1+son.a[0];
			b[0]=min(son.b[0],son.b[1]);
			b[1]=1+son.b[0];
		} else
		if(c=='2'){
			node son[2];
			a[0]=max(son[0].a[0]+son[1].a[1],son[0].a[1]+son[1].a[0]);
			a[1]=1+son[0].a[0]+son[1].a[0];
			b[0]=min(son[0].b[0]+son[1].b[1],son[0].b[1]+son[1].b[0]);
			b[1]=1+son[0].b[0]+son[1].b[0];
		}
	}
} r;
int main(){
	printf("%d %d\n",max(r.a[0],r.a[1]),min(r.b[0],r.b[1]));
}
