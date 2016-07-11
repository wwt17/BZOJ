#include <cstdio>
#include <algorithm>
using namespace std;

const int N=1e5+5;

int n;

typedef pair<int,int> vec;
#define n1 first
#define n2 second
struct data{
	vec p;
	data *next[2];
} a[N],*ord[N],e;
bool cmp(data *a,data *b){
	return a->p<b->p;
}

int main(){
	scanf("%d",&n);
	for(int i=0;i<n;i++){
		scanf("%d%d",&a[i].p.n1,&a[i].p.n2);
		ord[i]=a+i;
	}
	sort(ord,ord+n,cmp);
	for(int i=0;i<n-1;i++) if(ord[i]->p.n1==ord[i+1]->p.n1)
		ord[i]->next[0]=ord[i+1];
	for(int i=0;i<n;i++) swap(a[i].p.n1,a[i].p.n2);
	sort(ord,ord+n,cmp);
	for(int i=0;i<n-1;i++) if(ord[i]->p.n1==ord[i+1]->p.n1)
		ord[i]->next[1]=ord[i+1];
	int ans=-n;
	for(int i=0;i<n;i++)
		for(data *x=a+i,*y=a+i;x&&y;){
			e.p=vec(x->p.n1-a[i].p.n1,y->p.n2-a[i].p.n2);
			if(e.p.n1<e.p.n2) x=x->next[0]; else
			if(e.p.n1>e.p.n2) y=y->next[1]; else{
				e.p.n1+=a[i].p.n1;
				e.p.n2+=a[i].p.n2;
				data **tmp=lower_bound(ord,ord+n,&e,cmp);
				if(tmp<ord+n&&(*tmp)->p==e.p) ans++;
				x=x->next[0];
				y=y->next[1];
			}
		}
	printf("%d\n",ans);
	scanf("\n");
}

